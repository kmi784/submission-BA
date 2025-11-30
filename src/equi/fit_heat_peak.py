import time
from pathlib import Path

import gvar as gv
import numpy as np
from scipy.optimize import curve_fit


def _fit_result(value: float, variance: float) -> str:
    return str(gv.gvar(value, np.sqrt(variance)))


def _power(L, A, rho):
    return A * L**rho


def _expo(L, A, L0):
    return A / np.log(L / L0)


def _chi2(y: np.array, fit: np.array, error: np.array):
    return np.sum(((y - fit) / error) ** 2)


def fit_universell_law(
    target_directory: Path,
    fit_log_append: bool = True,
    lowest_datapoint: int = 0,
) -> None:
    """
    fits of the maximum temperature (heat maximum) as function of lattice length

    Parameters
    ----------
        `target_directory`: `Path`
            Directory where the raw simulation data is stored of the equilibrium
            treatment
        `fit_log_append`: `bool`
            If `True` it will append the fit log not overwrite it
        `lowest_datapoint`: `int`
            Cuts the data of the heat-peaks temperatures
    """
    with open("fit_equi.log", "a" if fit_log_append else "w") as f:
        f.write(
            "\n" + 89 * "*" + "\n"
            f"Target:   {target_directory / "fit.txt"}\n"
            f"Time:     {time.ctime()}\n\n"
        )

        L, T, errorT, C, errorC = np.transpose(np.loadtxt(target_directory / "fit.txt"))
        L, T, errorT = (
            L[lowest_datapoint:],
            T[lowest_datapoint:],
            errorT[lowest_datapoint:],
        )

        for i in range(0, len(L)):
            f.write(
                rf"${L[i]}$ & ${_fit_result(T[i], errorT[i]**2)}$ &"
                rf"${_fit_result(C[i], errorC[i]**2)}$ \\" + "\n"
            )
        f.write("\n")

        fit1, cov1 = curve_fit(_power, L, T, sigma=errorT)
        chi2_fit1 = round(_chi2(T, _power(L, *fit1), errorT) / (len(T) - len(fit1)), 3)

        fit2, cov2 = curve_fit(_expo, L, T, sigma=errorT)
        chi2_fit2 = round(_chi2(T, _expo(L, *fit2), errorT) / (len(T) - len(fit2)), 3)

        f.write(
            rf"${_fit_result(fit1[0], cov1[0][0])}$ & ${_fit_result(fit1[1], cov1[1][1])}$ "
            rf"& ${chi2_fit1}$ \\" + "\n"
            rf"${_fit_result(fit2[0], cov2[0][0])}$ & ${_fit_result(fit2[1], cov2[1][1])}$ "
            rf"& ${chi2_fit2}$ \\" + "\n\n"
            f"A = {fit1[0]}\nrho = {fit1[1]}\nA = {fit2[0]}\nL0 = {fit2[1]}\n"
        )


if __name__ == "__main__":
    fit_universell_law(
        target_directory=Path(__file__).parent.parent.parent / "data/raw/equi",
    )

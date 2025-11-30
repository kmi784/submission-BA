import time
from pathlib import Path

import numpy as np
from scipy.optimize import curve_fit

LATTICE_LENGTHS = (32, 64, 128)
ALGORITHMS = ("single", "line")
INITIAL_STATE = "U"


def _fit_result(value: float, variance: float) -> str:
    # import gvar as gv
    # return str(gv.gvar(value, np.sqrt(variance)))
    return rf"{value}\pm{np.sqrt(variance)}"


def _power(x, A, Tg, rho):
    return A * np.abs(Tg - x) ** (-rho)


def _vogel(x, A, T0, B):
    return A * np.exp(B / (x - T0))


def _chi2(y: np.array, fit: np.array, error: np.array):
    return np.sum(((y - fit) / error) ** 2)


def fit_glassy_temperature(
    target_directory: Path,
    fit_log_append: bool = True,
    lowest_datapoint={
        32: {"single": 0, "line": 8},
        64: {"single": 0, "line": 3},
        128: {"single": 0, "line": 1},
    },
) -> None:
    """
    fits of the relaxation time as function of the temperature to determine the glassy 
    transition temperature

    Parameters
    ----------
        `target_directory`: `Path`
            Directory where the raw simulation data is stored of the dynamical 
            treatment (low temperature quench)
        `fit_log_append`: `bool`
            If `True` it will append the fit log not overwrite it
        `lowest_datapoint`: `dict`
            Cuts the data of the relaxation time in the scheme
            `{<lattice length>: {"single": <lowest data point>, "line": <lowest data point>}}`
    """
    with open("fit_dynm.log", "a" if fit_log_append else "w") as f:
        columns = {
            "ferromagnetic": 1,
            "horizontal stripped": 3,
            "vertical stripped": 5,
        }
        guess = [2.0, 0.09, 2.5]
        for l in LATTICE_LENGTHS:
            for a in ALGORITHMS:
                for o in columns:
                    target = target_directory / f"L{l}-{INITIAL_STATE}-{a}/relax.txt"
                    T = np.loadtxt(target, usecols=0)
                    tau = np.loadtxt(target, usecols=columns[o])
                    error = np.loadtxt(target, usecols=columns[o] + 1)
                    ldp = lowest_datapoint[l][a]

                    fit1, cov1 = curve_fit(
                        _power,
                        T[ldp:],
                        tau[ldp:],
                        sigma=error[ldp:],
                    )
                    fit2, cov2 = curve_fit(
                        _vogel,
                        T[ldp:],
                        tau[ldp:],
                        sigma=error[ldp:],
                        p0=guess,
                    )

                    f.write(
                        "\n" + 89 * "*" + "\n"
                        f"Target:            {target}\n"
                        f"Orderparameter:    {o}\n"
                        f"Lowest data point: {ldp}\n"
                        f"Time:              {time.ctime()}\n\n"
                        rf"${_fit_result(fit1[0], cov1[0][0])}$ & "
                        rf"${_fit_result(fit1[1], cov1[1][1])}$ & "
                        rf"${_fit_result(fit1[2], cov1[2][2])}$ \\" + "\n"
                        rf"${_fit_result(fit2[0], cov2[0][0])}$ & "
                        rf"${_fit_result(fit2[1], cov2[1][1])}$ & "
                        rf"${_fit_result(fit2[2], cov2[2][2])}$ \\" + "\n\n"
                        f"Ap = {fit1[0]}\nTg = {fit1[1]}\nrho = {fit1[2]}\n"
                        f"Av = {fit2[0]}\nT0 = {fit2[1]}\nc = {fit2[2]}\n"
                    )


if __name__ == "__main__":
    fit_glassy_temperature(
        target_directory=Path(__file__).parent.parent.parent / "data/raw/dynm",
    )

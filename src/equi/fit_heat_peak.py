"""
fit script for the equilibrium treatment, i.e. fits of the maximum temperature 
(heat maximum) as function of lattice length
"""

import time
from pathlib import Path

import numpy as np
from scipy.optimize import curve_fit

TARGET = Path(__file__).parent.parent.parent / "data/raw/equi/fit.txt"


lowest_datapoint = 0


def _fit_result(value: float, variance: float) -> str:
    # import gvar as gv
    # return str(gv.gvar(value, np.sqrt(variance)))
    return rf"{value}\pm{np.sqrt(variance)}"


def power(L, A, rho):
    return A * L**rho


def expo(L, A, L0):
    return A / np.log(L / L0)


def chi2(y: np.array, fit: np.array, error: np.array):
    return np.sum(((y - fit) / error) ** 2)


with open("fit_equi.log", "a") as f:
    f.write(
        "\n" + 89 * "*" + "\n" f"Target:   {TARGET}\n" f"Time:     {time.ctime()}\n\n"
    )

    L, T, errorT, C, errorC = np.transpose(np.loadtxt(TARGET))
    L, T, errorT = L[lowest_datapoint:], T[lowest_datapoint:], errorT[lowest_datapoint:]

    for i in range(0, len(L)):
        f.write(
            rf"${L[i]}$ & ${_fit_result(T[i], errorT[i]**2)}$ &"
            rf"${_fit_result(C[i], errorC[i]**2)}$ \\" + "\n"
        )
    f.write("\n")

    fit1, cov1 = curve_fit(power, L, T, sigma=errorT)
    chi2_fit1 = round(chi2(T, power(L, *fit1), errorT) / (len(T) - len(fit1)), 3)

    fit2, cov2 = curve_fit(expo, L, T, sigma=errorT)
    chi2_fit2 = round(chi2(T, expo(L, *fit2), errorT) / (len(T) - len(fit2)), 3)

    f.write(
        rf"${_fit_result(fit1[0], cov1[0][0])}$ & ${_fit_result(fit1[1], cov1[1][1])}$ "
        rf"& ${chi2_fit1}$ \\" + "\n"
        rf"${_fit_result(fit2[0], cov2[0][0])}$ & ${_fit_result(fit2[1], cov2[1][1])}$ "
        rf"& ${chi2_fit2}$ \\" + "\n\n"
        f"A = {fit1[0]}\nrho = {fit1[1]}\nA = {fit2[0]}\nL0 = {fit2[1]}\n"
    )

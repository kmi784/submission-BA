import time 
from pathlib import Path

import numpy as np 
import gvar as gv
from scipy.optimize import curve_fit

target = "L128-U-single/"
dir = f"{Path(__file__).parent / "../../data/raw/dynm"}/"  
orderparameter = "V"
min = 0


def power(x,  A, Tg, rho) :
    return A*np.abs(Tg-x)**(-rho)

guess = [2.0, 0.09, 2.5]
def vogel(x, A, T0, B) :
    return A*np.exp(B/(x-T0))

def chi2(y : np.array, fit : np.array, error : np.array) : 
    return np.sum(((y-fit)/error)**2)

save = open("fit.log", "a")

if orderparameter == 'F' :
    column = 1
elif orderparameter == 'H' :
    column = 3
elif orderparameter == 'V' :
    column = 5

T = np.loadtxt(dir + target + "relax.txt", usecols=0)
tau = np.loadtxt(dir + target + "relax.txt", usecols=column)
error = np.loadtxt(dir + target + "relax.txt", usecols=column+1)

fit1, cov1 = curve_fit(power, T[min:], tau[min:], sigma=error[min:])
fit2, cov2 = curve_fit(vogel, T[min:], tau[min:], sigma=error[min:], p0=guess)

save.write(
    "\n*************************************************************************\n" +
    "Target             :" + target + "\n" +
    "Orderparameter     :" + orderparameter + "\n" + 
    "Lower fit-boundary :" + str(min) + "\n" +
    "Time               :" + str(time.ctime()) + "\n\n"
)

save.write(
    "$" + str(gv.gvar(fit1[0], np.sqrt(cov1[0][0]))) + "$ & $" 
        + str(gv.gvar(fit1[1], np.sqrt(cov1[1][1]))) + "$ & $" 
        + str(gv.gvar(fit1[2], np.sqrt(cov1[2][2]))) + "$ \\\\\n" +
    "$" + str(gv.gvar(fit2[0], np.sqrt(cov2[0][0]))) + "$ & $" 
        + str(gv.gvar(fit2[1], np.sqrt(cov2[1][1]))) + "$ & $" 
        + str(gv.gvar(fit2[2], np.sqrt(cov2[2][2]))) + "$ \\\\\n"
        + "\n"
)

save.write(
    "Ap = " + str(fit1[0]) + "\nTg = " + str(fit1[1]) + "\nrho = " + str(fit1[2]) + "\n" +
    "Av = " + str(fit2[0]) + "\nT0 = " + str(fit2[1]) + "\nc = " + str(fit2[2]) + "\n" 
)

import time
from pathlib import Path

import numpy as np 
import gvar as gv
from scipy.optimize import curve_fit

target = "fit.txt" 
dir = f"{Path(__file__).parent / "../../data/raw/equi"}/"
min = 0                                

def power(L, A, rho) :
    return A*L**rho

def expo(L, A, L0) :
    return A/np.log(L/L0)

def chi2(y : np.array, fit : np.array, error : np.array) : 
    return np.sum(((y-fit)/error)**2)

save = open("fit.log", "a")
save.write(
    "\n*************************************************************************\n" +
    "Target             :" + target + "\n" +
    "Time               :" + str(time.ctime()) + "\n\n"
)

L, T, errorT, C, errorC = np.transpose(np.loadtxt(dir + target))
L, T, errorT = L[min:], T[min:], errorT[min:]

for i in range(0, len(L)) :
    save.write(
        "$" + str(L[i]) + "$ & $" + str(gv.gvar(T[i], errorT[i])) + "$ & $" + str(gv.gvar(C[i], errorC[i])) + "$ \\\\ \n"
    )   
save.write("\n")

fit1, cov1 = curve_fit(power, L, T, sigma=errorT)
fit2, cov2 = curve_fit(expo, L, T, sigma=errorT)

save.write(
    "$" + str(gv.gvar(fit1[0], np.sqrt(cov1[0][0]))) + "$ & $" 
        + str(gv.gvar(fit1[1], np.sqrt(cov1[1][1]))) + "$ & $" 
        + str(round(chi2(T, power(L, *fit1), errorT)/(len(T)-len(fit1)), 3)) + "$ \\\\\n" +
    "$" + str(gv.gvar(fit2[0], np.sqrt(cov2[0][0]))) + "$ & $" 
        + str(gv.gvar(fit2[1], np.sqrt(cov2[1][1]))) + "$ & $" 
        + str(round(chi2(T, expo(L, *fit2), errorT)/(len(T)-len(fit2)), 3)) + "$ \\\\\n"
        + "\n"
)

save.write(
    "A = " + str(fit1[0]) + "\nrho = " + str(fit1[1]) + "\nA = " + str(fit2[0]) + "\nL0 = " + str(fit2[1]) + "\n"
)


import sys
import numpy as np
from scipy.optimize import curve_fit


#******************** Arguments ********************#
target = str(sys.argv[1])                           # relative path + name to target "L_-_/"
min = float(sys.argv[2])                            # temperture range
max = float(sys.argv[3])                            #
#***************************************************#


def find_range(y : np.array) :
    min = 0; max = 0
    for index in range(0,len(y)) :
        if y[index] > np.exp(-1) :
            min = index
        if y[index] < 0.1 or index == len(y)-1 : 
            max = index
            break
    return min, max
        
def f(x, tau, A) :
    return -x/tau+np.log(A)

def tau_star(fit : list, cov : list) :
    t = fit[0]*np.log(100*fit[1])
    error = np.sqrt( cov[1][1]*(fit[0]/fit[1])**2
                    +cov[0][0]*np.log(100*fit[1])**2
                    +(cov[0][1]+cov[1][0])*fit[0]*np.log(100*fit[1])/fit[1])

    return t, error


with open(target + "relax.txt", "w") as file :
    for T in np.round(np.linspace(min, max, num=int(100*(max-min))+2), 2) :
        t,gammaF, errorF, gammaH, errorH, gammaV, errorV = np.transpose(np.loadtxt(target + "T" + str(int(T*1000)) + ".txt"))

        minF, maxF = find_range(gammaF)
        fitF, covF = curve_fit(f, t[minF:maxF], np.log(gammaF[minF:maxF]), sigma=errorF[minF:maxF]/gammaF[minF:maxF])
        outF = tau_star(fitF, covF)

        minH, maxH = find_range(gammaH)
        fitH, covH = curve_fit(f, t[minH:maxH], np.log(gammaH[minH:maxH]), sigma=errorH[minH:maxH]/gammaH[minH:maxH])
        outH = tau_star(fitH, covH)

        minV, maxV = find_range(gammaV)
        fitV, covV = curve_fit(f, t[minV:maxV], np.log(gammaV[minV:maxV]), sigma=errorV[minV:maxV]/gammaV[minV:maxV])
        outV = tau_star(fitV, covV)

        print("T =",T,"\tFitrange [",minF, ":", maxF,"]")

        file.write(str(T) + "\t" + str(outF[0]) + "\t" + str(outF[1]) 
                          + "\t" + str(outH[0]) + "\t" + str(outH[1]) 
                          + "\t" + str(outV[0]) + "\t" + str(outV[1]) + "\n")





    



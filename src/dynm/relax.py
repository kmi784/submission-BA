
import os
import numpy as np
from scipy.optimize import curve_fit



#******************** Arguments ********************#
target = "../../data/timmons/L128-U-line/"           # relative path + name to target "L_-_/"
min, max = 0.31, 0.6                               # temperture range
plot = True                                         # generates plot with gnuplot
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




#*************** Load data ***************#
Plot = []
with open(target + "relax.txt", "w") as file :
    for T in np.round(np.linspace(min, max, num=int(100*(max-min))+2), 2) :
        t, gammaF, errorF, gammaH, errorH, gammaV, errorV = np.transpose(np.loadtxt(target + "T" + str(int(T*1000)) + ".txt"))

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

        Plot.append([T, fitF[0], fitF[1], (int(str(maxF)[0])+1)*10**(len(str(maxF))-1)])

        file.write(str(T) + "\t" + str(outF[0]) + "\t" + str(outF[1]) 
                          + "\t" + str(outH[0]) + "\t" + str(outH[1]) 
                          + "\t" + str(outV[0]) + "\t" + str(outV[1]) + "\n")


if plot :
    with open(target + "plot.gp", "w") as file :
        file.write(
            "set terminal pngcairo size 1500,2000 enhanced font 'Verdana,10'\n" +
            "set output 'plot.png'\n\n"
            "set multiplot layout 10,3\n\n" +
            "set logscale y exp(1)\n" +
            "set grid"
        )



        for plot in Plot :
            file.write(
                "\n\nunset label; set label 'T=" + str(plot[0]) + "' at graph 0.1,0.1\n" +
                "set xrange[0 : " + str(plot[3]) + "]\n" +
                "plot \"T" + str(int(plot[0]*1000)) + ".txt\" u 1:4 w lines lt 7 t 'F' \\" + 
                "\n\t,\"T" + str(int(plot[0]*1000)) + ".txt\" u 1:6 w lines lt 2 t 'H' \\" + 
                "\n\t,\"T" + str(int(plot[0]*1000)) + ".txt\" u 1:8 w lines lt 6 t 'V' \\" +
                "\n\t," + str(plot[2]) + "*exp(-x/" + str(plot[1]) + ") w lines lt -1 notitle"  
            )

        file.write(
            "\n\nunset multiplot\n" +
            "reset"
        )

    os.chdir(target)
    os.system("gnuplot \"plot.gp\"")
    os.system("rm plot.gp")


    



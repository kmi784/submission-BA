
import gvar as gv
import numpy as np

L, T3, eT3, C3, eC3 = np.transpose(np.loadtxt("peakg3.txt"))
L, T6, eT6, C6, eC6 = np.transpose(np.loadtxt("peakg6.txt"))

save = open("latex.txt", "w")

for i in range(0,len(L)):
    save.write(
        "$" + str(int(L[i])) + "$ & $" + str(gv.gvar(T3[i],eT3[i])) + "$ & $" + str(gv.gvar(C3[i],eC3[i])) \
                             + "$ & $" + str(gv.gvar(T6[i],eT6[i])) + "$ & $" + str(gv.gvar(C6[i],eC6[i])) + "$ \\\\\n"

    )



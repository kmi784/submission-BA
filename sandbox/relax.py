
import numpy as np

#*************** Parameter ***************#
target = "../data/timmons/L64-U-line/"                  # path + name of target
times = [900, 9000, 90000]              # time of measurement
#*****************************************#






import glob


for path in sorted(glob.glob(target + "*")) :
    if path.find("T") >= 0 :
        t, GF, eGF, GH, eGH, GV, eGV = np.transpose(np.loadtxt(path))
        
        tau = []
        for G in [GF, GH, GV] :
            for i in range(0,len(G)) :
                if G[i] <= 0.01 :
                    tau.append(i+1)
                    break
        print(tau)

    #    T = float((path.split("T")[1]).split(".")[0])/1000

        
    #    input = open(path, "r")
    #    for j, line in enumerate(input) :
    #        if j == times[i] :
    #            data = line.split("\t")
    #            output.write(str(T) + "\t" + data[1] + "\t" + data[2] 
    #                                + "\t" + data[3] + "\t" + data[4]
    #                                + "\t" + data[5] + "\t" + data[6])
    #    input.close()

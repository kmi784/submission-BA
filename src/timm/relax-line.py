
import numpy as np
import glob


#******************** Arguments ********************#
target = "../../data/timmons/L64-U-line/"           # relative path + name to target "L_-_/"
Temperatures = [0.32, 0.33, 0.34]             # tempertures
#***************************************************#


new_lines = []
for path in sorted(glob.glob(target + "*")) :
    if path.find("T") >= 0 :
        T = float((path.split("T")[1]).split(".")[0])/1000
        for temp in Temperatures :
            if T  == temp :
                input = open(path, "r")
                first = input.readline()
                second = input.readline().split("\t")
                second[-1] = second[-1][:-1]

                new_line = str(T) + "\t"
                for i in range(0,3) :
                    G01 = float(second[2*i+1])
                    print(T,-1/np.log(G01))
                    sigma = float(second[2*i+2])
                    new_line += str(-np.log(100)/np.log(G01)) + "\t" + str(np.log(100)*sigma/(G01*np.log(G01)**2)) + "\t"
                new_line += "\n"

                new_lines.append(new_line)
                input.close()


input = open(target + "relax.txt", "r")
old_lines = input.readlines()
input.close()


output = open("relax.txt", "w")
for line in old_lines :
    for new_line in new_lines :
        if line.split("\t")[0] == new_line.split("\t")[0] :
            line = new_line

    output.write(line)


        





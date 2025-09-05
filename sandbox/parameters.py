

import glob


dir = "../data/kalz/"
Targets = ["L30-U/", "L40-U/", "L50-U/", "L60-U/", "L70-U/", "L80-U/", "L90-U/", "L100-U/", "L110-U/", "L120-U/"]

output = open("latex.txt", "w")
table1 = ""
table2 = ""

for target in Targets :
    L = target.split("-")[0][1:]
    initial_state = target.split("-")[1][:-1]


    Points, linebreak = "\\makecell{", 1
    for path in sorted(glob.glob(dir + target + "*")) :
        if path.find("T") >= 0 :
            point = "$(" + str(float((path.split("T")[1]).split(".")[0])/1000) + ","
            paras :str


            input = open(path + "/save.txt", "r")
            for i, line in enumerate(input) :
                if i == 1 :
                    data = line.split(" ")
                    
                    point = point + data[0] + ")$"
                    paras = "$" + data[1][0] + "." + data[1][1] + "\\cdot10^{" + str(len(data[1])-1) + "}$ & $" \
                                + data[2][0] + "." + data[2][1] + "\\cdot10^{" + str(len(data[2])-1) + "}$ & $" \
                                + data[3][0] + "." + data[3][1] + "\\cdot10^{" + str(len(data[3])-1) + "}$"



            if linebreak == 4 :
                Points = Points + point + ",\\\\"
                linebreak = 1
            else :
                Points = Points + point + ","
                linebreak = linebreak +1
            
             
    table1 = table1 + "$" + L + "$ & " + Points[:-1] + "} \\\\\n\\hline\n"
    table2 = table2 + "$" + L + "$ & \\verb|" + initial_state + "| & " + paras + "\\\\\n"


output.write(table1 + "\n\n\n" + table2)


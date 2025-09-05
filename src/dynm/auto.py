from glob import glob
from pathlib import Path

target = f"{Path(__file__).parent / "../../data/raw/dynm/L32-F-line"}/" # path + name of target
times = [900, 9000, 90000] # time of measurement


for i in range(0,len(times)) :
    output = open(target + "autot" + str(i+1) + ".txt", "w")
    for path in sorted(glob(target + "*")) :
        if path.find("T") >= 0 :
            T = float((path.split("T")[1]).split(".")[0])/1000

            input = open(path, "r")
            for j, line in enumerate(input) :
                if j == times[i] :
                    data = line.split("\t")
                    output.write(str(T) + "\t" + data[1] + "\t" + data[2] 
                                        + "\t" + data[3] + "\t" + data[4]
                                        + "\t" + data[5] + "\t" + data[6])
            input.close()
    output.close()

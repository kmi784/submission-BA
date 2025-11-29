"""
relaxation time patch-script for the dynamical treatment (low temperature quench), i.e.
some relaxation times cannot be determined by fitting exponential decay to timeseries
"""

import glob
from pathlib import Path

import numpy as np

TARGET_DIR = Path(__file__).parent.parent.parent / "data/raw/dynm"


target = "L64-U-line"  
temperatures = [0.32, 0.33, 0.34]  # patch temperatures


new_lines = []
for path in sorted(glob.glob(str(TARGET_DIR / target) + "/*")):
    if path.find("T") >= 0:
        T = float((path.split("T")[1]).split(".")[0]) / 1000
        for temp in temperatures:
            if T == temp:
                input = open(path, "r")
                first = input.readline()
                second = input.readline().split("\t")
                second[-1] = second[-1][:-1]

                new_line = f"{T}\t"
                for i in range(0, 3):
                    G01 = float(second[2 * i + 1])
                    print(T, -1 / np.log(G01))
                    sigma = float(second[2 * i + 2])
                    new_line += (
                        f"{-np.log(100) / np.log(G01)}\t"
                        f"{np.log(100) * sigma / (G01 * np.log(G01) ** 2)}"
                    )
                new_line += "\n"

                new_lines.append(new_line)
                input.close()

input = open(TARGET_DIR / target  / "relax.txt", "r")
old_lines = input.readlines()
input.close()

output = open("relax.txt", "w")
for line in old_lines:
    for new_line in new_lines:
        if line.split("\t")[0] == new_line.split("\t")[0]:
            line = new_line

    output.write(line)

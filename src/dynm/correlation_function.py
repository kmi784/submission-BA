"""
correlation function script for the dynamical treatment (high temperature quench), i.e. 
collects the correlation as function of the temperature at set measurement times and 
writes them in <number of set measurement times> files 
"""

from glob import glob
from pathlib import Path

TARGET_DIR = Path(__file__).parent.parent.parent / "data/raw/dynm"
LATTICE_LENGTHS = (32, 64, 128)
ALGORITHMS = ("single", "line")
INITIAL_STATE = "F"

times = [900, 9000, 90000]  # time of measurement

for l in LATTICE_LENGTHS:
    for a in ALGORITHMS:
        target = TARGET_DIR / f"L{l}-{INITIAL_STATE}-{a}"
        for i in range(0, len(times)):
            with open(target / f"autot{i+1}.txt", "w") as fout:
                for path in sorted(glob(str(target) + "/*")):
                    if path.find("T") >= 0:
                        T = float((path.split("T")[1]).split(".")[0]) / 1000
                        with open(path, "r") as fin:
                            for j, line in enumerate(fin):
                                if j == times[i]:
                                    data = line.split("\t")
                                    fout.write(f"{T}\t" + "\t".join(data[1:]))



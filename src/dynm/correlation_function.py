from glob import glob
from pathlib import Path

LATTICE_LENGTHS = (32, 64, 128)
ALGORITHMS = ("single", "line")
INITIAL_STATE = "F"


def collect_correlation_function(
    target_directory: Path, time_points: list = [900, 9000, 90000]
) -> None:
    """
    collects the correlation as function of the temperature at set measurement
    time points and writes them in <len(time_points)> different  files.

    Parameters
    ----------
        `target_directory`: `Path`
            Directory where the raw simulation data is stored of the dynamical 
            treatment (high temperature quench)
        `time_points`: `list`
            Time points of the considered measurements 
    """
    for l in LATTICE_LENGTHS:
        for a in ALGORITHMS:
            target = target_directory / f"L{l}-{INITIAL_STATE}-{a}"
            for i in range(0, len(  time_points)):
                with open(target / f"autot{i+1}.txt", "w") as fout:
                    for path in sorted(glob(str(target) + "/*")):
                        if path.find("T") >= 0:
                            T = float((path.split("T")[1]).split(".")[0]) / 1000
                            with open(path, "r") as fin:
                                for j, line in enumerate(fin):
                                    if j ==   time_points[i]:
                                        data = line.split("\t")
                                        fout.write(f"{T}\t" + "\t".join(data[1:]))


if __name__ == "__main__":
    collect_correlation_function(Path(__file__).parent.parent.parent / "data/raw/dynm")

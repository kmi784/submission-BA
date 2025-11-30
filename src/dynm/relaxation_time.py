from pathlib import Path

import numpy as np
from scipy.optimize import curve_fit

LATTICE_LENGTHS = (32, 64, 128)
ALGORITHMS = ("single", "line")
INITIAL_STATE = "U"


def _find_range(y: np.array):
    min = 0
    max = 0
    for index in range(0, len(y)):
        if y[index] > np.exp(-1):
            min = index
        if y[index] < 0.1 or index == len(y) - 1:
            max = index
            break
    return min, max


def _f(x, tau, A):
    return -x / tau + np.log(A)


def _tau_star(fit: list, cov: list):
    t = fit[0] * np.log(100 * fit[1])
    error = np.sqrt(
        cov[1][1] * (fit[0] / fit[1]) ** 2
        + cov[0][0] * np.log(100 * fit[1]) ** 2
        + (cov[0][1] + cov[1][0]) * fit[0] * np.log(100 * fit[1]) / fit[1]
    )

    return t, error


def compute_relaxation_times(
    target_directory: Path,
    temperature_ranges: dict,
    generate_plot: bool = False,
) -> None:
    """
    determines the exponential decay constant by ranged least square fits and computes
    with the fit parameters the relaxation time as function of the temperature, if want
    a multi plot can be generated with gnuplot by setting `generate_plot=True`

    Parameters
    ----------
        `target_directory`: `Path`
            Directory where the raw simulation data is stored of the dynamical
            treatment (low temperature quench)
        `temperature_ranges`: `dict`
            Temperature ranges for the simulated systems in the scheme
            `{<lattice length>: (<temperature minimum>, temperature maximum)}`
        `generate_plot`: `bool`
            If `True` a multi plot is generated containing via gnuplot containing
            the exponentially decaying timeseries (order parameter) and its fits

    """
    for l in LATTICE_LENGTHS:
        for a in ALGORITHMS:
            target = target_directory / f"L{l}-{INITIAL_STATE}-{a}"
            min, max = temperature_ranges[l]
            plot = []
            with open(target / "relax.txt", "w") as file:
                print(f"\nTarget: {target}")
                for T in np.round(
                    np.linspace(min, max, num=int(100 * (max - min)) + 2), 2
                ):
                    t, gammaF, errorF, gammaH, errorH, gammaV, errorV = np.transpose(
                        np.loadtxt(target / f"T{int(T * 1000)}.txt")
                    )

                    minF, maxF = _find_range(gammaF)
                    if (maxF - minF) < 2:
                        continue
                    fitF, covF = curve_fit(
                        _f,
                        t[minF:maxF],
                        np.log(gammaF[minF:maxF]),
                        sigma=errorF[minF:maxF] / gammaF[minF:maxF],
                    )
                    outF = _tau_star(fitF, covF)

                    minH, maxH = _find_range(gammaH)
                    fitH, covH = curve_fit(
                        _f,
                        t[minH:maxH],
                        np.log(gammaH[minH:maxH]),
                        sigma=errorH[minH:maxH] / gammaH[minH:maxH],
                    )
                    outH = _tau_star(fitH, covH)

                    minV, maxV = _find_range(gammaV)
                    fitV, covV = curve_fit(
                        _f,
                        t[minV:maxV],
                        np.log(gammaV[minV:maxV]),
                        sigma=errorV[minV:maxV] / gammaV[minV:maxV],
                    )
                    outV = _tau_star(fitV, covV)

                    print("T =", T, "\tFitrange [", minF, ":", maxF, "]")

                    plot.append(
                        [
                            T,
                            fitF[0],
                            fitF[1],
                            (int(str(maxF)[0]) + 1) * 10 ** (len(str(maxF)) - 1),
                        ]
                    )

                    file.write(
                        f"{T}\t{outF[0]}\t{outF[1]}\t{outH[0]}\t{outH[1]}\t{outV[0]}\t{outV[1]}\n"
                    )

            if generate_plot:
                import os

                with open(target / "plot.gp", "w") as file:
                    file.write(
                        "set terminal pngcairo size 1500,2000 enhanced font 'Verdana,10'\n"
                        "set output 'plot.png'\n"
                        "set multiplot layout 10,3\n"
                        "set logscale y exp(1)\n"
                        "set grid\n"
                    )

                    for generate_plot in plot:
                        file.write(
                            f"unset label; set label 'T={generate_plot[0]}' at graph 0.1,0.1\n"
                            f"set xrange[0 : {generate_plot[3]}]\n"
                            f"plot 'T{int(generate_plot[0] * 1000)}.txt' u 1:4 w lines lt 7 t 'F' \\\n"
                            f"  ,'T{int(generate_plot[0] * 1000)}.txt' u 1:6 w lines lt 2 t 'H' \\\n"
                            f"  ,'T{int(generate_plot[0] * 1000)}.txt' u 1:8 w lines lt 6 t 'V' \\\n"
                            f"  ,{generate_plot[2]}*exp(-x/{generate_plot[1]}) w lines lt -1 notitle\n"
                        )

                    file.write("\nunset multiplot\nreset")

                os.chdir(target)
                os.system('gnuplot "plot.gp"')
                os.system("rm plot.gp")


if __name__ == "__main__":
    compute_relaxation_times(
        target_directory=Path(__file__).parent.parent.parent / "data/raw/dynm",
        temperature_ranges={
            32: (0.31, 0.6),
            64: (0.31, 0.6),
            128: (0.31, 0.6),
        },
        generate_plot=True
    )

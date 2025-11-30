import subprocess
from pathlib import Path
from typing import Literal

from dynm import (
    collect_correlation_function,
    compute_relaxation_times,
    fit_glassy_temperature,
)

from equi import fit_universell_law

SIGNAL_NAMES = {
    -11: "Segmentation Fault",
    -6: "Abort (SIGABRT)",
    -8: "Floating point exception",
    -4: "Illegal instruction",
    -9: "Killed",
}

ARGS_EQUI = {
    30: {
        "initial state": "U",
        "number equilibration": int(2.0e7),
        "number of simulation sweeps": int(5.0e7),
        "number of sweeps per block": int(5.0e5),
        "simulation point": {
            0.37: 9481,
            0.386: 8879,
            0.402: 1876,
            0.418: 8270,
            0.434: 1628,
            0.45: 9600,
            0.466: 5181,
            0.482: 8255,
            0.498: 7964,
            0.514: 7966,
            0.53: 8799,
        },
    },
    40: {
        "initial state": "U",
        "number equilibration": int(2.0e7),
        "number of simulation sweeps": int(5.0e7),
        "number of sweeps per block": int(5.0e5),
        "simulation point": {
            0.35: 3101,
            0.36: 6454,
            0.37: 2636,
            0.38: 3449,
            0.39: 4370,
            0.4: 3573,
            0.41: 2464,
            0.42: 9733,
            0.43: 6951,
            0.44: 9248,
            0.45: 404,
        },
    },
    50: {
        "initial state": "U",
        "number equilibration": int(2.0e7),
        "number of simulation sweeps": int(5.0e7),
        "number of sweeps per block": int(5.0e5),
        "simulation point": {
            0.34: 1262,
            0.35: 3959,
            0.36: 323,
            0.37: 7862,
            0.38: 3965,
            0.39: 9907,
            0.4: 4951,
            0.41: 353,
            0.42: 4764,
            0.43: 6756,
            0.44: 5063,
        },
    },
    60: {
        "initial state": "U",
        "number equilibration": int(2.0e7),
        "number of simulation sweeps": int(5.0e7),
        "number of sweeps per block": int(5.0e5),
        "simulation point": {
            0.33: 1304,
            0.34: 9748,
            0.35: 666,
            0.36: 7767,
            0.37: 6541,
            0.38: 6140,
            0.39: 4617,
            0.4: 848,
            0.41: 8426,
            0.42: 8597,
            0.43: 5430,
        },
    },
    70: {
        "initial state": "U",
        "number equilibration": int(5.0e7),
        "number of simulation sweeps": int(1.0e8),
        "number of sweeps per block": int(1.0e6),
        "simulation point": {
            0.32: 9334,
            0.33: 5248,
            0.34: 1710,
            0.35: 5503,
            0.36: 5083,
            0.37: 4443,
            0.38: 8094,
            0.39: 8390,
            0.4: 3062,
            0.41: 4150,
            0.42: 7934,
        },
    },
    80: {
        "initial state": "U",
        "number equilibration": int(5.0e7),
        "number of simulation sweeps": int(1.0e8),
        "number of sweeps per block": int(1.0e6),
        "simulation point": {
            0.32: 5660,
            0.326: 478,
            0.332: 286,
            0.338: 5366,
            0.344: 3288,
            0.35: 4412,
            0.356: 4696,
            0.362: 4554,
            0.368: 7866,
            0.374: 4665,
            0.38: 2323,
        },
    },
    90: {
        "initial state": "U",
        "number equilibration": int(5.0e7),
        "number of simulation sweeps": int(1.0e8),
        "number of sweeps per block": int(1.0e6),
        "simulation point": {
            0.32: 849,
            0.325: 120,
            0.33: 4593,
            0.335: 8940,
            0.34: 80,
            0.345: 8962,
            0.35: 4891,
            0.355: 3008,
            0.36: 115,
            0.365: 4401,
            0.37: 8335,
        },
    },
    100: {
        "initial state": "U",
        "number equilibration": int(1.0e8),
        "number of simulation sweeps": int(1.5e8),
        "number of sweeps per block": int(1.5e6),
        "simulation point": {
            0.31: 7564,
            0.315: 545,
            0.32: 7460,
            0.325: 6423,
            0.33: 819,
            0.335: 6148,
            0.34: 2233,
            0.345: 7,
            0.35: 9428,
            0.355: 7516,
            0.36: 4740,
        },
    },
    110: {
        "initial state": "U",
        "number equilibration": int(1.0e8),
        "number of simulation sweeps": int(1.5e8),
        "number of sweeps per block": int(1.5e6),
        "simulation point": {
            0.31: 9200,
            0.314: 9894,
            0.319: 5784,
            0.323: 6224,
            0.328: 3936,
            0.332: 4971,
            0.337: 6983,
            0.341: 672,
            0.346: 6819,
            0.35: 6636,
        },
    },
    120: {
        "initial state": "U",
        "number equilibration": int(1.0e8),
        "number of simulation sweeps": int(1.5e8),
        "number of sweeps per block": int(1.5e6),
        "simulation point": {
            0.3: 7976,
            0.304: 2828,
            0.309: 9951,
            0.313: 3972,
            0.318: 2650,
            0.322: 620,
            0.327: 2653,
            0.331: 3733,
            0.336: 3299,
            0.34: 1100,
        },
    },
}

ARGS_DYNM = {
    32: {
        "F": {
            "seed": {"single": 712, "line": 3730},
            "temperature minimum": 0.2,
            "temperature maximum": 0.5,
            "temperature step width": 0.01,
            "number of changing sweeps": int(1.0e5),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 50,
        },
        "U": {
            "seed": {"single": 3424, "line": 2309},
            "temperature minimum": 0.32,
            "temperature maximum": 0.61,
            "temperature step width": 0.01,
            "number of changing sweeps": int(5.0e6),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 4,
        },
    },
    64: {
        "F": {
            "seed": {"single": 4323, "line": 9761},
            "temperature minimum": 0.2,
            "temperature maximum": 0.5,
            "temperature step width": 0.01,
            "number of changing sweeps": int(1.0e5),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 50,
        },
        "U": {
            "seed": {"single": 7533, "line": 1837},
            "temperature minimum": 0.32,
            "temperature maximum": 0.61,
            "temperature step width": 0.01,
            "number of changing sweeps": int(5.0e6),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 4,
        },
    },
    128: {
        "F": {
            "seed": {"single": 6577, "line": 1373},
            "temperature minimum": 0.2,
            "temperature maximum": 0.5,
            "temperature step width": 0.01,
            "number of changing sweeps": int(1.0e5),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 50,
        },
        "U": {
            "seed": {"single": 4116, "line": 6918},
            "temperature minimum": 0.3,
            "temperature maximum": 0.6,
            "temperature step width": 0.01,
            "number of changing sweeps": int(5.0e6),
            "number of simulation sweeps": int(1.0e5),
            "number of repetitions of dependent run": 4,
        },
    },
}


class BinaryExecutionError(RuntimeError):
    pass


def _run_binary(cwd: Path, binary: str, args: list) -> str:
    cmd = " ".join([binary] + list(map(str, args)))
    result = subprocess.run(
        cmd,
        cwd=cwd,
        shell=True,
        text=True,
    )

    rc = result.returncode
    if rc > 0:
        raise BinaryExecutionError(
            f"Binary '{binary}' failed with exit code {rc}\n"
            f"Command: {cmd}\n"
            f"--- stderr ---\n{result.stderr}\n"
            f"--- stdout ---\n{result.stdout}"
        )
    elif rc < 0:
        name = SIGNAL_NAMES.get(rc, f"exit code {rc}")
        raise BinaryExecutionError(
            f"Binary: '{binary}' crashed with {name}\n" f"Command: {cmd}\n"
        )


def run_dynamical_simulation(
    lattice_length: int,
    algorithm: Literal["single", "line"],
    initial_state: Literal["F", "U"],
    output_directory: str = None,
) -> None:
    """
    runs the dynamical simulation

    Parameters
    ----------
        `lattice_length`: `int`
            Simulations points are deposed for the lattice lengths 32, 64, 128. For other
            you have to compile and run manually the corresponding binaries.
        `algorithm`: `"single"` or `"line"`
            - `"single"`: metropolis
            - `"line"`: metropolis + line-update rule
        `initial_state`: `"F"` or `"U"`
            - `"F"`: ferromagnetic initial state
            - `"U"`: uniformly distributed initial state
        `output_directory`: `str` (absolute or relative path)
            Directory where the raw simulation data is stored. Default
            `data/raw/dynm/`

    Notes
    -----
    The simulation binaries stores the simulated data with an output
    directory structure `<output_directory>/L<lattice_length>-U/T<1000*temperature>/`
    containing
    - `acceptance.txt`: Rate-sweeps*acceptance
    - `T*.txt`         : Spin-correlation
    """

    if lattice_length not in ARGS_DYNM:
        raise ValueError(
            f"No simulation parameters are deposited, for lattice length"
            f"'{lattice_length}'."
        )
    elif initial_state not in ARGS_DYNM[lattice_length]:
        raise ValueError(
            f"No simulation parameters are deposited, for initial state"
            f"'{initial_state}'."
        )
    elif algorithm not in ("single", "line"):
        raise ValueError(
            f"For 'algorithm' parameter you have to pass 'single' or 'line' not "
            f"'{algorithm}'."
        )
    else:
        args = ARGS_DYNM[lattice_length][initial_state]

    if output_directory is not None:
        path = Path(__file__).parent.parent / Path(output_directory)
        if not path.is_dir():
            raise ValueError(f"Output directory '{output_directory}' does not exists.")
        else:
            output_directory = (
                path if not path.is_absolute() else path.absolute()
            ).resolve()
    else:
        output_directory = Path(__file__).parent.parent.parent / "data/raw/dynm"

    print(f"Storing simulation data in '{output_directory}'...")
    seed = args["seed"][algorithm]
    temp_min = args["temperature minimum"]
    temp_max = args["temperature maximum"]
    temp_step = args["temperature step width"]
    n_chan = args["number of changing sweeps"]
    n_simu = args["number of simulation sweeps"]
    n_repe = args["number of repetitions of dependent run"]

    _run_binary(
        cwd=Path(__file__).parent.parent.parent / "bin",
        binary=f"./dgen{lattice_length}{algorithm}-0.5",
        args=[
            seed,
            temp_min,
            temp_max,
            temp_step,
            initial_state,
            n_chan,
            n_simu,
            n_repe,
            output_directory,
        ],
    )


def run_dynamical_analysis(
    target_directory: str = None, plot_fits_for_relaxation_time: bool = False
) -> None:
    """
    runs the data analysis function for the dynamical treatment

    Parameters
    ----------
        `target_directory`: `str` (absolute or relative path)
            Directory where the raw simulation data is stored of the dynamical
            treatment, (default `data/raw/dynm/`)
        `plot_fits_for_relaxation_time`: `bool`
            If `True` a multi plot is generated containing via gnuplot containing
            the exponentially decaying timeseries (order parameter) and its fits,
            needed for the determination of the relaxation time

    Notes
    -----
    The used analysis function for the dynamical treatment are defined in
    1) `src/dynm/correlation_function.py`
        - collects the correlation as function of the temperature (high temperature
          quench)
        - stores them into `<target_directory>/L*-F-*/autot*.txt`
    2) `src/dynm/relaxation_time.py`
        - computes the relaxation time as function of the temperature (low temperature
          quench)
        - since the determination of the relaxation time uses ranged least square fits
          of the exponentially decaying timeseries (order parameter), you may want plot
          these (set `plot_fits_for_relaxation_time=True`)
        - stores relaxation times into `<target_directory>/L*-U-*/relax.txt`, (optional)
          generates plots of the fits `<target_directory>/L*-U-*/plot.png` via gnuplot
    3) `src/dynm/fit_relaxation_time.py`
        - fits of the relaxation time as function of the temperature to determine the
          glassy transition temperature (low temperature quench)
        - writes the fit results into `fit_dynm.log`
    """
    if target_directory is not None:
        path = Path(__file__).parent.parent / Path(target_directory)
        if not path.is_dir():
            raise ValueError(f"Output directory '{target_directory}' does not exists.")
        else:
            target_directory = (
                path if not path.is_absolute() else path.absolute()
            ).resolve()
    else:
        target_directory = Path(__file__).parent.parent.parent / "data/raw/dynm"

    print(f"Loading simulation data from '{target_directory}'...")

    print(f"Collecting correlation for high temperature quench...")
    collect_correlation_function(target_directory)

    print(f"Computing relaxation times for low temperature quench...")
    compute_relaxation_times(
        target_directory,
        temperature_ranges={
            key: (
                value["U"]["temperature minimum"],
                value["U"]["temperature maximum"],
            )
            for key, value in ARGS_DYNM.items()
        },
        generate_plot=plot_fits_for_relaxation_time,
    )

    print(f"Fitting glassy temperature for the low temperature quench...")
    fit_glassy_temperature(target_directory, fit_log_append=False)

    print(f"Finished data analysis for the dynamical treatment.")


def run_equilibrium_simulation(
    lattice_length: int, output_directory: str = None
) -> None:
    """
    runs the equilibrium simulation (metropolis + line-update)

    Parameters
    ----------
        `lattice_length`: `int`
            Simulations points are deposed for the lattice lengths 30, 40, 50, 60, 70,
            80, 90, 100, 110, 120. For other you have to compile and run the
            corresponding binaries.
        `output_directory`: `str` (absolute or relative path)
            Directory where the raw simulation data is stored. Default
            `data/raw/equi/`

    Notes
    -----
    The simulation binaries stores the
    simulated data with an output directory structure
    `<output_directory>/L<lattice_length>-U/T<1000*temperature>/` containing
    - `entire.txt`     : full histogram over all sweeps
    - `block_*.txt`    : histogram for each block
    - `save.txt`       : save-point of the system and parameters
    """

    if lattice_length not in ARGS_EQUI:
        raise ValueError(
            f"No simulation parameters are deposited, for lattice length"
            f"'{lattice_length}'."
        )
    else:
        args = ARGS_EQUI[lattice_length]

    if output_directory is not None:
        path = Path(__file__).parent.parent / Path(output_directory)
        if not path.is_dir():
            raise ValueError(f"Output directory '{output_directory}' does not exists.")
        else:
            output_directory = (
                path if not path.is_absolute() else path.absolute()
            ).resolve()
    else:
        output_directory = Path(__file__).parent.parent.parent / "data/raw/equi"

    print(f"Storing simulation data in '{output_directory}'...")

    state = args["initial state"]
    n_equi = args["number equilibration"]
    n_simu = args["number of simulation sweeps"]
    n_jack = args["number of sweeps per block"]
    for temperature, seed in args["simulation point"].items():
        _run_binary(
            cwd=Path(__file__).parent.parent.parent / "bin",
            binary=f"./egen{lattice_length}line-0.5",
            args=[seed, temperature, state, n_equi, n_simu, n_jack, output_directory],
        )


def run_equilibrium_analysis(target_directory: str = None):
    """
    runs the data analysis function for the equilibrium treatment

    Parameters
    ----------
        `target_directory`: `str` (absolute or relative path)
            Directory where the raw simulation data is stored of the equilibrium
            treatment, (default `data/raw/equi/`)
    Notes
    -----
    The used data analysis binaries und functions are
    1) `bin/mean`
        - computes the means and errors (Jackknife analysis) of all measured
          observables, i.e. energy ferromagnetic/super-antiferromagnetic orderparameter,
          heat, ferromagnetic/super-antiferromagnetic susceptibility, as a function
          of the temperature
        - stores these functions into `<target_directory>/L*-U/mean.txt`
    2) `bin/wham`
        - uses multi-histogram reweighing to obtain smooth curves for the energy
          ferromagnetic/super-antiferromagnetic orderparameter, heat,
          ferromagnetic/super-antiferromagnetic susceptibility, as a function of the
          temperature
        - stores them into `<target_directory>/L*-U/wham.txt`
    3) `bin/peak`
        - uses multi-histogram reweighing to determine the heat-peak location per
          jackknife block an computes its mean and error (jackknife analysis) as
          function of the lattice length
        - stores them into `<target_directory>/fit.txt`
    4) `src/equi/fit_heat_peak.py`
        - fits of the heat-peaks temperatures as function of the lattice length to
          obtain a universell law
        - writes the fit results into `fit_equi.log`
    """
    if target_directory is not None:
        path = Path(__file__).parent.parent / Path(target_directory)
        if not path.is_dir():
            raise ValueError(f"Output directory '{target_directory}' does not exists.")
        else:
            target_directory = (
                path if not path.is_absolute() else path.absolute()
            ).resolve()
    else:
        target_directory = Path(__file__).parent.parent.parent / "data/raw/equi"

    print(f"Loading simulation data from '{target_directory}'...")

    print(f"Computing means and errors for observables...")
    for lattice_length, args in ARGS_EQUI.items():
        _run_binary(
            cwd=Path(__file__).parent.parent.parent / "bin",
            binary=f"./mean",
            args=[
                target_directory / f"L{lattice_length}-{args["initial state"]}",
                target_directory
                / f"L{lattice_length}-{args["initial state"]}/mean.txt",
            ],
        )

    print(f"Obtaining smooth curves for observables...")
    for lattice_length, args in ARGS_EQUI.items():
        _run_binary(
            cwd=Path(__file__).parent.parent.parent / "bin",
            binary=f"./wham",
            args=[
                target_directory / f"L{lattice_length}-{args["initial state"]}",
                target_directory
                / f"L{lattice_length}-{args["initial state"]}/wham.txt",
                min(args["simulation point"]),
                max(args["simulation point"]),
                400,
            ],
        )

    print(f"Determining heat-peak location as function of the lattice length...")
    for lattice_length, args in ARGS_EQUI.items():
        _run_binary(
            cwd=Path(__file__).parent.parent.parent / "bin",
            binary=f"./peak",
            args=[
                target_directory / f"L{lattice_length}-{args["initial state"]}",
                target_directory / f"fit.txt",
                int(
                    args["number of simulation sweeps"]
                    / args["number of sweeps per block"]
                ),
                min(args["simulation point"]),
                max(args["simulation point"]),
                800,
            ],
        )

    print(
        f"Fitting universell law to heat-peaks temperatures as function of the lattice "
        f"length..."
    )
    fit_universell_law(target_directory, fit_log_append=False)

    print(f"Finished data analysis for the dynamical treatment.")

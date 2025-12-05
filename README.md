This repository contains my Bachelor thesis *Ising model on a square lattice with competing nearest and next-nearest neighbor interactions*. The `pdf`-file [`thesis.pdf`](thesis.pdf) is the manuscript at the time of my submission. After my submission, I revised the repository (I know super nerdy), for better data reproduction. So the Appendix sections A1 und B1 in the manuscript are not up to date, better use this `README` for data reproduction.

```
repository
|--bin/             # target directory for binaries of the simulation
|--data/ 
|  |--plots/        # used data in the manuscript
|  |--raw/          # output of simulation binaries
|--latex/           # latex code of the manuscript
|--sandbox/         # playground for development
|--src/             
|  |--dynm/         # source code for simulation/analysis dynamic properties
|  |--equi/         # source code for simulation/analysis equilibrium properties
|  |--tests/        # some reference data for development
|--requirements.txt # python requirements
|--thesis.pdf       # manuscript
```

# Dependencies

## System requirements
- C++ compiler (`g++`)
- GNU Make (`make`)
- gnuplot
- Python 3.12

## Python packages
- `numpy`
- `scipy`
- `gvar`

~~~sh
pip install -r "requirements.txt"
~~~

# Data generation instructions

## Compiling 

Go to the directory `src/` and hit `make` in the cli. It will compile all needed binaries and store them into `bin/`.

## Generating raw data

Use [`src/simulation.py`](src/simulation.py) and the following python-functions,they will generate the raw data needed for the following data analysis

### `helper.run_equilibrium_simulation`
---------------------------------------
runs the dynamical simulation.

#### *Parameters:*
- `lattice_length`: `int`
    - Simulations points are deposed for the lattice lengths 32, 64, 128. For other you have to compile and run manually the corresponding binaries.
- `algorithm`: `"single"` or `"line"`
    - `"single"`: metropolis
    - `"line"`: metropolis + line-update rule
- `initial_state`: `"F"` or `"U"`
    - `"F"`: ferromagnetic initial state
    - `"U"`: uniformly distributed initial state
- `output_directory`: `str` (absolute or relative path)
    -  Directory where the raw simulation data is stored. Default `data/raw/dynm/`

#### *Notes:*
The simulation binaries stores the simulated data with an output directory structure `<output_directory>/L<lattice_length>-U/T<1000*temperature>/` containing
- `acceptance.txt`: Rate-sweeps*acceptance
- `T*.txt`         : Spin-correlation

### `helper.run_dynamical_simulation`
-------------------------------------
runs the equilibrium simulation (metropolis + line-update)

#### *Parameters:*
- `lattice_length`: `int`
    - Simulations points are deposed for the lattice lengths 30, 40, 50, 60, 70, 80, 90, 100, 110, 120. For other you have to compile and run the corresponding binaries.
- `output_directory`: `str` (absolute or relative path)
    - Directory where the raw simulation data is stored. Default `data/raw/equi/`

#### *Notes:*
The simulation binaries stores the simulated data with an output directory structure `<output_directory>/L<lattice_length>-U/T<1000*temperature>/` containing
- `entire.txt`     : full histogram over all sweeps
- `block_*.txt`    : histogram for each block
- `save.txt`       : save-point of the system and parameters


## Data Analysis

It is crucial that the simulated systems. i.e lattice length, initial states and simulation algorithms, matches with the systems deposed in the [dictionaries](src/helper/running.py) `ARGS_EQUI` and `ARGS_DYNM`, because the following data analysis functions highly depend on these dictionaries. 

If you want simulate other systems, you have to do the data analysis manually or add the wanted systems to the dictionaries and of course generate the simulation data with the functions `run_equilibrium_simulation` and `run_dynamical_simulation`.

Use [`src/analysis.py`](src/analysis.py) and the following python-functions,they will generate the finial data.

### `helper.run_dynamical_analysis` (dynamical treatment)
---------------------------------------------------------
runs the data analysis function for the dynamical treatment

#### *Parameters:*
- `target_directory`: `str` (absolute or relative path)
    - Directory where the raw simulation data is stored of the dynamical treatment, (default `data/raw/dynm/`)
- `plot_fits_for_relaxation_time`: `bool`
    - If `True` a multi plot is generated containing via gnuplot containing the exponentially decaying timeseries (order parameter) and its fits, needed for the determination of the relaxation time

#### *Notes:*
The used analysis function for the dynamical treatment are defined in
1) `src/dynm/correlation_function.py`
    - collects the correlation as function of the temperature (high temperature quench)
    - stores them into `<target_directory>/L*-F-*/autot*.txt`
2) `src/dynm/relaxation_time.py`
    - computes the relaxation time as function of the temperature (low temperature quench)
    - since the determination of the relaxation time uses ranged least square fits of the exponentially decaying timeseries (order parameter), you may want plot these (set `plot_fits_for_relaxation_time=True`)
    - stores relaxation times into `<target_directory>/L*-U-*/relax.txt`, (optional) generates plots of the fits `<target_directory>/L*-U-*/plot.png` via gnuplot
3) `src/dynm/fit_relaxation_time.py`
    - fits of the relaxation time as function of the temperature to determine the glassy transition temperature (low temperature quench)
    - writes the fit results into `fit_dynm.log`


### `run_equilibrium_analysis` (equilibrium treatment)
------------------------------------------------------
runs the data analysis function for the equilibrium treatment

#### *Parameters:*
- `target_directory`: `str` (absolute or relative path)
    - Directory where the raw simulation data is stored of the equilibrium treatment, (default `data/raw/equi/`)

#### *Notes:*
The used data analysis binaries und functions are
1) `bin/mean`
    - computes the means and errors (Jackknife analysis) of all measured observables, i.e. energy ferromagnetic/super-antiferromagnetic orderparameter, heat, ferromagnetic super-antiferromagnetic susceptibility, as a function of the temperature
    - stores these functions into `<target_directory>/L*-U/mean.txt`
2) `bin/wham`
    - uses multi-histogram reweighing to obtain smooth curves for the energy ferromagnetic/super-antiferromagnetic orderparameter, heat, ferromagnetic/super-antiferromagnetic susceptibility, as a function of the temperature
    - stores them into `<target_directory>/L*-U/wham.txt`
3) `bin/peak`
    - uses multi-histogram reweighing to determine the heat-peak location per jackknife block an computes its mean and error (jackknife analysis) as function of the lattice length
    - stores them into `<target_directory>/fit.txt`
4) `src/equi/fit_heat_peak.py`
    - fits of the heat-peaks temperatures as function of the lattice length to obtain a universell law
    - writes the fit results into `fit_equi.log`

# Used data

All `txt`-files containing the data used in manuscript have a `<prefix>` of the following scheme `L<length>-<state>-<algorithm>-*.txt` 
- `<length>`: lattice length of the system
- `<state>`: initial state
    - `F` for ferromagnetic
    - `U` for uniformly distributed
- `<algorithm>`: simulation algorithm
    - `single`: metropolis
    - `line`: metropolis + line-update rule 


## [`data/plots/dynm/`](data/plots/dynm/)

- `<prefix>-autot*.txt`
    ~~~
    [temperature] [ferro. autocorrelation] [error] [horiz. autocorrelation] [error] [verti. autocorrelation] [error]
    ~~~
    > Figures 4.4 and 4.9


- `<prefix>-acceptance.txt`
    ~~~
    [temperature] [single-spin-flip probability] [error] [line-spin-flip probability] [error]
    ~~~
    > Figures 4.5, 4.9 and 4.11


- `<prefix>-relax.txt`
    ~~~
    [temperature] [ferro. relaxation time] [error] [horiz. relaxation time] [error] [verti. relaxation time] [error]
    ~~~
    > Figures 4.6, 4.10 and 4.11

## [`data/plots/equi/`](data/plots/equi/)

- `<prefix>-mean.txt`
    ~~~
    [temperature] [energy] [error] [heat] [error] [ferro. magnetization] [error] [ferro. susceptibility] [error] [super-antiferro. magnetization] [error] [super-anti-ferro. susceptibility] [error]
    ~~~
    > Figures 4.1, 4.2 and 4.8


- `<prefix>-wham.txt`
    ~~~
    [temperature] [energy] [heat] [ferro. magnetization] [ferro. susceptibility] [super-antiferro. magnetization] [super-anti-ferro. susceptibility]
    ~~~
    > Figures 4.1, 4.2 and 4.8


- `fit.txt`
    ~~~
    [lattice length] [peak temperature] [error] [peak heat] [error]
    ~~~
    > Figure 4.7



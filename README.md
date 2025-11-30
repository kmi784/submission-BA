# Submission Bachelor Thesis 

This repository contains my Bachelor thesis *Ising model on a square lattice with competing nearest and next-nearest neighbor interactions*. The `pdf`-file [`thesis.pdf`](thesis.pdf) is the manuscript at the time of my submission. After my submission, I revised the repository (I know super nerdy), for better data reproduction. So the Appendix sections A1 und B1 in the manuscript are not up to date, better use this `README` for data reproduction.

```sh
repo
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

## Dependencies

### System requirements
- C++ compiler (`g++`)
- GNU Make (`make`)
- gnuplot
- Python 3.10+

### Python packages
- `numpy`
- `scipy`
- `gvar`

~~~sh
pip install -r "requirements.txt"
~~~

## Data generation instructions

### Compiling 

Go to the directory `src/` and hit `make` in the cli. It will compile all needed binaries and store them into `bin/`.

### Generating raw data

Use `src/simulation.py` and the functions
~~~py
def run_equilibrium_simulation(
    lattice_length: int, output_directory: str = None
) 
    pass

def run_dynamical_simulation(
    lattice_length: int, 
    algorithm: Literal["single", "line"],
    initial_state: Literal["F", "U"],
    output_directory: str = None
) -> None:
    pass
~~~
from the `running`-module. It will generate the raw data needed for 
the following data analysis.

### Data Analysis

#### Dynamical treatment



#### Equilibrium treatment



## Used data

All `txt`-files containing the used data have a `<prefix>` of the following scheme `L<length>-<state>-<algorithm>-*.txt` 
- `<length>`: lattice length of the system
- `<state>`: initial state
    - `F` for ferromagnetic
    <!--- `H` for horizontal stripped
    - `V` for vertical stripped-->
    - `U` for uniformly distributed
- `<algorithm>`: simulation algorithm
    - `single`: metropolis
    - `line`: metropolis + line-update rule 


### [`data/plots/dynm/`](data/plots/dynm/)

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

### [`data/plots/equi/`](data/plots/equi/)

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



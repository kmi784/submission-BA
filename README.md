## Dependencies

### System requirements
- c/c++ compiler (`gcc` and `g++`)
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



## Used data


> **!Attention** The file`<name>-L<length>-<state>-<algorithm>.txt` contains the data of the system with lattice length `<length>`, initial state `<state>` (`F` for ferromagnetic, `U` for uniformly distributed) and the used simulation algorithm `<algorithm>` (`line`, `single`)

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



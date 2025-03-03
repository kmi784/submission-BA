# Used data

> **!Attention** The file`<name>-L<length>-<state>-<algorithm>.txt` contains the data of the system with lattice length `<length>`, initial state `<state>` (`F` for ferromagnetic, `U` for uniformly distributed) and the used simulation algorithm `<algorithm>` (`line`, `single`)

## `plots/equi/`

- `mean-*.txt`
    ~~~
    [temperature] [energy] [error] [heat] [error] [ferro. magnetization] [error] [ferro. susceptibility] [error] [super-antiferro. magnetization] [error] [super-anti-ferro. susceptibility] [error]
    ~~~
    > Figure 4.1, 4.2 and 4.8


- `wham-*txt`
    ~~~
    [temperature] [energy] [heat] [ferro. magnetization] [ferro. susceptibility] [super-antiferro. magnetization] [super-anti-ferro. susceptibility]
    ~~~
    > Figure 4.1, 4.2 and 4.8


- `fit.txt`
    ~~~
    [lattice length] [peak temperature] [error] [peak heat] [error]
    ~~~
    > Figure 4.7


## `plots/dynm/`

- `autot*.txt`
    ~~~
    [temperature] [ferro. autocorrelation] [error] [horiz. autocorrelation] [error] [verti. autocorrelation] [error]
    ~~~
    > Figure 4.4, 4.9


- `acceptance-*.txt`
    ~~~
    [temperature] [single-spin-flip probability] [error] [line-spin-flip probability] [error]
    ~~~
    > Figure 4.5, 4.9, 4.11


- `relax-*.txt`
    ~~~
    [temperature] [ferro. relaxation time] [error] [horiz. relaxation time] [error] [verti. relaxation time] [error]
    ~~~
    > Figure 4.6, 4.10, 4.11
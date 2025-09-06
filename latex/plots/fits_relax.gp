#*************** Settings ***************
load "include.gp"
@eps; @setout
#****************************************

path = '../../data/plots/dynm/'
single = '-U-single-relax.txt'

set multiplot 
set key columns 3 samplen 1 at screen 0.99,0.99 width 0.5 box spacing 1.3

set ylabel '$\ln(\tau_{(\cdot)})$'
set yrange[4.7:13]; set ytics 5, 2, 13;
set xrange[-3:-1]; set xtics -2.8, 0.5, -1.2


power(x) = Ap*(x-Tg)**(-rho)
vogel(x) = Av*exp(c/(x-T0))


set bmargin at screen  0.15; set tmargin at screen  0.82




Ap = 3.6720519700735244
Tg = 0.25452497004595265
rho = 3.8192340623446106
Av = 4.095321690463054
T0 = 0.13498611439349972
c = 1.9083115095426404
set lmargin at screen  0.1; set rmargin at screen  0.38
unset xlabel
plot NaN w boxes fs solid   lc 14       t '$L\!=\!128$' \
    ,NaN w p                lc -1 pt 4  t 'ferromagnetic' \
    ,NaN w lines            lc -1       t 'power law' \
    ,NaN w p                lc -1 pt 6  t 'horizontal striped'\
    ,NaN w lines            lc -1 dt 4  t 'Fulcher-Vogel law' \
    ,NaN w p                lc -1 pt 8  t 'vertical striped' \
    ,path.'L128'.single  u (log($1-Tg)):(log($2)):($3/$2)     w yerrorbars   lc 14 pt 4      notitle \
    ,log(power(exp(x)+Tg)) lc -1 notitle, log(vogel(exp(x)+Tg)) lc -1 dt 4 notitle


Ap = 3.359216209191668
Tg = 0.2530036707840112
rho = 3.8968074818748444
Av = 3.5668017715705242
T0 = 0.13123949716291466
c = 1.9790043209124895
set lmargin at screen  0.4; set rmargin at screen  0.68
set xlabel '$\ln(T\!-\!T_g)$'; unset ylabel; set format y ""
plot path.'L128'.single  u (log($1-Tg)):(log($4)):($5/$4)     w yerrorbars   lc 14 pt 6      notitle \
    ,log(power(exp(x)+Tg)) lc -1 notitle, log(vogel(exp(x)+Tg)) lc -1 dt 4 notitle


Ap = 3.3169506686753136
Tg = 0.2525538559228552
rho = 3.9105932493568103
Av = 3.535243829987879
T0 = 0.13094157226466674
c = 1.9838006086379507
set lmargin at screen  0.70; set rmargin at screen  0.98
unset xlabel; unset ylabel; set format y ""
plot path.'L128'.single  u (log($1-Tg)):(log($6)):($7/$6)     w yerrorbars   lc 14 pt 8      notitle \
    ,log(power(exp(x)+Tg)) lc -1 notitle, log(vogel(exp(x)+Tg)) lc -1 dt 4 notitle


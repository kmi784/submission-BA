#*************** Settings ***************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6cm color standalone font 8
#****************************************




file = '../../data/plots/equi/fit.txt'
power(x) = A*x**rho
expon(x) = A/log(x/L0)

set multiplot 
set key columns 3 samplen 2 at screen 0.905,1.0 width 0 box spacing 1.3
set bmargin at screen  0.15; set tmargin at screen  0.9




set lmargin at screen  0.15; set rmargin at screen  0.48


set xrange[-4.84:-3.35]; set xtics -4.7, 0.4, -3.5
set yrange[-1.15:-0.83]; set ytics -1.15, 0.05, -0.85
A = 0.838242214074709
rho = -0.20202891111125287



set ylabel '$\ln(T_\mathrm{max})$'; set xlabel '$\ln(1/L)$'
plot file u (log(1/$1)):(log($2)):($3/$2)   w yerrorbars   lc -1   t '$(L,T_\mathrm{max})$' \
    ,log(power(exp(-x)))                                    lc -1   t 'power law' \
    ,NaN w lines dt 2                                       lc -1   t 'logarithmic law' 




set lmargin at screen  0.52; set rmargin at screen  0.85
unset ylabel; unset ytics; set y2tics mirror


set xrange[0.175:0.255]; set xtics 0.19, 0.02, 0.25
set y2range[0.31:0.435]; set y2tics 0.32, 0.02, 0.42
A = 1.7608911449161793
L0 = 0.4853338877893009

set y2label '$T_\mathrm{max}$'; set xlabel '$\ln(L/L_0)^{-1}$'
plot file u (1/log($1/L0)):2:3 axes x1y2 w yerrorbars   lc -1   notitle \
    ,expon(L0*exp(1/x))  axes x1y2                      lc -1 dt 2  notitle 
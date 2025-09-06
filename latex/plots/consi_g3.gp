#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,8.5cm color standalone font 8
#**********************************************************************


path = '../../data/plots/equi/'
mean = '-U_g3-mean.txt'
wham = '-U_g3-wham.txt'
theo = '-U_g3-kalz.txt'


set multiplot 
set key columns 4 samplen 2 at screen 0.99,0.99 width 0 box spacing 1.3
set xrange[1.08:1.42]; set xtics 1.1, 0.1, 1.4 



set lmargin at screen  0.15; set rmargin at screen  0.48


set bmargin at screen  0.54; set tmargin at screen  0.92

set yrange[-1.35:-0.9]; set ytics -1.3, 0.1, -0.9
set ylabel '$E/N$'; set format x "";
plot path.'L50'.mean    u 1:2:3     w yerrorbars    lc 3    t '$L\!=\!50$' \
    ,path.'L50'.wham    u 1:2       w lines         lc 3    notitle        \
    ,path.'L80'.mean    u 1:2:3     w yerrorbars    lc 6    t '$L\!=\!80$' \
    ,path.'L80'.wham    u 1:2       w lines         lc 6    notitle        \
    ,path.'L100'.mean   u 1:2:3     w yerrorbars    lc 8    t '$L\!=\!100$'\
    ,path.'L100'.wham   u 1:2       w lines         lc 8    notitle        \
    ,NaN w lines lc -1 dt 2 t 'referenz data'           


set bmargin at screen  0.12; set tmargin at screen  0.5

set yrange[0:1]; set ytics 0, 0.2, 1
set ylabel '$M/N$'; set format x; set xlabel '$T$'
plot path.'L50'.mean    u 1:6:7     w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:4       w lines         lc 3    notitle \
    ,path.'L80'.mean    u 1:6:7     w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:4       w lines         lc 6    notitle \
    ,path.'L100'.mean   u 1:6:7     w yerrorbars    lc 8    notitle \
    ,path.'L100'.wham   u 1:4       w lines         lc 8    notitle   





set lmargin at screen  0.52; set rmargin at screen  0.85
unset ylabel; unset ytics; set y2tics mirror


set bmargin at screen  0.54; set tmargin at screen  0.92

set y2range[0.4:2.6]; set y2tics 0.5, 0.5, 2.5
set y2label '$c_V$'; set format x ""; unset xlabel
plot path.'L50'.mean    u 1:4:5     axes x1y2   w yerrorbars    lc 3        notitle \
    ,path.'L50'.wham    u 1:3       axes x1y2   w lines         lc 3        notitle \
    ,path.'L50'.theo    u 1:2       axes x1y2   w lines         lc -1 dt 2  notitle \
    ,path.'L80'.mean    u 1:4:5     axes x1y2   w yerrorbars    lc 6        notitle \
    ,path.'L80'.wham    u 1:3       axes x1y2   w lines         lc 6        notitle \
    ,path.'L80'.theo    u 1:2       axes x1y2   w lines         lc -1 dt 2  notitle \
    ,path.'L100'.mean   u 1:4:5     axes x1y2   w yerrorbars    lc 8        notitle \
    ,path.'L100'.wham   u 1:3       axes x1y2   w lines         lc 8        notitle \
    ,path.'L100'.theo   u 1:2       axes x1y2   w lines         lc -1 dt 2  notitle   



set bmargin at screen  0.12; set tmargin at screen  0.5

set y2range[0:330]; set y2tics 0, 50, 300
set y2label '$\chi$'; set format x; set xlabel '$T$'
plot path.'L50'.mean    u 1:8:9     axes x1y2   w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:5       axes x1y2   w lines         lc 3    notitle \
    ,path.'L80'.mean    u 1:8:9     axes x1y2   w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:5       axes x1y2   w lines         lc 6    notitle \
    ,path.'L100'.mean   u 1:8:9     axes x1y2   w yerrorbars    lc 8    notitle \
    ,path.'L100'.wham   u 1:5       axes x1y2   w lines         lc 8    notitle    
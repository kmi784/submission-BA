#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,8.5cm color standalone font 8
#**********************************************************************


path = '../../data/kalz/'
mean = '-U_g6/mean.txt'
wham = '-U_g6/wham.txt'
theo = '-U_g6/kalz.txt'


set multiplot 
set key columns 4 samplen 2 at screen 0.99,0.99 width 0 box spacing 1.3
set xrange[0.935:1.045]; set xtics 0.94, 0.02, 1.04 



set lmargin at screen  0.15; set rmargin at screen  0.48


set bmargin at screen  0.54; set tmargin at screen  0.92

set yrange[-1.1:-0.8]; set ytics -1.1, 0.1, -0.8
set ylabel '$E/N$'; set format x "";
plot path.'L50'.mean    u 1:2:3     w yerrorbars    lc 3    t '$L\!=\!50$' \
    ,path.'L50'.wham    u 1:2       w lines         lc 3    notitle        \
    ,path.'L80'.mean    u 1:2:3     w yerrorbars    lc 6    t '$L\!=\!80$' \
    ,path.'L80'.wham    u 1:2       w lines         lc 6    notitle        \
    ,path.'L100'.mean   u 1:2:3     w yerrorbars    lc 8    t '$L\!=\!100$'\
    ,path.'L100'.wham   u 1:2       w lines         lc 8    notitle        \
    ,NaN w lines lc -1 dt 2 t 'referenz data'           


set bmargin at screen  0.12; set tmargin at screen  0.5

set yrange[0:0.95]; set ytics 0, 0.2, 1
set ylabel '$M_s/N$'; set format x; set xlabel '$T$'
plot path.'L50'.mean    u 1:10:11     w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:6         w lines         lc 3    notitle \
    ,path.'L80'.mean    u 1:10:11     w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:6         w lines         lc 6    notitle \
    ,path.'L100'.mean   u 1:10:11     w yerrorbars    lc 8    notitle \
    ,path.'L100'.wham   u 1:6         w lines         lc 8    notitle   





set lmargin at screen  0.52; set rmargin at screen  0.85
unset ylabel; unset ytics; set y2tics mirror


set bmargin at screen  0.54; set tmargin at screen  0.92

set y2range[0:20]; set y2tics 0, 4, 20
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

set y2range[0:600]; set y2tics 0, 100, 600
set y2label '$\chi_s$'; set format x; set xlabel '$T$'
plot path.'L50'.mean    u 1:12:13   axes x1y2   w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:7       axes x1y2   w lines         lc 3    notitle \
    ,path.'L80'.mean    u 1:13:13   axes x1y2   w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:7       axes x1y2   w lines         lc 6    notitle \
    ,path.'L100'.mean   u 1:12:13   axes x1y2   w yerrorbars    lc 8    notitle \
    ,path.'L100'.wham   u 1:7       axes x1y2   w lines         lc 8    notitle    



#*************** Settings ***************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6cm color standalone font 8
#****************************************

path = '../../data/plots/dynm/'
line = '-U-line-relax.txt'
single = '-U-single-relax.txt'

set key columns 3 samplen 1 at screen 0.99,0.99 width 0.5 box spacing 1.3


set xrange[0.3:0.61]; set xtics 0.31, 0.04, 0.61
set lmargin at screen  0.15; set rmargin at screen  0.95



set yrange[0:250000]; set ytics 0, 50000, 250000; set ylabel '$\tau$'
set format x; set xlabel '$T$'
set bmargin at screen  0.12; set tmargin at screen  0.82
plot NaN w p                lc -1 pt 4  t 'ferromagnetic' \
    ,NaN w lines            lc -1       t 'single spin up.' \
    ,NaN w p                lc -1 pt 6  t 'horizontal striped'\
    ,NaN w lines            lc -1 dt 4  t 'line spin up.' \
    ,NaN w p                lc -1 pt 8  t 'vertical striped' \
    ,path.'L128'.single  u 1:2:3     w yerrorlines   lc 14 pt 4      notitle \
    ,path.'L128'.single  u 1:4:5     w yerrorlines   lc 14 pt 6      notitle \
    ,path.'L128'.single  u 1:6:7     w yerrorlines   lc 14 pt 8      notitle \
    ,path.'L128'.line    u 1:2:3     w yerrorlines   lc 14 pt 4 dt 4 notitle \
    ,path.'L128'.line    u 1:4:5     w yerrorlines   lc 14 pt 6 dt 4 notitle \
    ,path.'L128'.line    u 1:6:7     w yerrorlines   lc 14 pt 8 dt 4 notitle 


































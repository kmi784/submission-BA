#*************** Settings ***************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6.5cm color standalone font 8
#****************************************



path = '../../data/plots/dynm/'
accep = '-U-line-acceptance.txt' 
single = '-U-single-relax.txt'
line = '-U-line-relax.txt'



set key columns 3 samplen 1 at screen 0.99,0.99 width 0.5 box spacing 1.3
set bmargin at screen  0.12; set tmargin at screen  0.82


set xlabel '$T$'
set xrange[0.305:0.355]; set xtics 0.31, 0.01, 0.45; 


set ylabel '$\tau$'
set yrange[0:350000];set ytics nomirror; set ytics 0, 50000, 250000; 


set y2label '$\ln(r_\mathrm{a})$'
set y2range[-25:0]; set y2tics mirror; set y2tics nomirror; set y2tics -16, 3, -1




set arrow from 0.32, graph 0 to 0.32, graph 1 nohead lc 14 dt 2 


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
    ,path.'L128'.line    u 1:6:7     w yerrorlines   lc 14 pt 8 dt 4 notitle \
    ,path.'L128'.accep   u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines   lc -1 pt 0      notitle \
    ,path.'L128'.accep   u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines   lc -1 dt 4 pt 0 notitle     


#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,5cm color standalone font 8
#**********************************************************************


path = '../../data/plots/equi/'
mean = '-U-mean.txt'
wham = '-U-wham.txt'


set multiplot

set yrange[-0.5:2.5]; set ytics ('$T_1$' 0,'$T_2$' 1,'$T_3$' 2); set ylabel 'measurements'; 
set xrange[-1:19]; set xtics ('initial state'0,4,7,11,14,18); set format x ""; set xlabel "sweeps" offset 15.5
unset key 

set label 1 'low $T$' at screen 0.02,0.22; set label 2 'high $T$' at screen 0.02,0.9

set bmargin at screen  0.2; set tmargin at screen  0.9



set label 3 'warimg run' at graph 0.1, 0.9
set lmargin at screen  0.15; set rmargin at screen  0.53

set label 4 at 0.8,-0.25 ' $^{^{N_\mathrm{m}}}$'
set label 5 at 7.8,0.75 ' $^{^{N_\mathrm{m}}}$'
set label 6 at 14.8,1.75 ' $^{^{N_\mathrm{m}}}$'
set label 7 at 4.6, 0.15 ' $^{^{N_\mathrm{c}}}$'
set label 8 at 11.6, 1.15 ' $^{^{N_\mathrm{c}}}$'

set arrow from 0, graph 0 to 0, graph 1 nohead lc -1 dt 2 
set arrow from 4, graph 0 to 4, graph 1 nohead lc -1 dt 2 
set arrow from 7, graph 0 to 7, graph 1 nohead lc -1 dt 2 
set arrow from 11, graph 0 to 11, graph 1 nohead lc -1 dt 2 
set arrow from 14, graph 0 to 14, graph 1 nohead lc -1 dt 2 
set arrow from 18, graph 0 to 18, graph 1 nohead lc -1 dt 2 
plot '-' u 1:2 w lines lc -1 lw 2
        0 0
        4 0
        7 1
        11 1
        14 2
        18 2
EOF




set label 3 'cooling run' at graph 0.6, 0.9
set ytics 0, 1, 2; set format y ""; unset ylabel; unset xlabel
set lmargin at screen  0.57; set rmargin at screen  0.95
set label 4 at 0.8,1.75 ' $^{^{N_\mathrm{m}}}$'
set label 5 at 7.8,0.75 ' $^{^{N_\mathrm{m}}}$'
set label 6 at 14.8,-0.25 ' $^{^{N_\mathrm{m}}}$'
set label 7 at 4.6, 1.1 ' $^{^{N_\mathrm{c}}}$'
set label 8 at 11.6, 0.1 ' $^{^{N_\mathrm{c}}}$'


set arrow from 0, graph 0 to 0, graph 1 nohead lc -1 dt 2 
set arrow from 4, graph 0 to 4, graph 1 nohead lc -1 dt 2 
set arrow from 7, graph 0 to 7, graph 1 nohead lc -1 dt 2 
set arrow from 11, graph 0 to 11, graph 1 nohead lc -1 dt 2 
set arrow from 14, graph 0 to 14, graph 1 nohead lc -1 dt 2 
set arrow from 18, graph 0 to 18, graph 1 nohead lc -1 dt 2 
plot '-' u 1:2 w lines lc -1 lw 2
        0 2
        4 2
        7 1
        11 1
        14 0
        18 0
EOF
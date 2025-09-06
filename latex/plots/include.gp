#Enable macros (can be called with @eps for eps macro defined below)
set macros

eps="set terminal epslatex size 12.1cm,6cm color standalone font 8 header '\\usepackage{amsmath}'"

log="se log;set format x '$10^{%T}$';set format y '$10^{%T}$';set xlabel offset 0,0.9;set ylabel offset 1.5,0;set xtics offset 0,0.3;set ytics offset 0.8,0"

#this 'hack' will call the output file the same as this file (so we don't have to change this)
setout="set out ARG0[1:strstrt(ARG0,'.gp')].'tex'"

#Defining default colors
set pointintervalbox 0
set linetype 1 lc rgb '#e41a1c' pt 4
set linetype 2 lc rgb '#377eb8' pt 4
set linetype 3 lc rgb '#4daf4a' pt 4
set linetype 4 lc rgb '#D95F02' pt 4
set linetype 5 lc rgb '#1B9E77' pt 4
set linetype 6 lc rgb '#7570B3' pt 4
set linetype 7 lc rgb '#666666' pt 4
set linetype 8 lc rgb '#E6AB02' pt 4
set linetype 9 lc rgb '#A6761D' pt 4
set linetype 10 lc rgb '#66A61E' pt 4
set linetype 11 lc rgb '#E7298A' pt 4
set linetype 12 lc rgb '#880000' pt 4
set linetype 13 lc rgb '#2F2A5A' pt 4
set linetype 14 lc rgb '#426837' pt 4

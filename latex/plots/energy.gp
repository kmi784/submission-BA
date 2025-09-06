#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6.8cm color standalone font 8
#**********************************************************************


path = '../../data/plots/equi/'
mean = '-U-mean.txt'
wham = '-U-wham.txt'



set multiplot
set key columns 3 samplen 2 top left spacing 1
set xrange[0.295:0.505]

set lmargin at screen  0.15; set rmargin at screen  0.95

set yrange[-1:-0.92]; set ytics -1,0.02,-0.92
set ylabel '$E/N$'; unset xlabel; set format x ""
set bmargin at screen  0.565; set tmargin at screen  0.97
plot path.'L30'.mean    u 1:2:3     w yerrorbars    lc 1    t '$L\!=\!30$'  \
    ,path.'L30'.wham    u 1:2       w lines         lc 1    notitle         \
    ,path.'L40'.mean    u 1:2:3     w yerrorbars    lc 2    t '$L\!=\!40$'  \
    ,path.'L40'.wham    u 1:2       w lines         lc 2    notitle         \
    ,path.'L50'.mean    u 1:2:3     w yerrorbars    lc 3    t '$L\!=\!50$'  \
    ,path.'L50'.wham    u 1:2       w lines         lc 3    notitle         \
    ,path.'L60'.mean    u 1:2:3     w yerrorbars    lc 4    t '$L\!=\!60$'  \
    ,path.'L60'.wham    u 1:2       w lines         lc 4    notitle         \
    ,path.'L70'.mean    u 1:2:3     w yerrorbars    lc 5    t '$L\!=\!70$ '  \
    ,path.'L70'.wham    u 1:2       w lines         lc 5    notitle         \
    ,path.'L80'.mean    u 1:2:3     w yerrorbars    lc 6    t '$L\!=\!80$ '\
    ,path.'L80'.wham    u 1:2       w lines         lc 6    notitle         \
    ,path.'L90'.mean    u 1:2:3     w yerrorbars    lc 7    t '$L\!=\!90$ '  \
    ,path.'L90'.wham    u 1:2       w lines         lc 7    notitle         \
    ,path.'L100'.mean   u 1:2:3     w yerrorbars    lc 8 pt 4    t '$L\!=\!100$' \
    ,path.'L100'.wham   u 1:2       w lines         lc 8    notitle   \
    ,path.'L110'.mean   u 1:2:3     w yerrorbars    lc 9 pt 4    t '$L\!=\!110$' \
    ,path.'L110'.wham   u 1:2       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:2:3     w yerrorbars    lc 10 pt 4    t '$L\!=\!120$' \
    ,path.'L120'.wham   u 1:2       w lines         lc 10    notitle 

set yrange[0.05:1.05]; set ytics 0.1, 0.2, 0.9
set ylabel '$c_V$'; set xlabel '$T$'; set format x
set bmargin at screen  0.12; set tmargin at screen  0.525
plot path.'L30'.mean    u 1:4:5     w yerrorbars    lc 1    notitle \
    ,path.'L30'.wham    u 1:3       w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:4:5     w yerrorbars    lc 2    notitle \
    ,path.'L40'.wham    u 1:3       w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:4:5     w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:3       w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:4:5     w yerrorbars    lc 4    notitle \
    ,path.'L60'.wham    u 1:3       w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:4:5     w yerrorbars    lc 5    notitle \
    ,path.'L70'.wham    u 1:3       w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:4:5     w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:3       w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:4:5     w yerrorbars    lc 7    notitle \
    ,path.'L90'.wham    u 1:3       w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:4:5     w yerrorbars    lc 8 pt 4   notitle \
    ,path.'L100'.wham   u 1:3       w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:4:5     w yerrorbars    lc 9 pt 4   notitle \
    ,path.'L110'.wham   u 1:3       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:4:5     w yerrorbars    lc 10 pt 4   notitle \
    ,path.'L120'.wham   u 1:3       w lines         lc 10    notitle       
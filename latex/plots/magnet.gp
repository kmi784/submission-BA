#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,9cm color standalone font 8
#**********************************************************************


path = '../../data/plots/equi/'
mean = '-U-mean.txt'
wham = '-U-wham.txt'


set multiplot

set xrange[0.295:0.505]
set key columns 5 samplen 2 at screen 0.99,0.99 width 0 box spacing 1.3

set label 1 '(ferro.)' at screen 0.13,0.02; set label 2 '(super-antiferro.)' at screen 0.79,0.02


set lmargin at screen  0.15; set rmargin at screen  0.53



# magentization F
set yrange [0:0.16]; set ytics 0,0.04,0.16
set ylabel '$M_{(\cdot)}/N$'; set format x "";
set bmargin at screen  0.515; set tmargin at screen  0.87
plot path.'L30'.mean    u 1:6:7     w yerrorbars    lc 1    t '$L\!=\!30$' \
    ,path.'L30'.wham    u 1:4       w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:6:7     w yerrorbars    lc 2    t '$L\!=\!40$' \
    ,path.'L40'.wham    u 1:4       w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:6:7     w yerrorbars    lc 3    t '$L\!=\!50$' \
    ,path.'L50'.wham    u 1:4       w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:6:7     w yerrorbars    lc 4    t '$L\!=\!60$' \
    ,path.'L60'.wham    u 1:4       w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:6:7     w yerrorbars    lc 5    t '$L\!=\!70$' \
    ,path.'L70'.wham    u 1:4       w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:6:7     w yerrorbars    lc 6    t '$L\!=\!80$' \
    ,path.'L80'.wham    u 1:4       w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:6:7     w yerrorbars    lc 7    t '$L\!=\!90$ ' \
    ,path.'L90'.wham    u 1:4       w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:6:7     w yerrorbars    lc 8 pt 4    t '$L\!=\!100$' \
    ,path.'L100'.wham   u 1:4       w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:6:7     w yerrorbars    lc 9 pt 4    t '$L\!=\!110$' \
    ,path.'L110'.wham   u 1:4       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:6:7     w yerrorbars    lc 10 pt 4    t '$L\!=\!120$' \
    ,path.'L120'.wham   u 1:4       w lines         lc 10    notitle 


unset label 1; unset label 2



# susceptibility F
set yrange [0:150]; set ytics 0,30,150
set ylabel '$\chi_{(\cdot)}$'; set xlabel "$T$"; set format x 
set bmargin at screen  0.12; set tmargin at screen  0.475
plot path.'L30'.mean    u 1:8:9     w yerrorbars    lc 1    notitle \
    ,path.'L30'.wham    u 1:5       w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:8:9     w yerrorbars    lc 2    notitle \
    ,path.'L40'.wham    u 1:5       w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:8:9     w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:5       w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:8:9     w yerrorbars    lc 4    notitle \
    ,path.'L60'.wham    u 1:5       w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:8:9     w yerrorbars    lc 5    notitle \
    ,path.'L70'.wham    u 1:5       w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:8:9     w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:5       w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:8:9     w yerrorbars    lc 7    notitle \
    ,path.'L90'.wham    u 1:5       w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:8:9     w yerrorbars    lc 8 pt 4   notitle \
    ,path.'L100'.wham   u 1:5       w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:8:9     w yerrorbars    lc 9 pt 4   notitle \
    ,path.'L110'.wham   u 1:5       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:8:9     w yerrorbars    lc 10 pt 4   notitle \
    ,path.'L120'.wham   u 1:5       w lines         lc 10    notitle





set lmargin at screen  0.57; set rmargin at screen  0.95
set format y "" 


# magentization S
set yrange [0:0.16]; set ytics 0,0.04,0.16
unset ylabel; unset xlabel; set format x "";
set bmargin at screen  0.515; set tmargin at screen  0.87
plot path.'L30'.mean    u 1:10:11   w yerrorbars    lc 1    notitle \
    ,path.'L30'.wham    u 1:6       w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:10:11   w yerrorbars    lc 2    notitle \
    ,path.'L40'.wham    u 1:6       w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:10:11   w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:6       w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:10:11   w yerrorbars    lc 4    notitle \
    ,path.'L60'.wham    u 1:6       w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:10:11   w yerrorbars    lc 5    notitle \
    ,path.'L70'.wham    u 1:6       w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:10:11   w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:6       w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:10:11   w yerrorbars    lc 7    notitle \
    ,path.'L90'.wham    u 1:6       w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:10:11   w yerrorbars    lc 8 pt 4    notitle \
    ,path.'L100'.wham   u 1:6       w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:10:11   w yerrorbars    lc 9 pt 4    notitle \
    ,path.'L110'.wham   u 1:6       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:10:11   w yerrorbars    lc 10 pt 4    notitle \
    ,path.'L120'.wham   u 1:6       w lines         lc 10    notitle







# susceptibility S
set yrange [0:150]; set ytics 0,30,150
unset ylabel; set xlabel "$T$"; set format x
set bmargin at screen  0.12; set tmargin at screen  0.475
plot path.'L30'.mean    u 1:12:13   w yerrorbars    lc 1    notitle \
    ,path.'L30'.wham    u 1:7       w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:12:13   w yerrorbars    lc 2    notitle \
    ,path.'L40'.wham    u 1:7       w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:12:13   w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:7       w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:12:13   w yerrorbars    lc 4    notitle \
    ,path.'L60'.wham    u 1:7       w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:12:13   w yerrorbars    lc 5    notitle \
    ,path.'L70'.wham    u 1:7       w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:12:13   w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:7       w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:12:13   w yerrorbars    lc 7    notitle \
    ,path.'L90'.wham    u 1:7       w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:12:13   w yerrorbars    lc 8 pt 4   notitle \
    ,path.'L100'.wham   u 1:7       w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:12:13   w yerrorbars    lc 9 pt 4   notitle \
    ,path.'L110'.wham   u 1:7       w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:12:13   w yerrorbars    lc 10 pt 4   notitle \
    ,path.'L120'.wham   u 1:7       w lines         lc 10    notitle      
       

#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6cm color standalone font 8
#**********************************************************************


path = '../../data/plots/equi/'
mean = '-U-mean.txt'
wham = '-U-wham.txt'


set multiplot

set yrange[0.35:0.85]; set ytics 0.2,0.1,0.8
set xrange[0.295:0.505]; set xlabel "$T$"
set key columns 5 samplen 2 at screen 0.99,0.99 width 0 box spacing 1.3

set label 1 '(ferro.)' at screen 0.13,0.02; set label 2 '(super-antiferro.)' at screen 0.79,0.02

set bmargin at screen  0.15; set tmargin at screen  0.85



# magentization F
set ylabel '$M_{(\cdot)}/\sqrt{N}$'; 
set lmargin at screen  0.15; set rmargin at screen  0.53
plot path.'L30'.mean    u 1:($6*sqrt(30)):($7*sqrt(30))     w yerrorbars    lc 1    t '$L\!=\!30$' \
    ,path.'L30'.wham    u 1:($4*sqrt(30))                   w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:($6*sqrt(40)):($7*sqrt(40))     w yerrorbars    lc 2    t '$L\!=\!40$' \
    ,path.'L40'.wham    u 1:($4*sqrt(40))                   w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:($6*sqrt(50)):($7*sqrt(50))     w yerrorbars    lc 3    t '$L\!=\!50$' \
    ,path.'L50'.wham    u 1:($4*sqrt(50))                   w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:($6*sqrt(60)):($7*sqrt(60))     w yerrorbars    lc 4    t '$L\!=\!60$' \
    ,path.'L60'.wham    u 1:($4*sqrt(60))                   w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:($6*sqrt(70)):($7*sqrt(70))     w yerrorbars    lc 5    t '$L\!=\!70$' \
    ,path.'L70'.wham    u 1:($4*sqrt(70))                   w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:($6*sqrt(80)):($7*sqrt(80))     w yerrorbars    lc 6    t '$L\!=\!80$' \
    ,path.'L80'.wham    u 1:($4*sqrt(80))                   w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:($6*sqrt(90)):($7*sqrt(90))     w yerrorbars    lc 7    t '$L\!=\!90$ ' \
    ,path.'L90'.wham    u 1:($4*sqrt(90))                   w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:($6*sqrt(100)):($7*sqrt(100))   w yerrorbars    lc 8 pt 4    t '$L\!=\!100$' \
    ,path.'L100'.wham   u 1:($4*sqrt(100))                  w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:($6*sqrt(110)):($7*sqrt(110))   w yerrorbars    lc 9 pt 4    t '$L\!=\!110$' \
    ,path.'L110'.wham   u 1:($4*sqrt(110))                  w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:($6*sqrt(120)):($7*sqrt(120))   w yerrorbars    lc 10 pt 4    t '$L\!=\!120$' \
    ,path.'L120'.wham   u 1:($4*sqrt(120))                  w lines         lc 10    notitle 



# 10:11 / 1:6

set format y ""
unset ylabel; 
set lmargin at screen  0.57; set rmargin at screen  0.95
plot path.'L30'.mean    u 1:($10*sqrt(30)):($11*sqrt(30))   w yerrorbars    lc 1    notitle \
    ,path.'L30'.wham    u 1:($6*sqrt(30))                   w lines         lc 1    notitle \
    ,path.'L40'.mean    u 1:($10*sqrt(40)):($11*sqrt(40))   w yerrorbars    lc 2    notitle \
    ,path.'L40'.wham    u 1:($6*sqrt(40))                   w lines         lc 2    notitle \
    ,path.'L50'.mean    u 1:($10*sqrt(50)):($11*sqrt(50))   w yerrorbars    lc 3    notitle \
    ,path.'L50'.wham    u 1:($6*sqrt(50))                   w lines         lc 3    notitle \
    ,path.'L60'.mean    u 1:($10*sqrt(60)):($11*sqrt(60))   w yerrorbars    lc 4    notitle \
    ,path.'L60'.wham    u 1:($6*sqrt(60))                   w lines         lc 4    notitle \
    ,path.'L70'.mean    u 1:($10*sqrt(70)):($11*sqrt(70))   w yerrorbars    lc 5    notitle \
    ,path.'L70'.wham    u 1:($6*sqrt(70))                   w lines         lc 5    notitle \
    ,path.'L80'.mean    u 1:($10*sqrt(80)):($11*sqrt(80))   w yerrorbars    lc 6    notitle \
    ,path.'L80'.wham    u 1:($6*sqrt(80))                   w lines         lc 6    notitle \
    ,path.'L90'.mean    u 1:($10*sqrt(90)):($11*sqrt(90))   w yerrorbars    lc 7    notitle \
    ,path.'L90'.wham    u 1:($6*sqrt(90))                   w lines         lc 7    notitle \
    ,path.'L100'.mean   u 1:($10*sqrt(100)):($11*sqrt(100)) w yerrorbars    lc 8 pt 4    notitle \
    ,path.'L100'.wham   u 1:($6*sqrt(100))                  w lines         lc 8    notitle \
    ,path.'L110'.mean   u 1:($10*sqrt(110)):($11*sqrt(110)) w yerrorbars    lc 9 pt 4    notitle \
    ,path.'L110'.wham   u 1:($6*sqrt(110))                  w lines         lc 9    notitle \
    ,path.'L120'.mean   u 1:($10*sqrt(120)):($11*sqrt(120)) w yerrorbars    lc 10 pt 4    notitle \
    ,path.'L120'.wham   u 1:($6*sqrt(120))                  w lines         lc 10    notitle
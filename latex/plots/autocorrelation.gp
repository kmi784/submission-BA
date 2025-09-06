#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,12.1cm color standalone font 8
#**********************************************************************


path = '../../data/plots/dynm/'

line1 = '-F-line-autot1.txt'
line2 = '-F-line-autot2.txt'
line3 = '-F-line-autot3.txt'

metro1 = '-F-single-autot1.txt'
metro2 = '-F-single-autot2.txt'
metro3 = '-F-single-autot3.txt'


set multiplot

set yrange[-0.05:1.05]; set ytics 0, 0.2, 1
set xrange[0.2:0.5]; set xtics 0.1, 0.1, 0.5
set key columns 3 samplen 1 at screen 0.99,0.99 width 0.9 box spacing 1.3
set label 1 '(single spin up.)' at screen 0.15,0.03; set label 2 '(line spin up.)' at screen 0.79,0.03


#*************** Single-spin  ***************#
set lmargin at screen  0.15; set rmargin at screen  0.53



#***** t1 *****#
set ylabel '$G_{(\cdot)}(0,t^*_1)$'; set format x "";
set bmargin at screen  0.6634; set tmargin at screen  0.92
plot NaN w boxes fs solid   lc 12       t '$L\!=\!32$ '\
    ,NaN w p                lc -1 pt 4  t 'ferromagnetic' \
    ,NaN w boxes fs solid   lc 13       t '$L\!=\!64$ '\
    ,NaN w p                lc -1 pt 6  t 'horizontal striped'\
    ,NaN w boxes fs solid   lc 14       t '$L\!=\!128$' \
    ,NaN w p                lc -1 pt 8  t 'vertical striped' \
    ,path.'L32'.metro1   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.metro1   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.metro1  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.metro1   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.metro1   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.metro1  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.metro1   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.metro1   u 1:6:7     w yerrorbars    lc 13   pt 8    notitle \
    ,path.'L128'.metro1  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle 


unset key; unset label 1; unset label 2; 




#***** t2 *****#
set ylabel '$G_{(\cdot)}(0,t^*_2)$'; set format x ""
set bmargin at screen  0.3966; set tmargin at screen  0.6434
plot path.'L32'.metro2   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.metro2   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.metro2  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.metro2   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.metro2   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.metro2  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.metro2   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.metro2   u 1:6:7     w yerrorbars    lc 13    pt 8    notitle \
    ,path.'L128'.metro2  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle 



#***** t3 *****#
set ylabel '$G_{(\cdot)}(0,t^*_3)$'; set xlabel "$T$"; set format x 
set bmargin at screen  0.12; set tmargin at screen  0.3766
plot path.'L32'.metro3   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.metro3   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.metro3  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.metro3   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.metro3   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.metro3  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.metro3   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.metro3   u 1:6:7     w yerrorbars    lc 13    pt 8    notitle \
    ,path.'L128'.metro3  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle 






#*************** Line-spin  ***************#
set lmargin at screen  0.57; set rmargin at screen  0.95
set format y "";



#***** t1 *****#
unset ylabel; unset xlabel; set format x ""; 
set bmargin at screen  0.6634; set tmargin at screen  0.92
plot path.'L32'.line1   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.line1   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.line1  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.line1   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.line1   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.line1  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.line1   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.line1   u 1:6:7     w yerrorbars    lc 13    pt 8    notitle \
    ,path.'L128'.line1  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle 



#***** t2 *****#
unset ylabel; set format x ""
set bmargin at screen  0.3966; set tmargin at screen  0.6434
plot path.'L32'.line2   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.line2   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.line2  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.line2   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.line2   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.line2  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.line2   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.line2   u 1:6:7     w yerrorbars    lc 13    pt 8    notitle \
    ,path.'L128'.line2  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle  



#***** t3 *****#
unset ylabel; set xlabel "$T$"; set format x 
set bmargin at screen  0.12; set tmargin at screen  0.3766
plot path.'L32'.line3   u 1:2:3     w yerrorbars    lc 12    pt 4    notitle \
    ,path.'L64'.line3   u 1:2:3     w yerrorbars    lc 13    pt 4    notitle \
    ,path.'L128'.line3  u 1:2:3     w yerrorbars    lc 14    pt 4    notitle \
    ,path.'L32'.line3   u 1:4:5     w yerrorbars    lc 12    pt 6    notitle \
    ,path.'L64'.line3   u 1:4:5     w yerrorbars    lc 13    pt 6    notitle \
    ,path.'L128'.line3  u 1:4:5     w yerrorbars    lc 14    pt 6    notitle \
    ,path.'L32'.line3   u 1:6:7     w yerrorbars    lc 12    pt 8    notitle \
    ,path.'L64'.line3   u 1:6:7     w yerrorbars    lc 13    pt 8    notitle \
    ,path.'L128'.line3  u 1:6:7     w yerrorbars    lc 14    pt 8    notitle 




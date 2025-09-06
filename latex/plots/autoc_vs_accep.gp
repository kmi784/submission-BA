#*************** Settings ***************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,7.5cm color standalone font 8
#****************************************



path = '../../data/plots/dynm/'
accep = '-F-line-acceptance.txt' 
autoc = '-F-line-autot1.txt' 



set key columns 3 samplen 1 at screen 0.99,0.99 width 0.5 box spacing 1.3
set xlabel '$T$'
set xrange[0.19:0.51]; set xtics 0.1, 0.05, 0.5
set bmargin at screen  0.12; set tmargin at screen  0.82


set ylabel '$G_{(\cdot)}(0,t^*)$'; 
set yrange[-0.05:1.35]; set ytics nomirror; set ytics 0, 0.2, 1


set y2label '$\ln(r_\mathrm{a})$'
set y2range[-20:0]; set y2tics mirror; set y2tics nomirror; set y2tics -16, 3, -1

set arrow from 0.43, graph 0 to 0.43, graph 1 nohead lc 12 dt 2 
set arrow from 0.38, graph 0 to 0.38, graph 1 nohead lc 13 dt 2
set arrow from 0.34, graph 0 to 0.34, graph 1 nohead lc 14 dt 2 

plot NaN w boxes fs solid   lc 12       t '$L\!=\!32$ '\
    ,NaN w p                lc -1 pt 4  t 'ferromagnetic' \
    ,NaN w lines            lc -1       t 'single spin up.' \
    ,NaN w boxes fs solid   lc 13       t '$L\!=\!64$ '\
    ,NaN w p                lc -1 pt 6  t 'horizontal striped'\
    ,NaN w lines            lc -1 dt 4  t 'line spin up.' \
    ,NaN w boxes fs solid   lc 14       t '$L\!=\!128$' \
    ,NaN w p                lc -1 pt 8  t 'vertical striped' \
    ,NaN w lines            lc -1 dt 2  t 'peak locations' \
    ,path.'L32'.autoc   u 1:2:3                             w yerrorbars    lc 12 pt 4      notitle \
    ,path.'L32'.autoc   u 1:4:5                             w yerrorbars    lc 12 pt 6      notitle \
    ,path.'L32'.autoc   u 1:6:7                             w yerrorbars    lc 12 pt 8      notitle \
    ,path.'L32'.accep   u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines   lc 12 pt 0      notitle \
    ,path.'L32'.accep   u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines   lc 12 dt 4 pt 0 notitle \
    ,path.'L64'.autoc   u 1:2:3                             w yerrorbars    lc 13 pt 4      notitle \
    ,path.'L64'.autoc   u 1:4:5                             w yerrorbars    lc 13 pt 6      notitle \
    ,path.'L64'.autoc   u 1:6:7                             w yerrorbars    lc 13 pt 8      notitle \
    ,path.'L64'.accep   u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines   lc 13 pt 0      notitle \
    ,path.'L64'.accep   u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines   lc 13 dt 4 pt 0 notitle \
    ,path.'L128'.autoc  u 1:2:3                             w yerrorbars    lc 14 pt 4      notitle \
    ,path.'L128'.autoc  u 1:4:5                             w yerrorbars    lc 14 pt 6      notitle \
    ,path.'L128'.autoc  u 1:6:7                             w yerrorbars    lc 14 pt 8      notitle \
    ,path.'L128'.accep  u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines   lc 14 pt 0      notitle \
    ,path.'L128'.accep  u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines   lc 14 dt 4 pt 0 notitle 




#set lmargin at screen  0.52; set rmargin at screen  0.85
#unset ylabel; 



#set y2label '$T_\mathrm{max}$'; set xlabel '$\ln(L/L_0)^{-1}$'
#plot file u (1/log($1/L0)):2:3 axes x1y2 w yerrorbars   lc -1       notitle \
#    ,expon(L0*exp(1/x))  axes x1y2                      lc -1 dt 2  notitle 
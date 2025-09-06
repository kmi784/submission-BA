#*************** Settings ***************
load "include.gp"
@eps; @setout
#****************************************


path = '../../data/plots/dynm/'
file = '-F-line-acceptance.txt'

set multiplot 
set xrange[0.2:0.5]; set xtics 0.1, 0.1, 0.5


set key columns 3 samplen 1 at screen 0.91,0.99 width 1 box spacing 1.3
set bmargin at screen  0.15; set tmargin at screen  0.84
set xlabel '$T$'


set lmargin at screen  0.15; set rmargin at screen  0.48

set yrange[0:0.55]; set ytics 0, 0.1, 0.5


set ylabel '$r_\mathrm{a}$'
plot NaN    w boxes fs solid    lc 12       t '$L\!=\!32$ '\
    ,NaN    w lines             lc -1       t 'single spin up.' \
    ,NaN    w boxes fs solid    lc 13       t '$L\!=\!64$ '\
    ,NaN    w lines             lc -1 dt 4  t 'line spin up.' \
    ,NaN    w boxes fs solid    lc 14       t '$L\!=\!128$' \
    ,path.'L32'.file    u 1:2:3     w yerrorlines  lc 12 pt 0       notitle \
    ,path.'L32'.file    u 1:4:5     w yerrorlines  lc 12 dt 4 pt 0  notitle \
    ,path.'L64'.file    u 1:2:3     w yerrorlines  lc 13 pt 0       notitle \
    ,path.'L64'.file    u 1:4:5     w yerrorlines  lc 13 dt 4 pt 0  notitle \
    ,path.'L128'.file   u 1:2:3     w yerrorlines  lc 14 pt 0       notitle \
    ,path.'L128'.file   u 1:4:5     w yerrorlines  lc 14 dt 4 pt 0  notitle 

set lmargin at screen  0.52; set rmargin at screen  0.85
unset ylabel; unset ytics; set y2tics mirror

set y2range[-17:0]; set y2tics -16, 3, -1

set y2label '$\ln(r_\mathrm{a})$'
plot path.'L32'.file    u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines  lc 12 pt 0       notitle \
    ,path.'L32'.file    u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines  lc 12 dt 4 pt 0  notitle \
    ,path.'L64'.file    u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines  lc 13 pt 0       notitle \
    ,path.'L64'.file    u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines  lc 13 dt 4 pt 0  notitle \
    ,path.'L128'.file   u 1:(log($2)):($3/$2)   axes x1y2   w yerrorlines  lc 14 pt 0       notitle \
    ,path.'L128'.file   u 1:(log($4)):($5/$4)   axes x1y2   w yerrorlines  lc 14 dt 4 pt 0  notitle 
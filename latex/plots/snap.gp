#****************************** Settings ******************************
load "include.gp"
@setout
set terminal epslatex size 12.1cm,6cm color standalone font 8
#**********************************************************************

snap1 = '../../data/snap/L120-U-snap-single.txt'
snap2 = '../../data/snap/L120-U-snap-line.txt'


set multiplot 
set border linewidth 0
unset key
unset colorbox
unset tics
set palette negative grey
set pm3d map corners2color c1
set autoscale fix


set tmargin at screen 0.9
set bmargin at screen 0.1





set label 1 '(single spin up.)' at screen 0.05,0.96; set label 2 '(line spin up.)' at screen 0.8,0.96
set lmargin at screen 0.05; set rmargin at screen 0.45
splot snap1 matrix
unset label 1; unset label 2

set lmargin at screen 0.55; set rmargin at screen 0.95
splot snap2 matrix
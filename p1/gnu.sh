#!/usr/bin/gnuplot
set term png
set output "$1"
set xlabel "x"
set ylabel "f"
set title "Fitted function and Exact Function"

plot "interp.dat" u 1:2 w lines tit "exact"
replot "interp.dat" u 1:3 w lines tit "n=10"
replot "interp.dat" u 1:4 w lines tit "n=20"
replot "interp.dat" u 1:5 w lines tit "n=40"

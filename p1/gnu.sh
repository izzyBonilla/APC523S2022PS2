#!/usr/bin/gnuplot
set term png
set output "$1"
set xlabel "x"
set ylabel "f"
set title "Fitted function and Exact Function"

plot "interp.dat" u 1:2 w lines
replot "interp.dat" u 1:3 w lines

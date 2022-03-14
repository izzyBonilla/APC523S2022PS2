#!/usr/bin/gnuplot
set term png
set output filename
set logscale xy
set xlabel "n"
set ylabel "err"
set title "Error vs n"

plot "err.dat" u 1:2 w lines tit "L2 err",\
     "err.dat" u 1:3 w lines tit "Max err"

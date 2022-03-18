#!/usr/bin/gnuplot

set term png
set output filename
set xlabel "iter"
set ylabel "epsilon"
set title "Error vs iteration"
set logscale y

plot "j.dat" u 1:2 w lines tit "Jacobi",\
     "gs.dat" u 1:2 w lines tit "Gauss-Seidel"
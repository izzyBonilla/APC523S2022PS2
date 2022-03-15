#!/usr/bin/gnuplot

set term png
set output outfile
set xlabel "h"
set ylabel "f"
set title "Error vs. h"

plot "gq_a.dat" u 1:2 w lines tit "error",\
     x**0.5 dashtype 2 tit "h^0.5",\
     x dashtype 2 tit "h",\
     x**2 dashtype 2 tit "h^2",\
     x**4 dashtype 2 tit "h^4",\
     x**10 dashtype 2 tit "h^10"
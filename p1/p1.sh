#!/bin/bash
make interp
make interp_err

# runge
./interp runge
gnuplot -e "filename='p1_1a.png'" gnu.sh 

# abs
./interp abs
gnuplot -e "filename='p1_1b.png'" gnu.sh 

# step
./interp step
gnuplot -e "filename='p1_1c.png'" gnu.sh 

make clean
rm *.dat

#!/bin/bash

make jacobi
make gs

# 1
./gs 1 > gs.dat
./jacobi 1 > j.dat

gnuplot -e "filename='p3_1.png'" gnu.sh

# 2
./gs 2 > gs.dat
./jacobi 2 > j.dat

gnuplot -e "filename='p3_2.png'" gnu.sh

make clean
rm *.dat

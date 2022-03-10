#!/bin/bash
make interp
make interp_err

# runge
./interp runge
gnu.sh p1_1a.png

# abs
./interp abs
gnu.sh p1_1b.png

# step
./interp step
gnu.sh p1_1c.png

make clean
rm *.dat

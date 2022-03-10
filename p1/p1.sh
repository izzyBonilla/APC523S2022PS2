#!/bin/bash
make interp


#!/bin/bash
make poisson1a
./poisson1a 128 1e-6
cat final_phi.dat | sed '1d' > clean.dat
gnuplot p1a_gnu.sh

make clean
rm *.dat

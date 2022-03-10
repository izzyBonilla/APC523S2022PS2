#!/bin/bash
make interp

# runge
for NC in 10 20 40 
do
	./interp runge $NC
	gnuplot gnu.sh 

#!/bin/bash
make poisson1a
./poisson1a 128 1e-6
cat final_phi.dat | sed '1d' > clean.dat
gnuplot p1a_gnu.sh

make clean
rm *.dat

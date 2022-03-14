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

# runge err
for ((i=10; i <= 1000; i+=50))
do
	./interp_err runge $i 0 >> testing
done

make clean
rm *.dat

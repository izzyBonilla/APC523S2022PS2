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
ERR_FILE=err.dat
./interp_err runge 1 0 > $ERR_FILE
for ((i=10; i <= 1000; i+=10))
do
	./interp_err runge $i 0 >> $ERR_FILE
done
gnuplot -e "filename='p1_2a.png'" gnu_err.sh

# abs err
./interp_err abs 1 0 > $ERR_FILE
for ((i=10; i <= 1000; i+=10))
do
	./interp_err runge $i 0 >> $ERR_FILE
done
gnuplot -e "filename='p1_2b.png'" gnu_err.sh

# step err
./interp_err step 1 0 > $ERR_FILE
for ((i=10; i <= 1000; i+=10))
do
	./interp_err runge $i 0 >> $ERR_FILE
done
gnuplot -e "filename='p1_2c.png'" gnu_err.sh



make clean
rm *.dat

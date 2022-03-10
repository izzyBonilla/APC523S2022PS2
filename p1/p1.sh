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
for ((i=10; i <= 1000; c+=500))
do
	ERR=$(./interp_err runge $i 0)
	echo $ERR >> errsdat
done

make clean
rm *.dat
#!/bin/bash
make poisson1c
for NTHREAD in 1 2 4 8 16
do
	export OMP_NUM_THREADS=$NTHREAD
	TIME=$(mpiexec -n poisson1c $NTHREAD 128 1e-6 | awk '/Finished in/ {print $3}')
	echo $NTHREAD $TIME >> runtimes.dat
done
gnuplot p1b_gnu.sh
make clean
rm *.dat

#!/bin/bash
make gq

# Part A x8
INPUT=gq.dat
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

gnuplot -e "filename='p2_a.png'"  gnu.sh
>$INPUT

# Part B abs_poly
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

gnuplot -e "filename='p2_b.png'"  gnu.sh
>$INPUT

# Part C step
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

gnuplot -e "filename='p2_c.png'"  gnu.sh
>$INPUT

# Part D inv sqrt
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

gnuplot -e "filename='p2_d.png'"  gnu.sh
>$INPUT

make clean

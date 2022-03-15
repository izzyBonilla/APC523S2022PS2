#!/bin/bash
make gq

# Part A x8
INPUT=gq_a.dat
OUTPUT=p2_a.png
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

gnuplot -e "infile=$INPUT,outfile=$OUTPUT" gnu.sh

# Part B abs_poly
INPUT=gq_b.dat
OUTPUT=p2_b.png
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

# Part C step
INPUT=gq_c.dat
OUTPUT=p2_c.png
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

# Part D inv sqrt
INPUT=gq_d.dat
OUTPUT=p2_d.png
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

make clean
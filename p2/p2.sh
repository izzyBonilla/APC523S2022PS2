#!/bin/bash
make gq

# Part A x8
INPUT=gq_a.dat
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

# Part B abs_poly
INPUT=gq_b.dat
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

# Part C step
INPUT=gq_c.dat
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

# Part D inv sqrt
INPUT=gq_d.dat
for i in 1 2 4 8 16 32 64 128 256
do
    ./gq $i -1 1 x8 >> $INPUT
done

make clean
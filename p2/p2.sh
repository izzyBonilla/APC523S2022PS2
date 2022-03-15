#!/bin/bash
make gq

# Part A
for i in {1..10}
do
    echo $i
    ./gq $i -1 1 x8
done
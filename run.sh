#!/bin/sh

g++-4.8 --std=c++11 -O2 -Wall -o solver src/main.cpp || exit

for i in `ls dat/*.dat`
do
    echo "=== STAGE : $i ==="
    echo "--- INPUT ---"
    cat $i
    echo "--- OUTPUT ---"
    ./solver < $i
done

rm -f ./solver

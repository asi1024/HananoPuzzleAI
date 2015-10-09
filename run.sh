#!/bin/sh

g++-4.8 --std=c++11 -O2 -Wall -o solver src/main.cpp || exit

for i in `ls dat/*.dat`
do
    echo "=== $i ==="
    ./solver < $i 2> /dev/null
done

rm -f ./solver

#!/bin/sh
mkdir bin 2>/dev/null
cp ../cutils/arg.* ../cutils/io.* ./ 2>/dev/null
gcc -ggdb -o ./bin/cvault main.c arg.c io.c -O3 -Wall 

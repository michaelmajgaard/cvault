#!/bin/sh
cp ../../cutils/permute.* ./ 2> /dev/null
gcc -ggdb -o main.o main.c permute.c $1

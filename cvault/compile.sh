#!/bin/sh
cp ../../cutils/arg.* ./ 2>/dev/null
gcc -ggdb -o main.o main.c arg.c $1

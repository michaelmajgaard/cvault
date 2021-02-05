#!/bin/sh
cp ../../cutils/arg.* ../../cutils/io.* ./ 2>/dev/null
gcc -ggdb -o main.o main.c arg.c io.c $1

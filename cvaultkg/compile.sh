#!/bin/sh
cp ../../cutils/arg.* ./
gcc -ggdb -o main.o main.c arg.c $1

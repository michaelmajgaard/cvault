#!/bin/sh
# $1 = gdb or lldb
./compile-debug.sh && $1 ./bin/main.o

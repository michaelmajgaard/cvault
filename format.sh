#!/bin/sh
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" -i $PWD/*.c

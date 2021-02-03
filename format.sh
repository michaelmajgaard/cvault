#!/bin/sh
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" -i $PWD/*.c 2>/dev/null
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" -i $PWD/*.h 2>/dev/null

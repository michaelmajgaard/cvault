#!/bin/sh
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" -i *.c 2>/dev/null
clang-format -style="{BasedOnStyle: llvm, IndentWidth: 4}" -i *.h 2>/dev/null
exit 0

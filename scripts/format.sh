#!/bin/bash
set -e

echo formating: $(pwd)
cfiles="find -type d \\( -path ./_deps -o -path ./build \\) -prune -o -iname \"*.cc\" -print"
hfiles="find -type d \\( -path ./_deps -o -path ./build \\) -prune -o -iname \"*.h\" -print"

format_cc="xargs clang-format -i -style=file"
format_he="xargs clang-format -i -style=file"

echo "work: Format source files..."
eval $cfiles | $format_cc
echo "done: Formated CC files"
echo "work: Format header files..."
eval $hfiles | $format_he
echo "done: Formated header files"

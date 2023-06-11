#!/bin/bash

set -ex

echo formating: $(pwd)

format="xargs clang-format-14 -i -style=file"

echo "work: Format source files..."
find src/ -iname "*.cc" -print | $format
echo "done: Formated CC files"
echo "work: Format header files..."
find src/ -iname "*.h" -print | $format
echo "done: Formated header files"

#!/bin/bash

# Using https://astyle.sourceforge.net/

set -ex

echo formating: $(pwd)

format="xargs clang-format -i -style=file"

# Not C++ files
# find src/ -iname "*.cc" -print | $format
find src/ -iname "*.h" -print | $format

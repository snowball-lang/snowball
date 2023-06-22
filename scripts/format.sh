#!/bin/bash

set -ex

echo formating: $(pwd)

format="xargs clang-format-14 -i -style=file"

find src/ -iname "*.cc" -print | $format
find src/ -iname "*.h" -print | $format

find app/ -iname "*.cc" -print | $format
find app/ -iname "*.h" -print | $format

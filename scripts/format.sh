#!/bin/bash

# Using https://astyle.sourceforge.net/

set -ex

echo formating: $(pwd)

format="xargs astyle -A14 -s2 -n -xG -S -xt0 -w -Y --indent-lambda -m0 -p -H -U --unpad-brackets  -xe --squeeze-ws -k1 -W1 -O -o -c -xy -xC120 --mode=c -z2 "

find src/ -iname "*.cc" -print | $format
find src/ -iname "*.h" -print | $format

find app/ -iname "*.cc" -print | $format
find app/ -iname "*.h" -print | $format

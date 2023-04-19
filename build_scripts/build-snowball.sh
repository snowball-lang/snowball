#! /bin/bash

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... bash $0"
    exit 2
fi

set -x
set -e

# check out latest tag

label=snowball-"$DIST"-"$ARCH"

export C="/usr/bin/g++"
export CXX="/usr/bin/g++-9"

sh build_scripts/release.sh -DCMAKE_CXX_COMPILER="/usr/bin/g++-9"

mv libSnowballRuntime.so ./bin/Release/
mv libSnowball.so ./bin/Release/

mkdir release
mkdir -p release/bin
cp -a ./bin/Release/. release/
mv release/snowball release/bin/snowball
cp -R ./stdlib release/libs
tar -czvf "$label".tar.gz release/

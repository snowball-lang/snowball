#!/bin/bash

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]] || [[ "$NAME" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... NAME=... bash $0"
    exit 2
fi

set -x
set -e

# check out latest tag

label=snowball-"$NAME"-"$ARCH"

bash build_scripts/release.sh

if [[ "$OSTYPE" == "darwin"* ]]; then
    mv libSnowballRuntime.dylib ./bin/Release/
    mv libSnowball.dylib ./bin/Release/
else
    mv libSnowballRuntime.so ./bin/Release/
    mv libSnowball.so ./bin/Release/
fi

mkdir release
mkdir -p release/bin
cp -a ./bin/Release/. release/
mv release/snowball release/bin/snowball
cp -R ./stdlib release/libs
tar -czvf "$label".tar.gz release/

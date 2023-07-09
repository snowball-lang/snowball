#!/bin/bash

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]] || [[ "$NAME" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... NAME=... bash $0"
    exit 2
fi

set -x
set -e

# check out latest tag

label=snowball-"$NAME"-"$ARCH"

if [[ "$NAME" == "ce-specific" ]]; then
    export BUILD_FOR_CE=1
fi

bash build_scripts/release.sh
mkdir -p ./bin/Release/lib

if [[ "$OSTYPE" == "darwin"* ]]; then
    mv libSnowballRuntime.dylib ./bin/Release/lib
    mv libSnowball.dylib ./bin/Release/lib
else
    mv libSnowballRuntime.so ./bin/Release/lib
    mv libSnowball.so ./bin/Release/lib
fi

mkdir release
mkdir -p release/bin
cp -a ./bin/Release/. release/
mv release/snowball release/bin/snowball

if [[ "$NAME" == "ce-specific" ]]; then
    sudo apt install patchelf -y
    patchelf --set-rpath '$ORIGIN/../lib' release/bin/snowball
fi

cp -R ./stdlib release/stdlib
tar -czvf "$label".tar.gz release/

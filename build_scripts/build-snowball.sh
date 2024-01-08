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
    mv libsnowballrt.dylib ./bin/Release/lib
    mv libSnowball.dylib ./bin/Release/lib
else
    mv libsnowballrt.so ./bin/Release/lib
    mv libSnowball.so ./bin/Release/lib
fi

mkdir release
mkdir -p release/bin
mkdir -p release/lib
cp -a ./bin/Release/. release/
mv release/snowball release/bin/snowball

if [[ "$NAME" == "darwin" ]]; then
    echo "TODO: rpath for darwin"
    #brew install patchelf
#
    #patchelf --set-rpath '@loader_path/../lib' release/bin/snowball
    #patchelf --set-rpath '@loader_path/../lib' release/lib/libSnowball.dylib
else
    patchelf --set-rpath '$ORIGIN/../lib' release/bin/snowball
    patchelf --set-rpath '$ORIGIN/../lib' release/lib/libSnowball.so

    # copy curl shared library
    cp /usr/lib/x86_64-linux-gnu/libcurl.so.4 release/lib/libcurl.so
    cp /usr/lib/x86_64-linux-gnu/libssl.so.1.1 release/lib/libssl.so
fi

cp -R ./stdlib release/stdlib
tar -czvf "$label".tar.gz -C release/ .

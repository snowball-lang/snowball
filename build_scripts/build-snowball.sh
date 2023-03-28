#! /bin/bash

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... bash $0"
    exit 2
fi

set -x
set -e

cleanup () {
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi
}

trap cleanup EXIT

# check out latest tag
git checkout "$(git rev-list --tags --max-count=1)"

label=snowball-"$DIST"-"$ARCH"

sh build_scipts/release.sh

mv libSnowballRuntime.so ./bin/Release/
mv libSnowball.so ./bin/Release/

mkdir release
mkdir -p release/bin
cp -a ./bin/Release/. release/
mv release/snowball release/bin/snowball
cp -R ./stdlib release/libs
tar -czvf "$label".tar.gz release/

#! /bin/bash

echo Building for: "$NAME"

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]] || [[ "$NAME" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... NAME=... bash $0"
    exit 1
fi

set -e

error() {
    export TERM=xterm-256color
    tput setaf 1
    tput bold
    echo "Error:" "$@"
    tput sgr0
}

if [[ "$OSTYPE" == "darwin"* ]]; then
    if [[ "$ARCH" == "arm64" ]]; then
        //brew uninstall --ignore-dependencies zstd
        //brew fetch --force --bottle-tag=arm64_big_sur zstd
        //zstdResult=$(brew --cache --bottle-tag=arm64_big_sur zstd)
        //brew install $zstdResult
        //# most recent: 1.5.5
        //rm -rf /usr/local/lib/libzstd.1.dylib
        //sudo ln -s /opt/homebrew/Cellar/zstd/1.5.5/lib/libzstd.1.5.5.dylib /usr/local/lib/libzstd.1.dylib
        //sudo mkdir -p usr/local/opt/zstd/lib/ && find / -name "libzstd.1.dylib" -exec ln -s  {} /usr/local/opt/zstd/lib/libzstd.1.dylib \;
        //lipo -info /opt/homebrew/Cellar/zstd/1.5.5/lib/libzstd.1.5.5.dylib

        brew fetch --force --bottle-tag=arm64_big_sur llvm@16
        llvmResult=$(brew --cache --bottle-tag=arm64_big_sur llvm@16)
        echo "Looking for arm64 version of (llvm): $llvmResult"
        brew install $llvmResult
    else
        brew install llvm@16
    fi

    export LLVM_DIR="/usr/local/opt/llvm@16/lib/cmake"
    bash build_scripts/build-snowball.sh
else

    # needed to keep user ID in and outside Docker in sync to be able to write to workspace directory
    uid="$(id -u)"
    image="$DIST":"$ARCH"-uid"$uid"
    dockerfile=containers/"$DIST"/Dockerfile."$ARCH"

    echo $dockerfile
    echo $uid
    if [ ! -d "containers/$DIST" ]; then
        error "Unknown dist: $DIST"
        exit 2
    fi

    if [ "$DIST" == "common" ]; then
        error "\"common\" is not a distro"
        exit 2
    fi

    if [ ! -f "$dockerfile" ]; then
        error "Dockerfile $dockerfile could not be found"
        exit 3
    fi

    # build image to cache dependencies
    docker build -t "$image" -f "$dockerfile" --build-arg UID="$uid" containers/"$DIST"

    # run build inside this image
    EXTRA_ARGS=()
    [ -t 1 ] && EXTRA_ARGS+=("-t")
    docker run --rm -i "${EXTRA_ARGS[@]}" -e DOCKER=1 -v "$(readlink -f .)":/ws "$image" bash -xc "cd /ws && bash build_scripts/build-snowball.sh"

    ls
fi

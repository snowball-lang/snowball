#! /bin/bash

if [[ "$ARCH" == "" ]] || [[ "$DIST" == "" ]]; then
    echo "Usage: env ARCH=... DIST=... bash $0"
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

cd "$(readlink -f "$(dirname "$0")")"

# needed to keep user ID in and outside Docker in sync to be able to write to workspace directory
uid="$(id -u)"
image=cmake-build/"$DIST":"$ARCH"-uid"$uid"
dockerfile=containers/"$DIST"/Dockerfile."$ARCH"

if [ ! -d "containers/$DIST" ]; then
    error "Unknown dist: $DIST"
    exit 2
fi

if [ "$DIST" == "common" ]; then
    error "\"common\" is not a distro"
    exit 2
fi

# the version detection magic on the CI relies on the filename scheme to contain a fixed number of dashes
# therefore, we need to enforce that distro directory names contain no dashes
if echo "$DIST" | grep -q '\-'; then
    error "\"$DIST\" is an invalid name"
    exit 2
fi

if [ ! -f "$dockerfile" ]; then
    error "Dockerfile $dockerfile could not be found"
    exit 3
fi

# build image to cache dependencies
docker build -t "$image" -f "$dockerfile" --build-arg UID="$uid" "$DIST"

# run build inside this image
EXTRA_ARGS=()
[ -t 1 ] && EXTRA_ARGS+=("-t")
docker run --rm -i "${EXTRA_ARGS[@]}" -e DOCKER=1 -v "$(readlink -f .)":/ws "$image" bash -xc "cd /ws && bash build_scripts/build-snowball.sh"

ls
ls cmake-build/
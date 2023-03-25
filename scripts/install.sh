#!/usr/bin/env bash
set -e
set -o pipefail

SNOWBALL_INSTALL_DIR=~/.snowball
OS=$(uname -s | awk '{print tolower($0)}')
ARCH=$(uname -m)

if [ "$OS" != "linux" ] && [ "$OS" != "darwin" ]; then
  echo "error: Pre-built binaries only exist for Linux and macOS." >&2
  exit 1
fi

SNOWBALL_BUILD_ARCHIVE=snowball-$OS-$ARCH.tar.gz

mkdir -p $SNOWBALL_INSTALL_DIR
cd $SNOWBALL_INSTALL_DIR
curl -L https://github.com/snowball-lang/snowball/releases/latest/download/"$SNOWBALL_BUILD_ARCHIVE" | tar zxvf - --strip-components=1

EXPORT_COMMAND="export PATH=$(pwd)/bin:\$PATH"
echo "PATH export command:"
echo "  $EXPORT_COMMAND"

echo "Snowball successfully installed at: $(pwd)"
echo "Open a new terminal session or update your PATH to use snowball"

echo "Happy coding! 🐱"
#!/usr/bin/sh
set -euxo pipefail

log() {
    echo "[snowball installer]: $@"
}

log cloning project
git clone --quiet https://github.com/snowball-lang/snowball.git
cd ./snowball

log compiling project
cmake . $@ > /dev/null
make > /dev/null

log installing snowball
sudo make install

log cleaning
cd ..
rm -rf ./snowball

echo "Happy coding! 🐱"
#/usr/bin/env bash

wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 16

rm llvm.sh

sudo apt update

sudo apt install cmake libzstd-dev -y

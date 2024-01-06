#/usr/bin/env bash
set -x

mkdir install_deps_temp
cd install_deps_temp

wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 16

sudo apt install -y libzstd-dev libsigsegv-dev pkg-config curl

cd ..
rm -rf install_deps_temp
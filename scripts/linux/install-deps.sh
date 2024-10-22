curl https://sh.rustup.rs -sSf | sh
sudo apt-get update && sudo apt-get install git wget unzip software-properties-common -y
wget https://github.com/Kitware/CMake/releases/download/v3.29.0/cmake-3.29.0-linux-x86_64.tar.gz
tar zxvf cmake-3.29.0-linux-x86_64.tar.gz
sudo cp -rf cmake-3.29.0-linux-x86_64/bin/* /usr/local/bin && sudo cp -rf cmake-3.29.0-linux-x86_64/share/* /usr/local/share && rm -rf cmake-3.29.0-linux-x86_64
wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && sudo ./llvm.sh 18 && rm llvm.sh
sudo add-apt-repository -P ppa:ubuntu-toolchain-r/test
sudo add-apt-repository -P ppa:mhier/libboost-latest
sudo apt-get update && sudo apt-get install liblld-18-dev libpolly-18-dev libc++-18-dev clang-tools-18 flex libboost1.81-dev liblz4-dev zlib1g-dev libevent-dev libjemalloc-dev python3-dev
sudo ln -s /usr/lib/llvm-18/bin/clang-scan-deps /usr/bin/clang-scan-deps
sudo ln -s /usr/bin/clang-format-18 /usr/bin/clang-format
sudo ln -s /usr/bin/clang-tidy-18 /usr/bin/clang-tidy
sudo ln -s /usr/bin/llvm-symbolizer-18 /usr/bin/llvm-symbolizer
sudo ln -s /usr/lib/llvm-18/include/x86_64-pc-linux-gnu/c++/v1/__config_site /usr/lib/llvm-18/include/c++/v1/__config_site
rm -rf cmake-3.29.0-linux-x86_64.tar.gz

sudo apt install -y libzstd-dev pkg-config liblld-18-dev libpolly-18-dev libc++-18-dev clang-tools-18 liblz4-dev zlib1g-dev libevent-dev libjemalloc-dev python3-dev

# Corrosion
git clone https://github.com/corrosion-rs/corrosion.git
cmake -Scorrosion -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release && sudo cmake --install build --config Release
rm -rf corrosion
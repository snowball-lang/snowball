if [[ "$OSTYPE" != "darwin"* ]]; then
    sudo apt install software-properties-common
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update
    sudo apt install gcc-9 g++-9 -y
    sudo apt install cmake -y

    export CC="/usr/bin/gcc-9"
    export CXX="/usr/bin/g++-9"
fi

mkdir -p bin/Release
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/local -DLLVM_ENABLE_BACKTRACES=OFF \
-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF \
-DLLVM_ENABLE_TERMINFO=OFF \
-DLLVM_ENABLE_ZLIB=OFF \
-DLLVM_INCLUDE_EXAMPLES=OFF \
-DLLVM_ENABLE_ZSTD=OFF \
-DCMAKE_OSX_ARCHITECTURES="$ARCH" \
-DLLVM_INCLUDE_DOCS=OFF -DCMAKE_BUILD_TYPE=Release -DEXECUTABLE_OUTPUT_PATH="bin/Release" $@ .
cmake --build . --config Release --verbose -- -j 3
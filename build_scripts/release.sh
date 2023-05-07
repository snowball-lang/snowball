export CXXFLAGS="-D_SN_DEBUG=0"

if [[ "$OSTYPE" != "darwin"* ]]; then
    export C="/usr/bin/g++"
    export CXX="/usr/bin/g++-9"

    g++ --help
fi

mkdir -p bin/Release
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DLLVM_ENABLE_BACKTRACES=OFF \
-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF \
-DLLVM_ENABLE_TERMINFO=OFF \
-DLLVM_ENABLE_ZLIB=OFF \
-DLLVM_INCLUDE_EXAMPLES=OFF \
-DLLVM_INCLUDE_DOCS=OFF -DCMAKE_BUILD_TYPE=Release -D_SN_DEBUG=OFF -DEXECUTABLE_OUTPUT_PATH="bin/Release" $@ .
cmake --build . --config Release -- -j 3
#!/usr/bin/env sh

# CURRENTLY BROKEN!

set -e
export CXXFLAGS="-D_SN_DEBUG=0"
export CMAKE_TOOLCHAIN_FILE="build_scripts/toolchains-windows.cmake"
export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu

mkdir -p bin/Release
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_BACKTRACES=OFF \
-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF \
-DLLVM_ENABLE_TERMINFO=OFF \
-DLLVM_ENABLE_ZLIB=OFF \
-DLLVM_INCLUDE_EXAMPLES=OFF \
-DLLVM_INCLUDE_DOCS=OFF \
-DLLVM_TOOL_LLVM_AR_BUILD=OFF -DEXECUTABLE_OUTPUT_PATH="bin/Release" $@ .
cmake --build . --config Release -- -j 3

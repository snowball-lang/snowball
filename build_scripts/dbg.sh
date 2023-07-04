set -ex
mkdir -p bin/Debug
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DLLVM_ENABLE_BACKTRACES=OFF \
-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF \
-DLLVM_ENABLE_TERMINFO=OFF \
-DLLVM_ENABLE_ZLIB=OFF \
-DLLVM_INCLUDE_EXAMPLES=OFF \
-DLLVM_INCLUDE_DOCS=OFF -DEXECUTABLE_OUTPUT_PATH="bin/Debug" $@ .
cmake --build . --config Debug
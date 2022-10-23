mkdir -p bin/Release
cmake -DCMAKE_BUILD_TYPE=Release -DEXECUTABLE_OUTPUT_PATH="Release" .
cmake --build .
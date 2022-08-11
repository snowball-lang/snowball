mkdir -p Debug
cmake -DCMAKE_BUILD_TYPE=Debug -DLIBRARY_OUTPUT_PATH="Debug" -DEXECUTABLE_OUTPUT_PATH="Debug" .
cmake --build .
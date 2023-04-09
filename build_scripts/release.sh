export CXXFLAGS="-D_SN_DEBUG=0"

mkdir -p bin/Release
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DCMAKE_BUILD_TYPE=Release -D_SN_DEBUG=OFF -DEXECUTABLE_OUTPUT_PATH="bin/Release" $@ .
cmake --build . --config Release -- -j 3
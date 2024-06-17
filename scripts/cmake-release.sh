
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-Wall -Wextra -Werror" \
      ..


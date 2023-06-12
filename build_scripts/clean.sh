#!/usr/bin/bash
set -ex

cmake --build . --target clean
rm -rf ./_deps
rm -rf ./.cache
rm -rf ./build
rm -rf ./CMakeFiles
rm -rf ./libsnowball.so
rm -rf ./libSnowball.so
rm -rf ./Makefile
rm -rf ./cmake_install.cmake
rm -rf ./CMakeCache.txt
rm -rf ./bin

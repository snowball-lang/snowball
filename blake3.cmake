
# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

set(BLAKE3_VERSION 1.5.1)
set(BLAKE3_URL "https://github.com/BLAKE3-team/BLAKE3/archive/${BLAKE3_VERSION}.tar.gz")

# Step 1: Download the BLAKE3 source code
include(FetchContent)
FetchContent_Declare(
  BLAKE3 
  URL ${BLAKE3_URL}
)

FetchContent_GetProperties(BLAKE3)
if(NOT BLAKE3_POPULATED)
    FetchContent_Populate(BLAKE3)
endif()

set(BLAKE3_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/blake3-src/c/)
set(BLAKE3_BUILD_DIR ${CMAKE_BINARY_DIR}/_deps/blake3-build)

configure_file(${BLAKE3_SOURCE_DIR}/blake3-config.cmake.in ${BLAKE3_BUILD_DIR}/blake3-config.cmake @ONLY)

execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${BLAKE3_SOURCE_DIR} WORKING_DIRECTORY ${BLAKE3_BUILD_DIR})

execute_process(COMMAND ${CMAKE_COMMAND} --build ${BLAKE3_BUILD_DIR} --target blake3)
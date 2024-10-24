
# --- PROJECT CONFIGURATION ---
cmake_minimum_required(VERSION 3.29)
project(snowball)

# --- CLANG CONFIGURATION ---
execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE clang_full_version_string)
string(REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION_STRING ${clang_full_version_string})

set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

# minimum c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

option(ENABLE_TESTS "Enable tests" ON)

if (CLANG_VERSION_STRING VERSION_EQUAL 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-deprecated-declarations -Wextra -Wno-unused-parameter")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-deprecated-declarations -Wextra -Wno-unused-parameter")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")

add_definitions(-DSIMDE_ENABLE_NATIVE_ALIASES)
if (CMAKE_C_COMPILER_ID STREQUAL "Clang" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "18.0")
    add_definitions(-mevex512)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
include(FetchContent)

# --- BUILD METADATA ---
# Get current system time and print the build time
execute_process(COMMAND "date" +"%Y-%m-%d %H:%M.%S" OUTPUT_VARIABLE CURRENT_SYS_TIME)
string(REGEX REPLACE "\n" "" CURRENT_SYS_TIME ${CURRENT_SYS_TIME})
message(STATUS "Build time = ${CURRENT_SYS_TIME}")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

# --- MODULES AND SOURCES ---

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cc")

file(GLOB_RECURSE BIN_SOURCES "src/bin/*.cc")
list(REMOVE_ITEM PROJECT_SOURCES ${BIN_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_library("lib${PROJECT_NAME}" SHARED ${PROJECT_SOURCES})
else()
    add_library("lib${PROJECT_NAME}" STATIC ${PROJECT_SOURCES})
endif()

add_executable(${PROJECT_NAME} ${BIN_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC "lib${PROJECT_NAME}")

# --- LLVM LIBRARIES ---
find_package(LLVM 18.1.8 REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
set(LLVM_ENABLE_BACKTRACES OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_PER_TARGET_RUNTIME_DIR ON CACHE BOOL "" FORCE)
set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_ZLIB OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL "" FORCE)

foreach(target ${LLVM_TARGETS_TO_BUILD})
  list(APPEND targets "LLVM${target}CodeGen")
endforeach()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Build a static binary: ${BUILD_FOR_WIN}")

llvm_map_components_to_libnames(llvm_libs
  AllTargetsAsmParsers
  AllTargetsCodeGens
  AllTargetsDescs
  AllTargetsInfos
  AggressiveInstCombine
  Analysis
  AsmParser
  BitWriter
  CodeGen
  Core
  IRReader
  InstCombine
  Instrumentation
  ObjCARCOpts
  Remarks
  ScalarOpts
  Symbolize
  Target
  TransformUtils
  Vectorize
  ExecutionEngine
  nativecodegen
  option
  lto
  support
  windowsdriver windowsmanifest symbolize
)

include_directories(${LLVM_INCLUDE_DIRS})
target_link_libraries("lib${PROJECT_NAME}" PUBLIC 
    ${llvm_libs}
)

# --- LLD LIBRARIES ---
set(LLD_LINKED_NAMES "lldCOFF" "lldELF" "lldMachO" "lldMinGW" "lldWasm" "LLVMLibDriver" "lldCommon")
set(LLD_LINKED_LIBS "")
foreach(name ${LLD_LINKED_NAMES})
  list(APPEND LLD_LINKED_LIBS "${LLVM_LIBRARY_DIRS}/lib${name}.a")
endforeach()

if(APPLE)
  # LLD 13.0.0 on Mac needs libxar
  list(APPEND LLD_LINKED_LIBS -lxar)
endif()
message(STATUS "LLD libraries: ${LLD_LINKED_LIBS}")
target_link_libraries("lib${PROJECT_NAME}" PUBLIC ${LLD_LINKED_LIBS})

# --- FMT LIBRARIES ---
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
set(FMT_INSTALL OFF)
FetchContent_MakeAvailable(fmt)
target_link_libraries("lib${PROJECT_NAME}" PUBLIC fmt::fmt)

# --- Declare if we are building on debug mode ---
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DSNOWBALL_DEBUG)
else()
  add_definitions(-DSNOWBALL_RELEASE)
endif()

# --- Rust libraries ---
find_package(Corrosion REQUIRED)
include(cmake/corrosion_cxx.cmake)

add_library_rust(PATH src/packages/clowder NAMESPACE clowder)
target_link_libraries("lib${PROJECT_NAME}" PUBLIC clowder::clowder)

# --- OTHER ---
message(STATUS "C++ Compilation flags: " ${CMAKE_CXX_FLAGS})

# --- TESTS ---
if (ENABLE_TESTS)
    enable_testing()
    message(STATUS "Tests enabled")

    add_compile_definitions(SNOWBALL_TESTING)

    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE TEST_SOURCES "tests/*.cc")
    add_executable(tests-bin ${TEST_SOURCES})
    target_link_libraries(tests-bin PUBLIC "lib${PROJECT_NAME}")
    target_link_libraries(tests-bin PUBLIC GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tests-bin)
endif()

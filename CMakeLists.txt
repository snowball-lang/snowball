cmake_minimum_required(VERSION 3.16)

if ("$ENV{ARCH}" STREQUAL "arm64")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_SYSTEM_PROCESSOR arm64)
    set(CMAKE_HOST_SYSTEM_PROCESSOR arm64)
    set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
  endif()
endif()

project(snowball)

if ("$ENV{ARCH}" STREQUAL "arm64")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_C_LINK_FLAGS "")
    set(CMAKE_CXX_LINK_FLAGS "")
  endif()
endif()

include(FetchContent)

if ("$ENV{BUILD_FOR_CE}" STREQUAL "1")
  message(STATUS "Building for CE")
  set(CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_FOR_WIN TRUE)
else()
  set(BUILD_FOR_WIN FALSE)
endif()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif()

if (STATIC_BUILD)
        set(CMAKE_EXE_LINKER_FLAGS "-static")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
        set(BUILD_SHARED_LIBS OFF)
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "User path" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

find_package(PkgConfig REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
else()
  pkg_check_modules(GLIB REQUIRED glib-2.0)
endif()

find_package(LLVM REQUIRED CONFIG)
set(LLVM_ENABLE_BACKTRACES OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_PER_TARGET_RUNTIME_DIR ON CACHE BOOL "" FORCE)
set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_ZLIB OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL "" FORCE)

add_definitions(${LLVM_DEFINITIONS})

message(STATUS ${LLVM_DEFINITIONS})
message(STATUS ${LLVM_CONFIG})
message(STATUS ${LLVM_ENABLE_ZLIB})
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Build a static binary (aka, for windows): ${BUILD_FOR_WIN}")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cc src/**/*cc src/*.c)
file(GLOB_RECURSE PROJECT_CMAKE_UTILS cmake/*.cmake)
file(GLOB_RECURSE PROJECT_MISC *.md *.txt)
set (PROJECT_EXPORT_HPP include/${PROJECT_NAME}/export.hpp)
set (GCC_COVERAGE_COMPILE_FLAGS "-Wl,-znodelete")
set (GCC_COVERAGE_LINK_FLAGS "-rdynamic")
set (PROJECT_FILES
  ${PROJECT_SOURCES}
  ${PROJECT_CMAKE_UTILS}
  ${PROJECT_MISC}
  ${PROJECT_EXPORT_HPP}
  ${LLVM_INCLUDE_DIRS})

file(GLOB_RECURSE RUNTIME_SOURCES runtime/**/*.cc runtime/**/*.c runtime/gc/*.c)
set (RUNTIME_FILES
  ${RUNTIME_SOURCES})

set(APP_HEADERS_DIR app/)
file(GLOB_RECURSE APP_HEADERS ${APP_HEADERS_DIR}/*.h ${APP_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE APP_SOURCES app/*.cc app/*.cc app/*.c)
set (APP_FILES
  ${APP_HEADERS}
  ${APP_SOURCES})

# Map llvm components
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
  Support
  Symbolize
  Target
  TransformUtils
  Vectorize
  nativecodegen
  ExecutionEngine
)

##################################################    Targets     ##################################################
if (${BUILD_FOR_WIN})
  add_library(snowball STATIC ${PROJECT_FILES})
  add_library(SnowballRuntime STATIC ${RUNTIME_FILES})
else()
  add_library(snowball SHARED ${PROJECT_FILES})
  add_library(SnowballRuntime SHARED ${RUNTIME_FILES})
endif()

add_executable(snowballexe ${APP_FILES})
target_include_directories(snowballexe PUBLIC ${APP_HEADERS_DIR})
target_link_libraries(snowballexe PUBLIC ${PROJECT_NAME} ${GLIB_LIBRARIES})

if (${BUILD_FOR_WIN})
  set_target_properties(snowballexe PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.exe)
else()
  set_target_properties(snowballexe PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
endif()
set_target_properties(snowball PROPERTIES OUTPUT_NAME "Snowball")

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

foreach(target ${LLVM_TARGETS_TO_BUILD})
  list(APPEND targets "LLVM${target}CodeGen")
endforeach()

execute_process(COMMAND gcc -dumpversion OUTPUT_VARIABLE _LIBC_VERSION)
string(REGEX REPLACE "\n" "" _LIBC_VERSION "${_LIBC_VERSION}")


set (STATICLIB_DIR ".snowball")
set (_SNOWBALL_LIBRARY_OBJ "lib")
set (_SNOWBALL_LIBRARY_DIR "stdlib")

if ("$ENV{BUILD_FOR_CE}" STREQUAL "1")
  add_compile_definitions(_SNOWBALL_BUILD_FOR_CE="1")
endif()

if (${BUILD_FOR_WIN})
  add_compile_definitions(LD_PATH="ld")
else()
  add_compile_definitions(LD_PATH="/usr/bin/ld")
endif()


add_compile_definitions(STATICLIB_DIR="${STATICLIB_DIR}")

add_compile_definitions(_SNOWBALL_LIBRARY_OBJ="${_SNOWBALL_LIBRARY_OBJ}")
add_compile_definitions(_SNOWBALL_LIBRARY_DIR="${_SNOWBALL_LIBRARY_DIR}")
add_compile_definitions(_SNOWBALL_PACKAGES_DIR=".sn/packages")

set(CONFIG_NAME "llvm-config")
if (NOT "${LLVM_CONFIG_EXECUTABLE}" STREQUAL "")
  set(CONFIG_NAME "${LLVM_CONFIG_EXECUTABLE}")
  unset(LLVM_CONFIG_EXECUTABLE CACHE)
endif()
find_program(LLVM_CONFIG_EXECUTABLE NAMES "${CONFIG_NAME}" "${CONFIG_NAME}-14")

execute_process(COMMAND ${CONFIG_NAME} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
string(REPLACE "\n" " " LLVM_LDFLAGS "${LLVM_LDFLAGS} ${LLVM_LDFLAGS2}")
string(STRIP ${LLVM_LDFLAGS} LLVM_LDFLAGS)

message(STATUS "${LLVM_LDFLAGS}")
add_compile_definitions(LLVM_LDFLAGS="${LLVM_LDFLAGS}")
add_compile_definitions(LIBC_VERSION="${_LIBC_VERSION}")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${LLVM_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include> PRIVATE source)
    target_include_directories(${PROJECT_NAME} PUBLIC ${LLVM_INCLUDE_DIRS} ${PROJECT_INCLUDE_DIRS})
    target_link_libraries     (${PROJECT_NAME} PUBLIC ${llvm_libs} ${GLIB_LIBRARIES} ${llvm_libraries} ${targets} ${PROJECT_LIBRARIES})

target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
set_target_properties     (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# To output llvm ir
# note: only works with clang (ofc).
# target_compile_options(${PROJECT_NAME} PUBLIC ${CMAKE_CXX_FLAGS} -flto -fembed-bitcode)

if(NOT BUILD_SHARED_LIBS)
  string               (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
  set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -D${PROJECT_NAME_UPPER}_STATIC)
endif()

##################################################    StdLib   ##################################################

macro( add_recursive retVal dir ext excl)
#Store unfiltered list of files into temporary list
    file( GLOB_RECURSE _tmp_list ${dir}/${ext})
#Resulted list is initially empty.Copy all needed elements into it.
    set(${retval} "")
    foreach(f ${_tmp_list})
        if(NOT f MATCHES ${excl})
            list(APPEND ${retVal} ${f})
        endif()
    endforeach()
endmacro( add_recursive )

add_recursive(std_sn_files "./stdlib" "*.sn" "/_tests/")

##################################################    Postbuild   ##################################################
include               (GenerateExportHeader)
string                (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME     ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/export.hpp
  EXPORT_MACRO_NAME    ${PROJECT_NAME_UPPER}_EXPORT
  STATIC_DEFINE        ${PROJECT_NAME_UPPER}_STATIC
)

#installation
install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS SnowballRuntime EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS snowballexe EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

# TODO: as a feature:
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

#install(FILES ${std_sn_files} DESTINATION ${HOME_DIR}/${STATICLIB_DIR}/${_SNOWBALL_LIBRARY_DIR})
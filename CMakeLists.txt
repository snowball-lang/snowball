cmake_minimum_required(VERSION 3.16)

message(STATUS $ENV{ARCH})
message(STATUS ${CMAKE_SYSTEM_NAME})

file(READ "snowball.version.str" version)
file(READ "snowball.version.id" versionID)
project(snowball VERSION ${version})

set(CMAKE_CXX_FLAGS_DEBUG "-g")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-limit-debug-info")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_compile_options ( -Wextra -pedantic -Wall -Wno-pedantic -Wno-ignored-qualifiers -Wno-reorder-ctor -Wno-unused-function -Wno-unused-parameter -Wno-comment -Wno-unknown-pragmas -Wno-misleading-indentation -Wno-deprecated-declarations -Wunused-but-set-variable)

# only when compiling c++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-ignored-qualifiers")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder-ctor -Wno-delete-non-abstract-non-virtual-dtor -Wno-unused-private-field -Wno-sometimes-uninitialized -Wno-c++20-extensions")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-discarded-qualifiers -Wshift-negative-value")
endif()

option(SNOWBALL_SANITIZER "Enable sanitizer" OFF)

if (SNOWBALL_SANITIZER)
  add_compile_options(-fsanitize=address,undefined)
  add_link_options(-fsanitize=address,undefined)
endif()

if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
  set(CPU_TYPE ${CMAKE_OSX_ARCHITECTURES})
  set(CMAKE_SYSTEM_PROCESSOR arm64)
  set(CMAKE_HOST_SYSTEM_PROCESSOR arm64)
  set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
endif()

option(SNOWBALL_CPPCHECK "Enable cppcheck" OFF)

if (SNOWBALL_CPPCHECK)
  set(CMAKE_CXX_CPPCHECK "cppcheck"
  "--enable=information"
  "--check-config"
  "--suppress=missingIncludeSystem")
endif()

if ("$ENV{ARCH}" STREQUAL "arm64")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_C_LINK_FLAGS "")
    set(CMAKE_CXX_LINK_FLAGS "")
  endif()
endif()

include(FetchContent)

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

find_package(LLVM 16 REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
set(LLVM_ENABLE_BACKTRACES OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_PER_TARGET_RUNTIME_DIR ON CACHE BOOL "" FORCE)
set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_ZLIB OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_DOCS OFF CACHE BOOL "" FORCE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CPM_DOWNLOAD_VERSION 0.32.3)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake...")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()
include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
    NAME backtrace
    GITHUB_REPOSITORY "ianlancetaylor/libbacktrace"
    GIT_TAG d0f5e95a87a4d3e0a1ed6c069b5dae7cbab3ed2a
    DOWNLOAD_ONLY YES)
if(backtrace_ADDED)
  set(backtrace_SOURCES
      "${backtrace_SOURCE_DIR}/atomic.c"
      "${backtrace_SOURCE_DIR}/backtrace.c"
      "${backtrace_SOURCE_DIR}/dwarf.c"
      "${backtrace_SOURCE_DIR}/fileline.c"
      "${backtrace_SOURCE_DIR}/mmapio.c"
      "${backtrace_SOURCE_DIR}/mmap.c"
      "${backtrace_SOURCE_DIR}/posix.c"
      "${backtrace_SOURCE_DIR}/print.c"
      "${backtrace_SOURCE_DIR}/simple.c"
      "${backtrace_SOURCE_DIR}/sort.c"
      "${backtrace_SOURCE_DIR}/state.c")
    set(backtrace_INCLUDE_DIRS "${backtrace_SOURCE_DIR}")

  # https://go.googlesource.com/gollvm/+/refs/heads/master/cmake/modules/LibbacktraceUtils.cmake
  set(BACKTRACE_SUPPORTED 1)
  set(BACKTRACE_ELF_SIZE 64)
  set(HAVE_GETIPINFO 1)
  set(BACKTRACE_USES_MALLOC 1)
  set(BACKTRACE_SUPPORTS_THREADS 1)
  set(BACKTRACE_SUPPORTS_DATA 1)
  set(HAVE_SYNC_FUNCTIONS 1)
  if(APPLE)
      set(HAVE_MACH_O_DYLD_H 1)
      list(APPEND backtrace_SOURCES "${backtrace_SOURCE_DIR}/macho.c")
  else()
      set(HAVE_MACH_O_DYLD_H 0)
      list(APPEND backtrace_SOURCES "${backtrace_SOURCE_DIR}/elf.c")
  endif()
  # Generate backtrace-supported.h based on the above.
  configure_file(
      ${CMAKE_SOURCE_DIR}/cmake/backtrace-supported.h.in
      ${backtrace_SOURCE_DIR}/backtrace-supported.h)
  configure_file(
      ${CMAKE_SOURCE_DIR}/cmake/backtrace-config.h.in
      ${backtrace_SOURCE_DIR}/config.h)
  add_library(backtrace STATIC ${backtrace_SOURCES})
  target_include_directories(backtrace BEFORE PRIVATE "${backtrace_SOURCE_DIR}")
  set_target_properties(backtrace PROPERTIES
      COMPILE_FLAGS "-funwind-tables -D_GNU_SOURCE"
      POSITION_INDEPENDENT_CODE ON)
endif()

message(STATUS ${LLVM_DEFINITIONS})
message(STATUS ${LLVM_ENABLE_ZLIB})
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Build a static binary: ${BUILD_FOR_WIN}")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE PROJECT_SOURCES src/compiler/*.cc src/compiler/**/*cc src/compiler/*.c)
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

set(APP_HEADERS_DIR src/app/)
file(GLOB_RECURSE APP_HEADERS ${APP_HEADERS_DIR}/*.h ${APP_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE APP_SOURCES src/app/src/*.cc src/app/*.c)
set (APP_FILES
  ${APP_HEADERS}
  ${APP_SOURCES})

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

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

##################################################    Targets     ##################################################
if (${BUILD_FOR_WIN})
  add_library(snowball STATIC ${PROJECT_FILES})
else()
  add_library(snowball SHARED ${PROJECT_FILES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  message(STATUS "Changing rpath origin destination (for macos)")
  message(STATUS "rpath: @loader_path/../lib")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,@loader_path/../lib")
else()
  message(STATUS "Changing rpath origin destination (for linux)")
  message(STATUS "rpath: $ORIGIN/../lib")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN/../lib")
endif()

# Add "LLD" libraries for all targets to the linker flags
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

add_executable(snowballexe ${APP_FILES})
target_include_directories(snowballexe PUBLIC ${APP_HEADERS_DIR})

if (${BUILD_FOR_WIN})
  set_target_properties(snowballexe PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.exe)
else()
  set_target_properties(snowballexe PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
endif()
set_target_properties(snowball PROPERTIES OUTPUT_NAME "Snowball")

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

foreach(target ${LLVM_TARGETS_TO_BUILD})
  list(APPEND targets "LLVM${target}CodeGen")
endforeach()

if (DEFINED ENV{BUILD_FOR_CE})
  add_compile_definitions(_SNOWBALL_BUILD_FOR_CE="1")
endif()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

include(blake3.cmake)

add_compile_definitions(_SNOWBALL_VERSION="${version}")
add_compile_definitions(_SNOWBALL_VERSION_NUMBER=${versionID})

message(STATUS "Blake3 source dir: ${BLAKE3_SOURCE_DIR}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM link paths: ${LLVM_LIBRARY_DIRS}")
message(STATUS "LLVM libs: ${llvm_libs}")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${LLVM_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include> ${BLAKE3_SOURCE_DIR} PRIVATE source)
target_link_libraries(${PROJECT_NAME} PUBLIC ${llvm_libs} ${GLIB_LIBRARIES} 
                     ${targets} ${PROJECT_LIBRARIES} 
                     nlohmann_json::nlohmann_json fmt::fmt ${BLAKE3_BUILD_DIR}/libblake3.a 
                     ${LLD_LINKED_LIBS})
target_link_libraries(snowballexe PUBLIC ${PROJECT_NAME})


target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
add_compile_definitions("_SN_DEBUG=$<CONFIG:Debug>")
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
install(TARGETS snowballexe EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

# TODO: as a feature:
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

#install(FILES ${std_sn_files} DESTINATION ${HOME_DIR}/${STATICLIB_DIR}/${_SNOWBALL_LIBRARY_DIR})

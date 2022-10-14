cmake_minimum_required(VERSION 3.16)
project(snowball)


if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "User path" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE PROJECT_HEADERS include/snowball/*.h include/snowball/types/*.h include/snowball/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cc src/types/*.cc src/*.c)
file(GLOB_RECURSE PROJECT_CMAKE_UTILS cmake/*.cmake)
file(GLOB_RECURSE PROJECT_MISC *.md *.txt)
set (PROJECT_EXPORT_HPP include/${PROJECT_NAME}/export.hpp)
set (GCC_COVERAGE_COMPILE_FLAGS "-Wl,-znodelete")
set (GCC_COVERAGE_LINK_FLAGS "-rdynamic")
set (PROJECT_FILES
  ${PROJECT_HEADERS}
  ${PROJECT_SOURCES}
  ${PROJECT_CMAKE_UTILS}
  ${PROJECT_MISC}
  ${PROJECT_EXPORT_HPP}
  ${LLVM_INCLUDE_DIRS})

file(GLOB_RECURSE EXEC_HEADERS include/exec/*.h include/exec/*.hpp)
file(GLOB_RECURSE EXEC_SOURCES exec/*.cc exec/*.cc exec/*.c)
set (EXEC_FILES
  ${EXEC_HEADERS}
  ${EXEC_SOURCES})


# Map llvm components
llvm_map_components_to_libnames(llvm_libs
    Analysis
    Core
    ExecutionEngine
    InstCombine
    Object
    OrcJIT
    # RuntimeOyld
    ScalarOpts
    Support
    native
    MC
    mcjit
)

##################################################    Targets     ##################################################
add_library(snowball SHARED ${PROJECT_FILES})
add_executable(snowballexe ${EXEC_FILES})
target_link_libraries(snowballexe PUBLIC ${PROJECT_NAME})
set_target_properties(snowballexe PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

foreach(target ${LLVM_TARGETS_TO_BUILD})
  list(APPEND targets "LLVM${target}CodeGen")
endforeach()

execute_process(COMMAND gcc -dumpversion OUTPUT_VARIABLE _LIBC_VERSION)
string(REGEX REPLACE "\n" "" _LIBC_VERSION "${_LIBC_VERSION}")

set (STATICLIB_DIR "/usr/lib")
set (_SNOWBALL_LIBRARY_DIR "snowball")

add_compile_definitions(CC_PATH="/usr/bin/clang")
add_compile_definitions(LD_PATH="/usr/bin/ld")
add_compile_definitions(STATICLIB_DIR="${STATICLIB_DIR}/")

add_compile_definitions(_SNOWBALL_LIBRARY_DIR="${_SNOWBALL_LIBRARY_DIR}")

add_compile_definitions(LIBC_VERSION="${_LIBC_VERSION}")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${LLVM_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include> PRIVATE source)
    target_include_directories(${PROJECT_NAME} PUBLIC ${LLVM_INCLUDE_DIRS} ${PROJECT_INCLUDE_DIRS})
    target_link_libraries     (${PROJECT_NAME} PUBLIC ${llvm_libs} ${llvm_libraries} ${targets} ${PROJECT_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
set_target_properties     (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(NOT BUILD_SHARED_LIBS)
  string               (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
  set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -D${PROJECT_NAME_UPPER}_STATIC)
endif()

##################################################    StdLib   ##################################################
file(GLOB std_c_files "stdlib/*/*.cc")
foreach(file ${std_c_files})
  get_filename_component(lib_name ${file} NAME_WE )

    # TODO: see if this can be cleaner
  set (LIB_FILE
    ${file}
    "stdlib/_include/${lib_name}.h")

  set (lib_name "Snowball${lib_name}")

  add_library(${lib_name} SHARED ${LIB_FILE})
  target_link_libraries(${lib_name} PUBLIC ${PROJECT_NAME})

  install(TARGETS ${lib_name} EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${STATICLIB_DIR}/
    LIBRARY  DESTINATION ${STATICLIB_DIR}/
    RUNTIME  DESTINATION ${STATICLIB_DIR}/)
endforeach()

file(GLOB std_sn_files "stdlib/*/*.sn")
install(FILES ${std_sn_files} DESTINATION ${STATICLIB_DIR}/${_SNOWBALL_LIBRARY_DIR})



##################################################    Postbuild   ##################################################
include               (GenerateExportHeader)
string                (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME     ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/export.hpp
  EXPORT_MACRO_NAME    ${PROJECT_NAME_UPPER}_EXPORT
  STATIC_DEFINE        ${PROJECT_NAME_UPPER}_STATIC
)

# installation
install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS snowballexe EXPORT MyLibConfig
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
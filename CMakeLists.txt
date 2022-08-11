cmake_minimum_required(VERSION 3.16)
project(snowball)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h include/types/*.h include/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cc src/types/*.cc src/*.c)
file(GLOB_RECURSE PROJECT_CMAKE_UTILS cmake/*.cmake)
file(GLOB_RECURSE PROJECT_MISC *.md *.txt)
file(GLOB_RECURSE LIBS_HEADERS libs/*.h)
file(GLOB_RECURSE LIBS_SOURCES libs/*.cc)
set (PROJECT_EXPORT_HPP include/${PROJECT_NAME}/export.hpp)
set (GCC_COVERAGE_COMPILE_FLAGS "-Wl,-znodelete")
set (GCC_COVERAGE_LINK_FLAGS "-Wl,-znodelete")
set (PROJECT_FILES
  ${PROJECT_HEADERS}
  ${PROJECT_SOURCES}
  ${PROJECT_CMAKE_UTILS}
  ${PROJECT_MISC}
  ${PROJECT_EXPORT_HPP}
  ${LLVM_INCLUDE_DIRS})

set (SYSTEM_FILES
  ${LIBS_HEADERS}
  ${LIBS_SOURCES})

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
add_library(system_libs SHARED ${SYSTEM_FILES})

target_link_libraries(system_libs PUBLIC snowball)

add_executable(snowballexe sn/main.cc)
set_target_properties(snowballexe PROPERTIES OUTPUT_NAME "snowball")

target_link_libraries(snowballexe PUBLIC snowball)

foreach(target ${LLVM_TARGETS_TO_BUILD})
  list(APPEND targets "LLVM${target}CodeGen")
endforeach()


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

##################################################    Postbuild   ##################################################
include               (GenerateExportHeader)
string                (TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME     ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/export.hpp
  EXPORT_MACRO_NAME    ${PROJECT_NAME_UPPER}_EXPORT
  STATIC_DEFINE        ${PROJECT_NAME_UPPER}_STATIC
)

# installation
install(TARGETS system_libs EXPORT MyLibConfig DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/libs)
install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS snowballexe EXPORT MyLibConfig DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
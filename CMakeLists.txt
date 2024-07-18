
# Basic CMake configuration

cmake_minimum_required(VERSION 3.14)


# Project configuration

set(META_PROJECT_NAME        "snowball")
set(META_PROJECT_DESCRIPTION "A simple programming language")
set(META_AUTHOR_ORGANIZATION "snowball-lang")
set(META_GITHUB_REPO         "https://github.com/snowball-lang/snowball")
set(META_AUTHOR_DOMAIN       "https://github.com/snowball-lang/snowball")
set(META_AUTHOR_MAINTAINER   "Mauro Balades")
set(META_VERSION_MAJOR       "1")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")


string(MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)
string(TOLOWER ${META_PROJECT_ID} META_PROJECT_ID_LOWER)

# Determine if this is built as a subproject  or if it is the master project.
if(NOT DEFINED ${META_PROJECT_ID}_IS_MASTER_PROJECT)
  set(${META_PROJECT_ID}_IS_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(${META_PROJECT_ID}_IS_MASTER_PROJECT ON)
  endif()
endif()

# Project options 

option(BUILD_SHARED_LIBS            "Build shared instead of static libraries."              ON)
option(SNOWBALL_BUILD_TESTS         "Setup target to build and run tests."                   OFF)
option(SNOWBALL_BUILD_EXAMPLES      "Setup target to build the examples."                    OFF)
option(SNOWBALL_BUILD_DOCS          "Setup target to build the doxygen and sphinx docs."     ON)
option(SNOWBALL_WITH_VALGRIND       "Builds targets with valgrind profilers added"           OFF)
option(USE_CCACHE                   "Enable caching of compiled artifacts using ccache"      OFF)

# Generate folders for IDE targets (e.g., VisualStudio solutions)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(IDE_FOLDER "${META_PROJECT_NAME}")

# Declare project
project(
  ${META_PROJECT_NAME}
  VERSION ${META_VERSION}
  DESCRIPTION ${META_PROJECT_DESCRIPTION}
  HOMEPAGE_URL ${META_GITHUB_REPO}
  LANGUAGES C CXX)

# Set CXX standard and search for cxx modules
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define the following alias variables used by the common cmake functions
set(${PROJECT_NAME}_BUILD_TESTS ${SNOWBALL_BUILD_TESTS})
set(${PROJECT_NAME}_BUILD_EXAMPLES ${SNOWBALL_BUILD_EXAMPLES})


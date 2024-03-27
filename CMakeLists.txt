cmake_minimum_required(VERSION 3.20)
project(modmaid)

# Use C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add utility scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake")

# Add external dependencies
include(CPM)
if(WIN32)
  CPMAddPackage(NAME "minhook" GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook" GIT_TAG "master")
endif()

# Common definitions
if(WIN32)
  add_compile_definitions(OS_WINDOWS)
elseif(UNIX)
  add_compile_definitions(OS_UNIX)
endif()

# Add submodules
add_subdirectory(modmaid)
add_subdirectory(examples)
add_subdirectory(debug)

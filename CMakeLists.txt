cmake_minimum_required(VERSION 3.20)
project(modmaid)

# Use C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endif()

# Add utility scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake")
include(ModMaidUtils)
include(CPM)

# Project settings
__maid_option(MAID_BUILD_TESTS BOOL ON "Build unittests")
__maid_option(MAID_BUILD_EXAMPLES BOOL ON "Build examples")

# Add external dependencies
if(WIN32)
  CPMAddPackage(
    NAME "minhook"
    GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
    GIT_TAG "master"
  )
endif()

if(MAID_BUILD_TESTS)
  CPMAddPackage("gh:catchorg/Catch2#v3.5.3")
endif()

CPMAddPackage("gh:marzer/tomlplusplus#v3.4.0")

# Common definitions
if(WIN32)
  add_compile_definitions(OS_WINDOWS)
elseif(UNIX)
  add_compile_definitions(OS_UNIX)
endif()

# Add submodules
add_subdirectory(modules)

if(MAID_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

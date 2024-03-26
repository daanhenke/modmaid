# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-src"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-build"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/tmp"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/src/minhook-populate-stamp"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/src"
  "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/src/minhook-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/src/minhook-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Daan/maid-old/cmake-build-debug/_deps/minhook-subbuild/minhook-populate-prefix/src/minhook-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

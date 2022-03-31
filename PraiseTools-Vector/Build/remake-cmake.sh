#!/bin/bash

rm -f CMakeCache.txt cmake_install.cmake Makefile *.x86
rm -r CMakeFiles

cmake CMakeLists.txt

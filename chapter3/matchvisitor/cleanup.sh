#!/bin/sh
rm -rf build
rm -rf CMakeFiles cmake_install.cmake compile_commands.json Makefile CMakeCache.txt
find . \( -name "*.log" -o -name "*~" -o -name "*.tmp" \) -exec rm -rf {} \;

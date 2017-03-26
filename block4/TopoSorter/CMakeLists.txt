cmake_minimum_required(VERSION 3.6)
project(TopoSorter)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/TopoSorter.cpp src/TopoSorter.h)
add_executable(TopoSorter ${SOURCE_FILES})
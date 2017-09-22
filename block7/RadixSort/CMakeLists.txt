cmake_minimum_required(VERSION 3.8)
project(RadixSort)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp include/RadixSort.hpp)
add_executable(RadixSort ${SOURCE_FILES})
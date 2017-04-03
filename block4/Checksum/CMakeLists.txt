cmake_minimum_required(VERSION 3.6)
project(Checksum)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/Checksum.cpp src/Checksum.h)
add_executable(Checksum ${SOURCE_FILES})
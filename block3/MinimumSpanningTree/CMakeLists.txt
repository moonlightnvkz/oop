cmake_minimum_required(VERSION 3.6)
project(MinimumSpanningTree)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/MST.cpp src/MST.h src/DSU.cpp src/DSU.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(MinimumSpanningTree_exe ${SOURCE_FILES})

add_library(MinimumSpanningTree_lib ${SOURCE_FILES})

target_link_libraries(MinimumSpanningTree_exe gtest gtest_main)

add_subdirectory(test)

add_executable(MinimumSpanningTree ${SOURCE_FILES})
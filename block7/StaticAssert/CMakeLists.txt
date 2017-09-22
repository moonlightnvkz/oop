cmake_minimum_required(VERSION 3.8)
project(StaticAssert)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp include/StaticAssert.hpp test/StaticAssertTest.cpp)
add_executable(StaticAssert ${SOURCE_FILES})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(StaticAssert_exe ${SOURCE_FILES})
add_library(StaticAssert_lib SHARED ${SOURCE_FILES})
target_link_libraries(StaticAssert_exe gtest gtest_main)

add_subdirectory(test)
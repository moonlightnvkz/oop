cmake_minimum_required(VERSION 3.8)
project(ObjectPool)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp include/ObjectPool.hpp)
add_executable(ObjectPool ${SOURCE_FILES})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(ObjectPool_exe ${SOURCE_FILES})
add_library(ObjectPool_lib SHARED ${SOURCE_FILES})
target_link_libraries(ObjectPool_exe gtest gtest_main)

add_subdirectory(test)
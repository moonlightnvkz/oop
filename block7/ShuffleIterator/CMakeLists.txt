cmake_minimum_required(VERSION 3.8)
project(ShuffleIterator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp
        include/shuffle_range.h
        )

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(ShuffleIterator_exe ${SOURCE_FILES})
add_library(ShuffleIterator_lib SHARED ${SOURCE_FILES})
target_link_libraries(ShuffleIterator_exe gtest gtest_main)

add_subdirectory(test)

add_executable(ShuffleIterator ${SOURCE_FILES} test/shuffle_range_test.cpp)
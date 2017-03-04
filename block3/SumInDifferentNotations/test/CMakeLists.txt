cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicTest
        RadixTranslation_test.cpp)

target_link_libraries(runBasicTest gtest gtest_main)
target_link_libraries(runBasicTest SumInDifferentNotations_lib)
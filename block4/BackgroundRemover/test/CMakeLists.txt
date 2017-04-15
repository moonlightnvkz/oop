cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RunAllTests
        GaussianTest.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(RunAllTests ${OpenCV_LIBS})

target_link_libraries(RunAllTests gtest gtest_main)
target_link_libraries(RunAllTests BackgroundRemover_lib)
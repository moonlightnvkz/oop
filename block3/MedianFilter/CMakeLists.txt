cmake_minimum_required(VERSION 3.6)
project(MedianFilter_exe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/MedianFilter.cpp src/MedianFilter.h)

add_executable(MedianFilter_exe src/main.cpp ${SOURCE_FILES})
add_library(MedianFilter_lib SHARED ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(MedianFilter_exe ${OpenCV_LIBS})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(MedianFilter_exe gtest gtest_main)

add_subdirectory(test)
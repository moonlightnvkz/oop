cmake_minimum_required(VERSION 3.6)
project(MedianFilter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/MedianFilter.cpp src/MedianFilter.h)
add_executable(MedianFilter ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(MedianFilter ${OpenCV_LIBS})
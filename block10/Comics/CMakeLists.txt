cmake_minimum_required(VERSION 3.8)
project(Comics)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp src/CartoonFilter.cpp src/CartoonFilter.h)
add_executable(Comics ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Comics ${OpenCV_LIBS})
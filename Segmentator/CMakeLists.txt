cmake_minimum_required(VERSION 3.7)
project(Segmentator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/GaussianFilter.cpp src/GaussianFilter.h src/GraphSegmentator.cpp src/GraphSegmentator.h
        src/ImageSegmentator.cpp src/ImageSegmentator.h)
add_executable(Segmentator ${SOURCE_FILES})


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Segmentator ${OpenCV_LIBS})

include_directories(${PROJECT_SOURCE_DIR}/lib/MST/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/MST/lib)
target_link_libraries(Segmentator ${PROJECT_SOURCE_DIR}/lib/MST/lib/libMinimumSpanningTree_lib.so)
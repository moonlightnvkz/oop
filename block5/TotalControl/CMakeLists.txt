cmake_minimum_required(VERSION 3.7)
project(TotalControl)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp
        src/VisitsListReader.cpp src/VisitsListReader.h
        src/User.cpp src/User.h
        src/Timestamp.cpp src/Timestamp.h
        src/Crowd.cpp src/Crowd.h
        src/CrowdFinder.cpp src/CrowdFinder.h
        src/Location.cpp src/Location.h
        src/LocationsSplitter.cpp src/LocationsSplitter.h)


add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(TotalControl_exe ${SOURCE_FILES})
add_library(TotalControl_lib SHARED ${SOURCE_FILES})
target_link_libraries(TotalControl_exe gtest gtest_main)

add_subdirectory(test)
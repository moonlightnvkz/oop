cmake_minimum_required(VERSION 3.7)
project(TotalControl)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp
        src/VisitsListReader.cpp include/VisitsListReader.h
        src/User.cpp include/User.h
        src/Timestamp.cpp include/Timestamp.h
        src/Crowd.cpp include/Crowd.h
        src/CrowdFinder.cpp include/CrowdFinder.h
        src/Location.cpp include/Location.h
        )


add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(TotalControl_exe ${SOURCE_FILES})
add_library(TotalControl_lib SHARED ${SOURCE_FILES})
target_link_libraries(TotalControl_exe gtest gtest_main)

add_subdirectory(test)
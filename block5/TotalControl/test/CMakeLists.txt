cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(RunAllTests
        Timestamp_test.cpp VisitsListReader_test.cpp LocationsSplitter_test.cpp CrowdMaxAvg_test.cpp CrowdFinder_test.cpp)

target_link_libraries(RunAllTests gtest gtest_main)
target_link_libraries(RunAllTests TotalControl_lib)
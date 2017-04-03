cmake_minimum_required(VERSION 3.6)
project(TopoSorter)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Winvalid-pch -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-nonliteral -Wmissing-include-dirs -Wredundant-decls")

set(SOURCE_FILES src/main.cpp src/TopoSorter.cpp src/TopoSorter.h src/TopoSorterParser.cpp src/TopoSorterParser.h test/toposorter_test.cpp)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(TopoSorter_exe ${SOURCE_FILES} src/TopoSorterParser.cpp src/TopoSorterParser.h)
add_library(TopoSorter_lib ${SOURCE_FILES})
target_link_libraries(TopoSorter_exe gtest gtest_main)

#include_directories(lib/libtokenizer)
#link_directories(lib/libtokenizer)
#target_link_libraries(TopoSorter_exe libtokenizer.a)

add_subdirectory(test)
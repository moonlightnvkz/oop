cmake_minimum_required(VERSION 3.6)
project(SumInDifferentNotations)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/RadixTranslation.cpp src/RadixTranslation.h src/DiffRadixPlus.cpp src/DiffRadixPlus.h)
add_executable(SumInDifferentNotations ${SOURCE_FILES})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(SumInDifferentNotations_exe ${SOURCE_FILES})

add_library(SumInDifferentNotations_lib ${SOURCE_FILES})

target_link_libraries(SumInDifferentNotations_exe gtest gtest_main)

add_subdirectory(test)
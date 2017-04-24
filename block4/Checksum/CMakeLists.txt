cmake_minimum_required(VERSION 3.6)
project(Checksum)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/Checksum.cpp src/Checksum.h
        src/ArgumentsParser.cpp src/ArgumentsParser.h
        src/ManifestReader.cpp src/ManifestReader.h
        src/ManifestWriter.cpp src/ManifestWriter.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(Checksum_exe src/main.cpp ${SOURCE_FILES})
add_library(Checksum_lib SHARED ${SOURCE_FILES})

target_link_libraries(Checksum_exe gtest gtest_main)

add_subdirectory(test)
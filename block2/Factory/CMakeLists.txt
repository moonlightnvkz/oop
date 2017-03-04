cmake_minimum_required(VERSION 3.6)
project(Factory)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c
        src/circle.h
        src/circle.c
        src/new.h
        src/new.c
        src/point.h
        src/point.c
        src/rect.c
        src/rect.h
        src/line.c
        src/line.h
        src/objects.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(Factory_exe ${SOURCE_FILES})

add_library(Factory_lib ${SOURCE_FILES})

target_link_libraries(Factory_exe gtest gtest_main)

add_subdirectory(test)
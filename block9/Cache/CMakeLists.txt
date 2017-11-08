cmake_minimum_required(VERSION 3.8)
project(Cache)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        src/Cache.cpp
        include/Cache.h)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(Cache_exe ${SOURCE_FILES})
add_library(Cache_lib SHARED ${SOURCE_FILES})
target_link_libraries(Cache_exe gtest gtest_main)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Cache_lib PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Cache_lib PUBLIC DEBUG=0)
endif()

add_subdirectory(test)
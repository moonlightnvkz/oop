cmake_minimum_required(VERSION 3.8)
project(Trie)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS -Wall )

set(SOURCE_FILES src/main.cpp include/Trie.hpp)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(Trie_exe ${SOURCE_FILES})
add_library(Trie_lib SHARED ${SOURCE_FILES})
target_link_libraries(Trie_exe gtest gtest_main)

add_subdirectory(test)
cmake_minimum_required(VERSION 3.8)
project(Trie)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp include/Trie.hpp)
add_executable(Trie ${SOURCE_FILES})
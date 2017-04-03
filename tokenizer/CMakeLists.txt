cmake_minimum_required(VERSION 3.7)
project(tokenizer)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -Wformat=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Winvalid-pch -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-nonliteral -Wmissing-include-dirs -Wredundant-decls")

set(SOURCE_FILES main.cpp Tokenizer.cpp Tokenizer.h)
add_library(tokenizer ${SOURCE_FILES})
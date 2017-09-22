cmake_minimum_required(VERSION 3.8)
project(MyVariant)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        include/variant.hpp
        )
add_executable(MyVariant ${SOURCE_FILES})
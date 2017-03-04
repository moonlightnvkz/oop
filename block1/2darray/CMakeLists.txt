cmake_minimum_required(VERSION 3.6)
project(2darray)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Array2D.c Array2D.h tests_Array2D.c tests_Array2D.h)
add_executable(2darray ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.8)
project(C__HTMLLinter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp include/IWritable.h include/Writable.cpp include/Writable.h include/HTMLDecorator.cpp include/HTMLDecorator.h include/LineDecorator.cpp include/LineDecorator.h include/IWritableDecorator.h include/CppDecorator.cpp include/CppDecorator.h include/WordFinder.cpp include/WordFinder.h include/CodeReviewDecorator.cpp include/CodeReviewDecorator.h)
add_executable(C__HTMLLinter ${SOURCE_FILES})
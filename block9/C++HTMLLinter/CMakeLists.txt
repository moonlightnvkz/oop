cmake_minimum_required(VERSION 3.8)
project(C__HTMLLinter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp include/IWritable.h src/Writable.cpp include/Writable.h src/HTMLDecorator.cpp include/HTMLDecorator.h src/LineDecorator.cpp include/LineDecorator.h include/IWritableDecorator.h src/CppDecorator.cpp include/CppDecorator.h src/WordFinder.cpp include/WordFinder.h src/CodeReviewDecorator.cpp include/CodeReviewDecorator.h)
add_executable(C__HTMLLinter ${SOURCE_FILES})
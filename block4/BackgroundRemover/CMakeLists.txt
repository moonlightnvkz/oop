cmake_minimum_required(VERSION 3.7)
project(BackgroundRemover)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -Wformat=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Winvalid-pch -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-nonliteral -Wmissing-include-dirs -Wredundant-decls")


set(SOURCE_FILES
        src/GaussianFilter.cpp src/GaussianFilter.h
        src/BackgroundRemover.cpp src/BackgroundRemover.h
        src/LuminosityHistogram.cpp src/LuminosityHistogram.h
        src/BalancedHistogramThresholder.cpp src/BalancedHistogramThresholder.h
        )

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (GUI_SOURCES src/MainWindow.cpp src/MainWindow.h src/mainwindow.ui)

add_executable(BackgroundRemover_exe src/main.cpp ${SOURCE_FILES} ${GUI_SOURCES} test/GaussianTest.cpp)
add_library(BackgroundRemover_lib SHARED ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(BackgroundRemover_exe ${OpenCV_LIBS})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(BackgroundRemover_exe gtest gtest_main)

add_subdirectory(test)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

target_link_libraries(BackgroundRemover_exe Qt5::Core Qt5::Widgets Qt5::Gui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(RunAllTests
        TrieTest.cpp)

target_link_libraries(RunAllTests gtest gtest_main)
target_link_libraries(RunAllTests Trie_lib)
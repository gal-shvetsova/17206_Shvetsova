cmake_minimum_required(VERSION 3.6)
project(sort_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tests.cpp Reference.cpp Trit_Iterator.cpp Other.h TritSet.h TritSet.cpp)
add_executable(trit_test ${SOURCE_FILES})

add_subdirectory(googletest-master)

target_link_libraries( trit_test gtest gtest_main)


cmake_minimum_required(VERSION 3.17)
project(hw_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -lm)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(source)
include_directories(includes)

add_executable(hw_2.out source/main.c includes/tuple.h source/tuple.c)
target_link_libraries(hw_2.out PRIVATE m)

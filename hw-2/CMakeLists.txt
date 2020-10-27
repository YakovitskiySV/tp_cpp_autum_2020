cmake_minimum_required(VERSION 3.17)
project(hw_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-g -Wall -Werror -Wextra -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(source)
include_directories(includes)

add_library(single_proc STATIC
        includes/tuple.h
        source/tuple.c
        includes/single-process.h
        source/single-process.c)

add_library(multi_proc SHARED
        includes/tuple.h
        source/tuple.c
        includes/multi-process.h
        source/multi-process.c)

add_executable(hw_2.out source/main.c)

add_executable(tests.out tests/tests.cpp)

target_include_directories(tests.out PUBLIC includes)

target_link_libraries(tests.out
        ${GTEST_LIBRARIES}
        Threads::Threads
        pthread
        single_proc
        multi_proc)

target_link_libraries(hw_2.out
        single_proc
        multi_proc
        m)  # m для math.h

enable_testing()
add_test(NAME gtest COMMAND tess.out)

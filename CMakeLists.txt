cmake_minimum_required(VERSION 2.8.12.2)
project(IZ-1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror ")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(${SOURCES_DIR})


add_executable(iz1.out
        ${SOURCES_DIR}/main.c
        ${SOURCES_DIR}/pet.c
        ${INCLUDES_DIR}/pet.h)
target_include_directories(iz1.out PUBLIC ${INCLUDES_DIR})

add_executable(tests.out
        ${TESTS_DIR}/tests.cpp
        ${SOURCES_DIR}/pet.c
        ${INCLUDES_DIR}/pet.h)
target_include_directories(tests.out PUBLIC ${INCLUDES_DIR})

target_link_libraries(tests.out
        ${GTEST_LIBRARIES}
        Threads::Threads)

enable_testing()
add_test(tests "./tests")
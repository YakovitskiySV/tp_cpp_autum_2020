cmake_minimum_required(VERSION 2.8.12.2)
project(IZ-1 C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCC)
    option(ENABLE_COVERAGE "Enable coverage for gcc/clang" TRUE)

    if(ENABLE_COVERAGE)
        add_compile_options(--coverage -O0)
    endif()
endif()

set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(${SOURCES_DIR})

# Создание iz1.out (самой программы из условия ИЗ-1)
add_executable(iz1.out
        ${SOURCES_DIR}/main.c
        ${SOURCES_DIR}/pet.c
        ${INCLUDES_DIR}/pet.h)

target_include_directories(iz1.out PUBLIC
        ${INCLUDES_DIR})

# Создание tests.out (тесты написанные при помощи gtest)
add_executable(tests.out
        ${TESTS_DIR}/tests.cpp
        ${SOURCES_DIR}/pet.c
        ${INCLUDES_DIR}/pet.h)

target_include_directories(tests.out PUBLIC
        ${INCLUDES_DIR})

target_link_libraries(tests.out PUBLIC
        ${GTEST_LIBRARIES}
         pthread
        --coverage)

enable_testing()
add_test(tests "./tests")
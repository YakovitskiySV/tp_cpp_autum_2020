cmake_minimum_required(VERSION 3.17)
project(IZ-1)

set(CMAKE_C_STANDARD 99)

include_directories("${PROJECT_SOURCE_DIR}/includes")
include_directories("${PROJECT_SOURCE_DIR}/source")

file(GLOB
        SOURCES "source/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
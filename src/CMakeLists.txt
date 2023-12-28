cmake_minimum_required(VERSION 3.10)
project(lab1_os)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR $(CMAKE_CURRENT_SOURCE_DIR)/../include)

include_directories(${INCLUDE_DIR})

add_executable(child_1 child_1.c function.c)
add_executable(child_2 child_2.c function.c)
add_executable(main main.c function.c)
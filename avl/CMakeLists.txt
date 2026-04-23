cmake_minimum_required(VERSION 3.15)
project(AVLTree CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(test_avl
    tests/test_avl.cpp
    src/avl.cpp
)
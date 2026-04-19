cmake_minimum_required(VERSION 3.14)
project(BinarySearchTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)

add_library(bst_lib
    src/bst.cpp
)
target_include_directories(bst_lib PUBLIC include)

add_executable(test_bst
    tests/test_bst.cpp
)
target_link_libraries(test_bst PRIVATE bst_lib)

enable_testing()
add_test(NAME BSTTests COMMAND test_bst)
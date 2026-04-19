# Binary Seach Tree - C++

A clean, recursive implementation of a Binary Search Tree (BST) in modern C++17.

## Features

| Operation | Complexity |
| --- | --- |
| 'insert(val)' | O(h) |
| 'search(val)' | O(h) |
| 'remove(val)' | O(h) |
| 'inorder()' | O(n) |
| 'height()' | O(n) |

*h = tree height; O(log n) average, O(n) worst case (degenerate/sorted input). *

## Build & Run

'''bash
mkdir build && cd build
cmake ..
make

# Run tests directly
./test_bst

# Or via CTest
ctest --output-on-failure
'''
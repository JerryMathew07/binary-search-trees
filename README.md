# Trees — C++ Data Structures

A progression from a plain Binary Search Tree to a 
self-balancing AVL tree, showing why balancing matters
and how to fix it.

## Projects

### bst/
Plain Binary Search Tree with recursive insert, search,
delete (all 3 cases), and traversals.

### avl/
Generic self-balancing AVL tree with O(log n) guaranteed
operations, subtree-size augmentation for order-statistics
queries (kthSmallest, rank), and template interface
compatible with any comparable type.

## The Problem BST → AVL Solves
Sorted insert into a plain BST degrades to O(n) — it
becomes a linked list. AVL guarantees O(log n) always
by rebalancing after every insert and delete.

## Build
mkdir build && cd build
cmake ..
make
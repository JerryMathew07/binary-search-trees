# AVL Tree — C++

A self-balancing Binary Search Tree in C++17. Guarantees O(log n) insert,
search, and delete by maintaining the AVL invariant after every operation.
Augmented with subtree sizes for O(log n) order-statistics queries.

## Features

| Operation | Complexity |
|---|---|
| `insert(key)` | O(log n) |
| `search(key)` | O(log n) |
| `remove(key)` | O(log n) |
| `kthSmallest(k)` | O(log n) |
| `rank(key)` | O(log n) |
| `inorder / preorder / postorder` | O(n) |
| `height()` | O(1) |

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./test_avl
```
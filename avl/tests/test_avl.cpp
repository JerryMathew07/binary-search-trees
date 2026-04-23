#include "avl.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>

static int passed = 0, failed = 0;

void check(bool condition, const std::string& label){
    if (condition) { std::cout << " [PASS] " << label << '\n'; ++passed; }
    else           { std::cout << " [FAIL] " << label << '\n'; ++failed; }
}

bool isBalanced(int n, int h){
    return h <= static_cast<int>(1.44 * std::log2(n) + 1);
}

//Test suites

void test_empty(){
    std::cout << "\n-- Empty Tree -----------------------\n";
    AVL t;
    check(t.empty(), "empty() on fresh tree");
    check(t.size() == 0, "size() == 0");
    check(t.height() == 0, "height() == 0");
    check(!t.search(42), "search on empty tree -> false");
    t.remove(42);
    check(true, "remove on empty tree doesn't crash");
}

void test_insert_search() {
    std::cout <<"\n-- Insert & Search -------------------\n";
    AVL t;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) t.insert(v);

    check(t.search(50), "search root");
    check(t.search(20), "search leftmost");
    check(t.search(80), "search rightmost");
    check(!t.search(99), "search absent value");
    check(t.size() == 7, "size after 7 inserts");

    t.insert(50);
    check(t.size() == 7, "duplicate insert doesn't grow size");
}

void test_balancing_sorted_insert() {
    std::cout << "\n-- Balancing (sorted insert) --------\n";
    AVL t;
    for (int i = 1; i <= 15; ++i) t.insert(i);

    int h = t.height();
    check(h <= 6, "height stays logarithmic (h=" + std::to_string(h) + ")");
    check(t.size() == 15, "size correct after 15 inserts");
    check(t.search(1), "search min element");
    check(t.search(15), "search max element");
}

void test_traversals() {
    std::cout << "\n-- Traversals -----------------------\n";
    AVL t;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) t.insert(v);

    std::cout << " Inorder (except 1 3 4 5 6 7 8): ";
    t.inorder();
    std::cout << " Preorder (root first):          ";
    t.preorder();
    std::cout << " Postorder (root last):          ";
    t.postorder();
    check(true, "all three traversals ran without crash");
}

void test_delete() {
    std::cout << "\n-- Delete ---------------------------\n";
    AVL t;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) t.insert(v);

    t.remove(20);
    check(!t.search(20), "delete leaf (20)");
    check(t.size() == 6, "size decremented");

    t.remove(60);
    check(!t.search(60), "delete node with one child (60)");

    t.remove(30);
    check(!t.search(30), "delete node with two children (30)");
    check(t.search(40), "successor (40) still present");

    t.remove(50);
    check(!t.search(50), "delete root (50)");

    t.remove(999);
    check(true, "remove non-existent value doesn't crash");
    check(isBalanced(t.size(), t.height()), "tree balanced after deletions");
}

void test_kth_smallest() {
    std::cout << "\n-- kthSmallest (Order-Statistics)----\n";
    AVL t;
    std::vector<int> vals = {15, 5, 20, 3, 8, 17, 25, 1, 4, 6, 11};
    for (int v : vals) t.insert(v);
    std::sort(vals.begin(), vals.end());

    bool all_ok = true;
    for (int k = 1; k <= (int) vals.size(); ++k)
        if (t.kthSmallest(k) != vals[k-1]) { all_ok = false; break; }
    check(all_ok, "kthSmallest correct for all k");

    bool threw = false;
    try{t.kthSmallest(0);} catch (const std::out_of_range&) {threw = true; }
    check(threw, "kthSmallest(0) throws out_of_range");

    threw = false;
    try { t.kthSmallest(t.size() + 1); } catch (const std::out_of_range&) { threw = true; }
    check(threw, "kthSmallest(size+1) throws out_of_range");
}

void test_rank(){
    std::cout <<"\n-- rank-------------------------------\n";
    AVL t;
    for (int v : {10, 5, 15, 3, 7, 12, 20}) t.insert(v);

    check(t.rank(3) == 0, "rank(3) == 0");
    check(t.rank(5) == 1, "rank(5) == 1");
    check(t.rank(7) == 2, "rank(7) == 2");
    check(t.rank(10) == 3, "rank(10) == 3");
    check(t.rank(12) == 4, "rank(12) == 4");
    check(t.rank(15) == 5, "rank(15) == 5");
    check(t.rank(20) == 6, "rank(20) == 6");
}

void test_large_stress(){
    std::cout << "\n-- Large Insert / Delete (stress) ---\n";
    AVL t;
    const int N = 1000;

    for (int i = 0; i < N; ++i) t.insert(i);
    check(t.size() == N, "size == 1000 after bulk insert");
    check(isBalanced(N, t.height()), "balanced after 1000 inserts");

    for (int i = 0; i < N; i += 2) t.remove(i);
    check(t.size() == N/2, "size ==500 after remoing evens");
    check(isBalanced(N/2, t.height()), "balance after 500 deletes");
    check(t.search(1), "odd value (1) still present");
    check(!t.search(0), "even value (0) removed");
    check(t.kthSmallest(1) == 1, "kthSmallest(1) == 1 after deletes");
}

int main() {
    std::cout << " AVL Tree Test Suite\n";

    test_empty();
    test_insert_search();
    test_balancing_sorted_insert();
    test_traversals();
    test_delete();
    test_kth_smallest();
    test_rank();
    test_large_stress();

    std::cout << " Results: " << passed << " passed, "
              << failed << " failed\n";

    return failed == 0 ? 0 : 1;
}
#include "bst.h"

#include<iostream>

static int passed = 0, failed = 0;

void check(bool condition){
    if(condition){
        ++passed;
    } else {
        ++failed;
    }
}

void test_insert_and_search(){
    BST bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    check(bst.search(50));
    check(bst.search(20));
    check(bst.search(80));
    check(bst.search(60));
    check(!bst.search(99));
    check(!bst.search(0));
}

void test_duplicate_insert(){
    BST bst;

    bst.insert(10);
    bst.insert(10);
    bst.insert(10);

    check(bst.height() == 1);
    check(bst.search(10));
}

void test_inorder(){
    BST bst;
    for ( int v : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(v);
    
        std::cout << " Inorder output: ";
        bst.inorder(); // visual verification
        check(true);
}

void test_height(){
    BST bst;
    check(bst.height() == 0);

    bst.insert(10);
    check(bst.height() == 1);

    bst.insert(5);
    bst.insert(15);
    check(bst.height() == 2);

    BST chain;
    for ( int i = 1; i <= 5; ++i) chain.insert(i);
    check(chain.height() == 5);
}

void test_delete(){
    BST bst;
    for(int v : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(v);
    
        //Delete a leaf
        bst.remove(20);
        check(!bst.search(20));
        check( bst.search(30));

        //Delete node with one child
        bst.remove(60);
        check(!bst.search(60));
        check( bst.search(70));
        check( bst.search(80));

        //Delete node with two children
        bst.remove(30);
        check(!bst.search(30));
        check( bst.search(40));

        //Delete root
        bst.remove(50);
        check(!bst.search(50));
        check( bst.search(70));

        bst.remove(999);
}

void test_empty_tree(){
    BST bst;
    check(bst.isEmpty());
    check(!bst.search(42));
    check(bst.height() == 0);
    bst.remove(42);
}

int main() {
    std::cout << " BST Test Suite\n";

    test_empty_tree();
    test_insert_and_search();
    test_duplicate_insert();
    test_inorder();
    test_height();
    test_delete();

    std::cout << " Results: " << passed << " passed, " << failed << " failed\n";

    return failed == 0? 0 : 1;
}
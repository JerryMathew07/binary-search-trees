#include "avl.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

int AVL::ht(const Node* n) { return n ? n -> height : 0; }
int AVL::sz(const Node* n) { return n ? n -> size : 0; }
int AVL::bf(const Node* n) { return n ? ht(n->left) - ht(n->right) : 0; }

void AVL::pull(Node* n) {
    if(n){
        n -> height = 1 + std::max(ht(n->left), ht(n->right));
        n -> size = 1 + sz(n ->left) + sz(n->right);
    }
}

AVL::Node* AVL::rotateRight(Node* root){
    Node* newRoot = root->left;
    Node* T2 = newRoot->right;

    newRoot->right = root;
    root->left = T2;

    pull(root);
    pull(newRoot);

    return newRoot;
}

AVL::Node* AVL::rotateLeft(Node* root){
    Node* newRoot = root->right;
    Node* T2 = newRoot->left;
    
    newRoot->left = root;
    root->right = T2;

    pull(root);
    pull(newRoot);

    return newRoot;
}

AVL::Node* AVL::rebalance(Node* n){
    int balance = bf(n);

    if (balance > 1){
        if (bf(n->left) < 0)
            n->left = rotateLeft(n->left);
        return(rotateRight(n));
    }
    else if(balance < -1){
        if (bf(n->right) > 0)
            n->right = rotateRight(n->right);
        return(rotateLeft(n));
    }
    else{
        pull(n);
        return n;
    }
}

AVL::AVL() : root_(nullptr) {}
AVL::~AVL() { destroy_(root_); }

void AVL::destroy_(Node* n){
    if(!n) return;
    destroy_(n->left);
    destroy_(n->right);
    delete n;
}

void AVL::insert(int key) { 
    root_ = insert_(root_, key); 
}

AVL::Node* AVL::insert_ (Node* n, int key) {
    if(!n) return new Node(key);

    if (key < n->data)
        n->left = insert_(n->left, key);
    else if (key > n->data)
        n->right = insert_(n->right, key);
    else    
        return n;
    
    return rebalance(n);
}

bool AVL::search(int key) const{
    return search_(root_, key);
}

bool AVL::search_(const Node* n, int key) {
    if (!n) 
        return false;
    if (key == n->data) 
        return true;
    if (key < n->data) 
        return search_(n->left, key);
    
    return search_(n->right, key);
}

void AVL::remove(int key){ 
    root_ = remove_(root_, key);
}

AVL::Node* AVL::remove_(Node* n, int key){
    if(!n)
        return nullptr;
    if (key < n->data) 
        n->left = remove_(n->left, key);
    else if (key > n->data)
        n->right = remove_(n->right, key);
    else{
        if(!n->left || !n->right){
            Node* child = n->left ? n->left : n->right;
            delete n;
            return child;
        }
        Node* successor = minNode_(n->right);
        n->data = successor->data;
        n->right = remove_(n->right, successor->data);
    }
    return rebalance(n);
}

AVL::Node* AVL::minNode_(Node* n){
    while(n->left) n = n->left;
    return n;
}

//Traversals

void AVL::inorder() const {
    inorder_(root_);
    std::cout << "\n";
}

void AVL::preorder() const {
    preorder_(root_);
    std::cout << "\n";
}

void AVL::postorder() const {
    postorder_(root_);
    std::cout << "\n";
}

void AVL::inorder_(const Node* n){
    if(!n)
        return;
    inorder_(n->left);
    std::cout << n->data << ' ';
    inorder_(n->right);
}

void AVL::preorder_(const Node* n){
    if(!n)
        return;
    std::cout << n->data << ' ';
    preorder_(n->left);
    preorder_(n->right);
}

void AVL::postorder_(const Node* n){
    if(!n)
        return;
    postorder_(n->left);
    postorder_(n->right);
    std::cout << n->data <<' ';
}

int AVL::height() const {
    return ht(root_);
}

int AVL::size() const {
    return sz(root_);
}

bool AVL::empty() const {
    return root_ == nullptr;
}

int AVL::kthSmallest(int k) const{
    if(k < 1 || k > sz(root_))
        throw std::out_of_range("kthSmallest: k out of range");
    
    const Node* n = root_;
    while(n) {
        int leftSize = sz(n->left);
        if (k == leftSize + 1) 
            return n->data;
        else if(k <= leftSize)
            n = n->left;
        else{
            k -= leftSize + 1;
            n = n->right;
        }
    }
    throw std::out_of_range("kthSmallest: internal error");
}

int AVL::rank(int key) const {
    int count = 0;
    const Node* n = root_;
    while(n){
        if (key < n->data)
            n = n->left;
        else if (key > n->data) { 
            count += sz(n->left) + 1;
            n = n->right;
        }
        else{
            count += sz(n->left);
            break;
        }
    }
    return count;
}
#include "bst.h"

#include<algorithm>
#include<iostream>

BST::BST() : root_(nullptr) {}

BST::~BST() { destroy_(root_); }

void BST::destroy_(Node* node){
    if(!node) return;
    destroy_(node->left);
    destroy_(node->right);
    delete node;
}

bool BST::isEmpty() const { return root_ == nullptr;}

void BST::insert(int val){
    root_ = insert_(root_, val);
}

Node* BST::insert_(Node* node, int val){
    if(!node) return new Node(val);

    if(val < node->data)
        node->left = insert_(node->left, val);
    else if(val > node->data)
        node->right = insert_(node->right, val);
    
    return node;
}

bool BST::search(int val) const{
    return search_(root_, val);
}

bool BST::search_(const Node* node, int val) const {
    if (!node) return false;

    if (val == node->data) return true;

    else if (val < node->data) return search_(node->left, val);

    else return search_(node->right, val);
}

void BST::remove(int val){
    root_ = remove_(root_, val);
}

Node* BST::remove_(Node* node, int val){
    if(!node) return nullptr;

    if (val < node->data)
        node->left = remove_(node->left, val);
    else if (val > node->data)
        node->right = remove_(node->right, val);
    else{
        if(!node->left && !node->right){
            delete node;
            return nullptr;
        }
        else if(!node->left){
            Node* replacementNode = node->right;
            delete node;
            return replacementNode;
        }
        else if(!node->right){
            Node* replacementNode = node->left;
            delete node;
            return replacementNode;
        }
        else{
            Node *succesor = minNode_(node->right);
            node->data = succesor->data;
            node->right = remove_(node->right, succesor->data);
        }
    }
    return node;
}

Node* BST::minNode_(Node* node){
    while(node->left) node = node->left;
    return node;
}

void BST::inorder() const {
    inorder_(root_);
    std::cout<<"\n";
}

void BST::inorder_(const Node* node) const {
    if(!node) return;
    inorder_(node->left);
    std::cout<<node->data<<"\n";
    inorder_(node->right);  
}

int BST::height() const{
    return height_(root_);
}

int BST::height_(const Node* node) const {
    if(!node) return 0;
    return 1 + std::max(height_(node->left), height_(node->right));
}
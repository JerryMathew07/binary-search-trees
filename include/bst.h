#pragma once

struct Node{
    int data;
    Node *left;
    Node *right;

    explicit Node(int val) : data(val), left(nullptr), right(nullptr){}
};

class BST {
    public:
        BST();
        ~BST();

        void insert(int val);
        bool search(int val) const;
        void remove(int val);

        void inorder() const;
        int height() const;
        bool isEmpty() const;

    private:

        Node* root_;

        Node* insert_(Node* node, int val);
        bool search_(const Node* node, int val) const;
        Node* remove_(Node* node, int val);
        void inorder_(const Node* node) const;
        int height_(const Node* node) const;
        void destroy_(Node* node);

        static Node* minNode_(Node* node);
};
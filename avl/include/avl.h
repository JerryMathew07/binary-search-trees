#pragma once

class AVL {
    public:
        AVL();
        ~AVL();

        AVL(const AVL&) = delete;
        AVL& operator= (const AVL&) = delete;

        //Core operations
        void insert(int key);
        bool search(int key) const;
        void remove(int key);

        //Traversals
        void preorder() const;
        void inorder() const;
        void postorder() const;

        //Metrics
        int height() const;
        int size() const;
        bool empty() const;

        //order-statics
        int kthSmallest(int k) const;
        int rank(int key) const;
    
    private:
        struct Node{
            int data;
            int height;
            int size;
            Node* left;
            Node* right;

            explicit Node(int val)
                : data(val), height(1), size(1), left(nullptr), right(nullptr) {}
        };

    Node* root_;

    //Helpers
    static int ht(const Node* n);
    static int sz(const Node* n);
    static int bf(const Node* n);
    static void pull(Node* n);

    //Rotations
    static Node* rotateRight(Node* n);
    static Node* rotateLeft (Node* n);

    //Rebalance
    static Node* rebalance(Node* n);

    //Recursive workers
    static Node* insert_ (Node* n, int key);
    static bool search_ (const Node* n, int key);
    static Node* remove_ (Node* n, int key);
    static void inorder_ (const Node* n);
    static void preorder_ (const Node* n);
    static void postorder_ (const Node* n);
    static void destroy_ (Node* n);
    static Node* minNode_ (Node* n);
};
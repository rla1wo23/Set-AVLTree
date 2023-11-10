#include <iostream>

struct Node
{
    int key;
    int height;
    Node *left;
    Node *right;
};

class AVLTree
{
private:
    Node *root;
    int height(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T = x->right;
        x->right = y;
        y->left = T;
        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));
        return x;
    }
    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T = y->left;
        y->left = x;
        x->right = T;
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;
    }
    Node *insert(Node *node, int key){};
    Node *findMinNode(Node *node){};
    Node *erase(Node *node, int key){};
    int findDepth(Node *node, int key, int depth){};
    int findRank(Node *node, int key){};

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void insert(int key);
    void erase(int key);
    int find(int key);
    int rank(int key);
    void minimum();
    void maximum();
    bool empty();
    int size();

private:
    int number_of_nodes_ = 0;
};

AVLTree::~AVLTree()
{
}

void AVLTree::insert(int key)
{
}

void AVLTree::erase(int key)
{
}

int AVLTree::find(int key)
{
}

int AVLTree::rank(int key)
{
}

void AVLTree::minimum()
{
}

void AVLTree::maximum()
{
}

bool AVLTree::empty()
{
}

int AVLTree::size()
{
}

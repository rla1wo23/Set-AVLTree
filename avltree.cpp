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
    int Height(Node *node)
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
        return Height(node->left) - Height(node->right);
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T = x->right;
        x->right = y;
        y->left = T;
        y->height = 1 + std::max(Height(y->left), Height(y->right));
        x->height = 1 + std::max(Height(x->left), Height(x->right));
        return x;
    }
    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T = y->left;
        y->left = x;
        x->right = T;
        x->height = 1 + std::max(Height(x->left), Height(x->right));
        y->height = 1 + std::max(Height(y->left), Height(y->right));

        return y;
    }
    Node *insert(Node *node, int key){};
    Node *findMinNode(Node *node){};
    Node *findMaxNode(Node *node){};
    Node *erase(Node *node, int key){};
    int findDepth(Node *node, int key, int depth){};
    int findRank(Node *node, int key){};

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void insert(int key);
    void erase(int key);
    void find(int key)
    {
        int depth = findDepth(root, key, 1);
        std::cout << depth << std::endl;
    }
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

#include <algorithm>
#include <iostream>

struct Node
{
    int key;
    int height = 1;
    Node *left = nullptr;
    Node *right = nullptr;
};

class AVLTree
{
public:
    Node *root_;
    Node *FindNodePtr(int find_target) // 찾고자 하는 노드의 포인터를 반환합니다.
    {
        Node *iterator = root_;
        while (iterator != nullptr && iterator->key != find_target)
        {
            iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
        }
        return iterator;
    }
    // 재귀적으로 Node를 삽입하려는 것으로, 현재 탐색하는 노드의 위치를 노드 포인터형으로 반환합니다.
    Node *InsertNode(Node *iterator, int key_of_new_node){};
    // 노드를 삭제합니다.
    Node *EraseNode(Node *root_node, int item){};

    void DoBalncing(Node *&root, int target_key) // root노드와 어떤 키를 기준으로 Roating하는지를 정의합니다.
    {
        int balance_factor = CalculateBalance(root);
        if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1)
        {
            return;
        }
        if (balance_factor > 1 && target_key < root->left->key)
        {
            root = RightRotation(root);
        }
        else if (balance_factor > 1 && target_key > root->left->key)
        {
            root->left = LeftRotation(root->left);
            root = RightRotation(root);
        }
        else if (balance_factor < -1 && target_key > root->right->key)
        {
            root = LeftRotation(root);
        }
        else if (balance_factor < -1 && target_key < root->right->key)
        {
            root->right = RightRotation(root->right);
            root = LeftRotation(root);
        }
    }
    int height(Node *target_node) // getter(height)
    {
        if (target_node == nullptr)
            return 0;
        else
            return target_node->height;
    }
    int CalculateBalance(Node *target_node)
    {
        return target_node->left->height - target_node->right->height;
    }

    Node *LeftRotation(Node *x) // 왼쪽 Roation을 수행합니다.
    {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }
    Node *RightRotation(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }
    Node *FindMinimumNode(Node *x)
    {
        while (x->left != nullptr)
        {
            x = x->left;
        }
        return x;
    }
    Node *FindMaximumNode(Node *x)
    {
        while (x->right != nullptr)
        {
            x = x->right;
        }
        return x;
    }

public:
    AVLTree()
    {
        this->root_ = nullptr;
    }
    int Insert(int new_key)
    {
        Node *newNode = InsertNode(this->root_, new_key);
        return root_->height - newNode->height;
    }

    // 최솟값 찾기
    void minimum(int x)
    {
        Node *root_of_subtree = FindNodePtr(x);
        std::cout << FindMinimumNode(root_of_subtree) << "\b";
    } // 최댓값 찾기

    void maximum(int x)
    {
        Node *root_of_subtree = FindNodePtr(x);
        Node *maximum_node = FindMaximumNode(root_of_subtree);
        std::cout << maximum_node->key << " ";
        std::cout << root_->height - maximum_node->height << "\n";
    }

    void erase()
    {
    }
};
class Set
{
public:
private:
    AVLTree tree;
};
int main()
{
    AVLTree tree;

    return 0;
}
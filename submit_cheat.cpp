#include <algorithm>
#include <iostream>

struct Node
{
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;
};

class AVLTree
{
private:
    Node *root_;
    Node *FindNodePtr(int find_target)
    {
        Node *iterator = root_;
        /*key값을 찾거나 없다면 break*/
        while (iterator != nullptr && iterator->key != find_target)
        {
            iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
        }
        return iterator; // 찾고자 하는 노드의 포인터를 리턴합니다.
    }

    /*새로운 key 삽입함수로 root_노드 반환*/
    Node *InsertNode(Node *root_of_subtree, int key_of_new_node) // 재귀적으로 Node를 삽입하려는 것으로, 서브트리의 부모노드를 계속 반환합니다.
    {
        /*새로운 노드 삽입*/
        if (root_of_subtree == nullptr)
        {
            Node *new_node = new Node;
            new_node->key = key_of_new_node;
            root_of_subtree = new_node;
            return root_of_subtree;
        }
        else if (root_of_subtree->key < key_of_new_node)
        { // item이 key값보다 크다면 오른쪽으로 이동
            root_of_subtree->right = InsertNode(root_of_subtree->right, key_of_new_node);
        }
        else
        { // item이 key값보다 작다면 왼쪽으로 이동
            root_of_subtree->left = InsertNode(root_of_subtree->left, key_of_new_node);
        }
        root_of_subtree->height = std::max(height(root_of_subtree->left), height(root_of_subtree->right)) + 1;
        DoBalncing(root_of_subtree, key_of_new_node); // 새로운 노드가 추가되었으므로 재귀적으로 부모노드들 높이 1증가 시켜주고
                                                      // Balace Factor 측정하여 2이상이라면 재조정함수
        return root_of_subtree;
    }

    /*key 삭제 함수*/
    Node *EraseNode(Node *r, int item)
    {
        if (r->key > item && r->left != nullptr)
        {
            r->left = EraseNode(r->left, item);
        }
        else if (r->key < item && r->right != nullptr)
        {
            r->right = EraseNode(r->right, item);
        }
        else if (r->key == item)
        {
            MoveChild(r);
        }
        /*root_를 지운게 아니라면*/
        if (r != nullptr)
        {
            r->height = std::max(height(r->left), height(r->right)) + 1;
            DoBalncing(r, item);
        }

        return r;
    }

    /* balance Factor 측정후 재조정*/
    void DoBalncing(Node *&r, int item)
    {
        int balance_factor = CalculateBalance(r);

        // case 1 (left left)
        if (balance_factor > 1 && item < r->left->key)
        {
            r = RightRotation(r);
        }
        // case 2 (left right)
        else if (balance_factor > 1 && item > r->left->key)
        {
            r->left = LeftRotation(r->left);
            r = RightRotation(r);
        }
        // case 3 (right right)
        else if (balance_factor < -1 && item > r->right->key)
        {
            r = LeftRotation(r);
        }
        // case 4 ( right left)
        else if (balance_factor < -1 && item < r->right->key)
        {
            r->right = RightRotation(r->right);
            r = LeftRotation(r);
        }
    }

    /* 삭제시 자식 이식 함수*/
    void MoveChild(Node *&target_node)
    {
        Node *delete_ptr = target_node; // 삭제를 위한 포인터
        if (target_node->left == nullptr)
        {
            target_node = target_node->right;
        }
        else if (target_node->right == nullptr)
        {
            target_node = target_node->left;
        }
        else
        {
            Node *next_min = target_node->right;    // 삭제할 타겟 다음으로 가장 작은 수
            Node *parent_of_next_min = target_node; // x의 부모 노드

            /* 오른쪽 자식중 가장 작은 값*/
            while (next_min->left != nullptr)
            {
                parent_of_next_min = next_min;
                next_min = next_min->left;
            }

            target_node->key = next_min->key; // successor과 key값 교환
            /*오른쪽 자식이 가장 작다면*/
            if (parent_of_next_min == target_node)
            {
                target_node->right = next_min->right; // z의 오른쪽 자식 붙여주기
            }
            else
            {
                parent_of_next_min->left = next_min->right; // 오른쪽 자식의 왼쪽 자식이 있다면
            }                                               // 그 z(successor)의 오른쪽 자식 p[z]의 왼쪽에 붙여주기
            delete_ptr = next_min;                          // 값 삭제를 위해 y <- z;
        }
        delete delete_ptr;
    }
    /*높이 getter */
    int height(Node *r)
    {
        if (r == nullptr)
            return 0;
        else
            return r->height;
    }
    /*좌우 자식 깊이 비교하여 Balnace Factor get*/
    int CalculateBalance(Node *r)
    {
        return height(r->left) - height(r->right);
    }

    /*x를 중심으로 왼쪽으로 회전*/
    Node *LeftRotation(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;

        // 위치가 바뀌었으므로 높이 재조정
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }
    /*y를 중심으로 오른쪽으로 회전*/
    Node *RightRotation(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        x->right = y;

        // 위치가 바뀌었으므로 높이 재조정
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

    void Minimum(int x)
    {
        Node *root_of_subtree = FindNodePtr(x);
        std::cout << FindMinimumNode(root_of_subtree) << "\b";
    } // 최댓값 찾기

    void Maximum(int x)
    {
        Node *root_of_subtree = FindNodePtr(x);
        Node *maximum_node = FindMaximumNode(root_of_subtree);
        std::cout << maximum_node->key << " ";
        std::cout << root_->height - maximum_node->height << "\n";
    }

    void Erase(int x)
    {
    }
};

int main()
{
    AVLTree tree;

    return 0;
}
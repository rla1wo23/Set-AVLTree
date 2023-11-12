#include <algorithm>
#include <iostream>
struct Node
{
    int key;
    int height = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};
class AVLTree
{
public:       // 자식 클래스에서 public함수를 통해서만 AVLTree에 접근할 수 있게끔 합니다.
    AVLTree() // Rule of Three를 만족하게끔 1)복사생성자 2)소멸자를 적절히 추가해야 합니다.
    {
        this->root_ = nullptr;
    }
    bool IsEmpty()
    {
        return node_counter_ == 0;
    }
    int Size()
    {
        return node_counter_;
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
        std::cout << FindMinimumNode(root_of_subtree) << "\n";
    } // 최댓값 찾기

    void maximum(int x)
    {
        Node *root_of_subtree = FindNodePtr(x);
        Node *maximum_node = FindMaximumNode(root_of_subtree);
        std::cout << maximum_node->key << " ";
        std::cout << root_->height - maximum_node->height << "\n";
    }
    void rank(int x)
    {
    }
    void erase()
    {
    }

protected: // protected부분은 자식 클래스에서 직접 호출해서 사용할 수 없으므로 아래 함수들은 public함수를 통해서 접근해서 도구적으로 사용됩니다.
    Node *root_;
    Node *FindNodePtr(int find_target) // 찾고자 하는 노드의 포인터를 반환. input:key, output: 해당 key를 가진 노드의 포인터
    {
        Node *iterator = root_;
        while (iterator != nullptr && iterator->key != find_target)
        {
            iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
        }
        return iterator;
    }
    // 재귀적으로 Node를 삽입하려는 것으로, 현재 탐색중인 노드를 포인터형으로 반환합니다. input:현재 노드의 위치, 삽입하려는 키 output: 탐색해볼 위치
    Node *InsertNode(Node *iterator, int key_of_new_node){
        // 1.node_counter를 증가
        // 2.Balance 체크 후 깨졌다면 AdjustBlance 함수를 호출해서 로테이션을 적절히 수행
    };
    Node *EraseNode(Node *root_node, int key_of_target){}; // 노드를 삭제합니다.

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
    Node *LeftRotation(Node *old_axis) // 왼쪽 Roation을 수행합니다.
    {
        Node *new_axis = old_axis->right;
        if (new_axis->left != nullptr)
        {
            old_axis->right = new_axis->left;
        }
        new_axis->left = old_axis;
        old_axis->height = std::max(height(old_axis->left), height(old_axis->right)) + 1; // height재조정
        new_axis->height = std::max(height(new_axis->left), height(new_axis->right)) + 1;
        return new_axis;
    }
    Node *RightRotation(Node *old_axis)
    {
        Node *new_axis = old_axis->left;
        if (new_axis->right != nullptr)
        {
            old_axis->left = new_axis->right;
        }
        new_axis->right = old_axis;
        old_axis->height = std::max(height(old_axis->left), height(old_axis->right)) + 1;
        new_axis->height = std::max(height(new_axis->left), height(new_axis->right)) + 1;
        return new_axis;
    }
    void AdjustBlance(Node *&root, int target_key) // root노드와 어떤 키를 기준으로 밸런스를 맞출지 정의합니다.
    {
        int balance_factor = CalculateBalance(root);
        if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) // 균형이 맞음, 밸런스 조정필요 없음
        {
            return;
        }
        if (balance_factor > 1 && target_key < root->left->key) // 왼쪽이 더 큰 트리, ll의 경우
        {
            root = RightRotation(root);
        }
        else if (balance_factor > 1 && target_key > root->left->key) // lr상황
        {
            root->left = LeftRotation(root->left);
            root = RightRotation(root);
        }
        else if (balance_factor < -1 && target_key > root->right->key) // rr상황
        {
            root = LeftRotation(root);
        }
        else if (balance_factor < -1 && target_key < root->right->key) // rl상황
        {
            root->right = RightRotation(root->right);
            root = LeftRotation(root);
        }
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

protected:
    int node_counter_ = 0;
};
class Set : public AVLTree
{
public:
    Set()
    {
        tree = AVLTree();
    }
    void minimum(int X);
    void maximum(int X);
    void empty()
    {
        std::cout << tree.IsEmpty();
    }
    void size()
    {
        std::cout << tree.Size();
    }
    void find(int x);
    void insert(int x);
    void rank(int x);
    void erase(int x);

public:
    AVLTree tree;
};
int main()
{
    Set s;

    return 0;
}
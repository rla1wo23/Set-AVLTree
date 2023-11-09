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
    // AVL Tree의 회전 연산 및 기타 도움 함수들을 정의합니다.
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

    // AVL Tree의 삽입, 삭제, 탐색, 랭크, 최솟값, 최댓값, 비어 있는지 여부, 크기를 수행하는 함수들을 정의합니다.
};

AVLTree::~AVLTree()
{
    // AVL Tree의 노드들을 삭제하는 로직을 추가할 수 있습니다.
}

void AVLTree::insert(int key)
{
    // AVL Tree에 새로운 노드를 삽입하는 로직을 추가할 수 있습니다.
}

void AVLTree::erase(int key)
{
    // AVL Tree에서 노드를 삭제하는 로직을 추가할 수 있습니다.
}

int AVLTree::find(int key)
{
    // AVL Tree에서 노드를 탐색하는 로직을 추가할 수 있습니다.
}

int AVLTree::rank(int key)
{
    // AVL Tree에서 노드의 랭크를 찾는 로직을 추가할 수 있습니다.
}

void AVLTree::minimum()
{
    // AVL Tree에서 최솟값을 찾는 로직을 추가할 수 있습니다.
}

void AVLTree::maximum()
{
    // AVL Tree에서 최댓값을 찾는 로직을 추가할 수 있습니다.
}

bool AVLTree::empty()
{
    // AVL Tree가 비어 있는지 여부를 판별하는 로직을 추가할 수 있습니다.
}

int AVLTree::size()
{
    // AVL Tree의 크기를 찾는 로직을 추가할 수 있습니다.
}

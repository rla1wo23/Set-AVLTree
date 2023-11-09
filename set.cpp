#include "avltree.cpp"
class Set
{
private:
    AVLTree avlTree;

public:
    void insert(int key)
    {
        avlTree.insert(key);
    }

    void erase(int key)
    {
        avlTree.erase(key);
    }

    int find(int key)
    {
        return avlTree.find(key);
    }

    int rank(int key)
    {
        return avlTree.rank(key);
    }

    void minimum()
    {
        avlTree.minimum();
    }

    void maximum()
    {
        avlTree.maximum();
    }

    bool empty()
    {
        return avlTree.empty();
    }

    int size()
    {
        return avlTree.size();
    }
};

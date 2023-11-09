#include <iostream>
#include <algorithm>

struct Node
{
    int key;
    int height;
    Node *left;
    Node *right;
};

class AVLSet
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

    Node *insert(Node *node, int key)
    {
        if (node == nullptr)
        {
            Node *newNode = new Node{key, 1, nullptr, nullptr};
            return newNode;
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            // Duplicate keys are not allowed in set, do nothing
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Heavy
        if (balance > 1 && key < node->left->key)
        {
            return rotateRight(node);
        }
        // Right Heavy
        if (balance < -1 && key > node->right->key)
        {
            return rotateLeft(node);
        }
        // Left Right Heavy
        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right Left Heavy
        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *findMinNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    Node *erase(Node *node, int key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = erase(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = erase(node->right, key);
        }
        else
        {
            // Node to be deleted found

            // Node with one child or no child
            if (node->left == nullptr || node->right == nullptr)
            {
                Node *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
            }
            else
            {
                // Node with two children, get the inorder successor (smallest in the right subtree)
                Node *temp = findMinNode(node->right);

                // Copy the inorder successor's data to this node
                node->key = temp->key;

                // Delete the inorder successor
                node->right = erase(node->right, temp->key);
            }
        }

        if (node == nullptr)
        {
            return node;
        }

        // Update height of the current node
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Rebalance the node
        int balance = balanceFactor(node);

        // Left Heavy
        if (balance > 1 && balanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }
        // Right Heavy
        if (balance < -1 && balanceFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }
        // Left Right Heavy
        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right Left Heavy
        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    int sizeHelper(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + sizeHelper(node->left) + sizeHelper(node->right);
    }

    int findDepth(Node *node, int key, int depth)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (key == node->key)
        {
            return depth;
        }
        if (key < node->key)
        {
            return findDepth(node->left, key, depth + 1);
        }
        else
        {
            return findDepth(node->right, key, depth + 1);
        }
    }

    int findRank(Node *node, int key)
    {
        if (node == nullptr)
        {
            return 1;
        }
        if (key < node->key)
        {
            return findRank(node->left, key);
        }
        else
        {
            return 1 + sizeHelper(node->left) + findRank(node->right, key);
        }
    }

public:
    AVLSet() : root(nullptr) {}

    ~AVLSet()
    {
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    void erase(int key)
    {
        int depth = findDepth(root, key, 1);
        if (depth == 0)
        {
            std::cout << "0" << std::endl;
        }
        else
        {
            root = erase(root, key);
            std::cout << depth << std::endl;
        }
    }

    void find(int key)
    {
        int depth = findDepth(root, key, 1);
        std::cout << depth << std::endl;
    }

    void rank(int key)
    {
        int rank = findRank(root, key);
        std::cout << findDepth(root, key, 1) << " " << rank << std::endl;
    }

    void minimum()
    {
        Node *current = root;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        std::cout << current->key << " " << 1 << std::endl;
    }

    void maximum()
    {
        Node *current = root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        std::cout << current->key << " " << 1 << std::endl;
    }

    void empty()
    {
        if (root == nullptr)
        {
            std::cout << "1" << std::endl;
        }
        else
        {
            std::cout << "0" << std::endl;
        }
    }

    void size()
    {
        int setSize = sizeHelper(root);
        std::cout << setSize << std::endl;
    }
};

int main()
{
    AVLSet set;
    int T;
    std::cin >> T;
    while (T--)
    {
        // Example usage
        set.insert(5);
        set.insert(3);
        set.insert(7);
        set.insert(1);

        set.minimum(); // Output: 1 1
        set.maximum(); // Output: 7 1
        set.empty();   // Output: 0
        set.size();    // Output: 4
        set.find(3);   // Output: 2
        set.rank(5);   // Output: 1 3

        set.erase(3); // Output: 2
        set.find(3);  // Output: 0 (node not found)
    }
    return 0;
}

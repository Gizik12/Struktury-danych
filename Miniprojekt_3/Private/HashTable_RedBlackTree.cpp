#include "../Public/HashTable_RedBlackTree.h"


// Funkcje klasy RBTreeNode
RBTreeNode::RBTreeNode(int k, int v)
{
    this->key = k;
    this->value = v;
    this->color = RED;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}
// Funkcje klasy RedBlackTree
void RedBlackTree::rotateLeft(RBTreeNode*& root, RBTreeNode*& pt)
{
    RBTreeNode* pt_right = pt->right;
    pt->right = pt_right->left;

    if (pt->right != nullptr)
    {
        pt->right->parent = pt;
    }

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
    {
        root = pt_right;
    }

    else if (pt == pt->parent->left)
    {
        pt->parent->left = pt_right;
    }
    else
    {
        pt->parent->right = pt_right;
    }

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RedBlackTree::rotateRight(RBTreeNode*& root, RBTreeNode*& pt)
{
    RBTreeNode* pt_left = pt->left;
    pt->left = pt_left->right;

    if (pt->left != nullptr)
    {
        pt->left->parent = pt;
    }

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
    {
        root = pt_left;
    }
    else if (pt == pt->parent->left)
    {
        pt->parent->left = pt_left;
    }
    else
    {
        pt->parent->right = pt_left;
    }
    pt_left->right = pt;
    pt->parent = pt_left;
}

void RedBlackTree::fixViolation(RBTreeNode*& root, RBTreeNode*& pt)
{
    RBTreeNode* parent_pt = nullptr;
    RBTreeNode* grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left)
        {
            RBTreeNode* uncle_pt = grand_parent_pt->right;
            if (uncle_pt != nullptr && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        else
        {
            RBTreeNode* uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != nullptr) && (uncle_pt->color == RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

RedBlackTree::RedBlackTree()
{
    this->root = nullptr;
}
void RedBlackTree::insert(const int& key, const int& value)
{

    RBTreeNode* pt = new RBTreeNode(key, value);
    root = BSTInsert(root, pt);
    fixViolation(root, pt);
}

RBTreeNode* RedBlackTree::BSTInsert(RBTreeNode* root, RBTreeNode* pt)
{
    if (root == nullptr)
    {
        return pt;
    }
    if (pt->key < root->key)
    {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->key > root->key)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
    return root;
}

RBTreeNode* RedBlackTree::search(RBTreeNode* node, int key)
{
    if (node == nullptr || node->key == key)
    {
        return node;
    }
    if (node->key < key)
    {
        return search(node->right, key);
    }
    return search(node->left, key);
}

RBTreeNode* RedBlackTree::getRoot()
{
    return root;
}

void RedBlackTree::setRoot(RBTreeNode* newRoot)
{
    root = newRoot;
}
// Funkcje klasy HashTable_RB
int HashTable_RB::hashFunction(int key) const
{
    return key % capacity;
}

HashTable_RB::HashTable_RB(int cap)
{
    capacity = cap;
    hashTable = new RedBlackTree * [capacity];
    for (int i = 0; i < capacity; i++)
    {
        hashTable[i] = new RedBlackTree();
    }
}

HashTable_RB::~HashTable_RB()
{
    for (int i = 0; i < capacity; i++)
    {
        delete hashTable[i];
    }
    delete[] hashTable;
}

void HashTable_RB::insert(int key, int value)
{
    int hashIndex = hashFunction(key);
    hashTable[hashIndex]->insert(key, value);
}

int HashTable_RB::search(int key) const
{
    int hashIndex = hashFunction(key);
    RBTreeNode* node = hashTable[hashIndex]->search(hashTable[hashIndex]->getRoot(), key);
    return node ? node->value : -1;
}

void HashTable_RB::remove(int key)
{
    int hashIndex = hashFunction(key);
    RedBlackTree* tree = hashTable[hashIndex];
    RBTreeNode* root = tree->getRoot();
    RBTreeNode* nodeToRemove = tree->search(root, key);

    if (nodeToRemove)
    {
        RBTreeNode* parent = nodeToRemove->parent;

        // Jeśli węzeł do usunięcia ma dwoje dzieci
        if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr)
        {
            // Znajdź następnik węzła do usunięcia (najmniejszy w prawym poddrzewie)
            RBTreeNode* successor = nodeToRemove->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            // Zamień klucz i wartość następnika z kluczem i wartością węzła do usunięcia
            swap(nodeToRemove->key, successor->key);
            swap(nodeToRemove->value, successor->value);

            // Węzeł do usunięcia teraz staje się następnikiem i przechodzimy do usuwania go
            nodeToRemove = successor;
        }

        // Znajdź dziecko węzła do usunięcia lub nullptr, jeśli węzeł nie ma dzieci
        RBTreeNode* child = (nodeToRemove->right == nullptr) ? nodeToRemove->left : nodeToRemove->right;

        // Jeśli węzeł do usunięcia jest korzeniem drzewa
        if (parent == nullptr)
        {
            tree->setRoot(child); // Użycie metody setRoot
        }
        else {
            // Zaktualizuj wskaźnik rodzica na dziecko węzła do usunięcia
            if (nodeToRemove == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }

        // Jeśli istnieje dziecko, zaktualizuj jego wskaźnik na rodzica
        if (child != nullptr) {
            child->parent = parent;
        }

        // Zwolnij pamięć zajmowaną przez węzeł do usunięcia
        delete nodeToRemove;
    }
}
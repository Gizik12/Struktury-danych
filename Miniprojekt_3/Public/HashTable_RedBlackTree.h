#include "HashTable.h"

#ifndef HASH_TABLE_REDBLACKTREE
#define HASH_TABLE_REDBLACKTREE

enum Color { RED, BLACK };

struct RBTreeNode 
{
    int key;
    int value;
    Color color;
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;

    RBTreeNode(int k, int v);
};

class RedBlackTree 
{
private:
    RBTreeNode* root;

    void rotateLeft(RBTreeNode*& root, RBTreeNode*& pt);

    void rotateRight(RBTreeNode*& root, RBTreeNode*& pt);

    void fixViolation(RBTreeNode*& root, RBTreeNode*& pt);
public:
    RedBlackTree();

    void insert(const int& key, const int& value);

    RBTreeNode* BSTInsert(RBTreeNode* root, RBTreeNode* pt);

    RBTreeNode* search(RBTreeNode* node, int key);

    RBTreeNode* getRoot();

    void setRoot(RBTreeNode* newRoot);
};

class HashTable_RB 
{
private:
    RedBlackTree** hashTable;
    int capacity;

    int hashFunction(int key);

public:
    HashTable_RB(int cap);

    ~HashTable_RB();

    virtual void insert(int key, int value);

    virtual int search(int key);

    virtual void remove(int key);
};

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

#endif
#ifndef BTREE_H
#define BTREE_H
#include "Node.h"

class BTree
{
private:

    Node* root;
    int degree;

public:
    BTree(int);
    ~BTree();
    void traverse();
    Node* find(int);

    void insert(int);

    void erase(int);

};

#endif // BTREE_H

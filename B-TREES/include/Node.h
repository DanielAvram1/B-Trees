#ifndef NODE_H
#define NODE_H
#include<iostream>
using namespace std;

class Node
{
private:
    int *key;
    Node **child;
    int n;
    bool leaf;
    int degree;
public:
    friend class BTree;
    Node(int, bool);
    ~Node();

    void traverse();

    Node* find(int);

    void insertInNonFull(int);

    void splitChild(int, Node*);

    void erase(int);

    int findInThis(int);

    void fillChildOfThis(int);

    void mergeWithNext(int);

    void eraseFromLeaf(int);

    void eraseFromNonLeaf(int);

    int getPred(int);

    int getSucc(int);

    void borrowFromPrev(int);

    void borrowFromNext(int);

};

#endif // NODE_H

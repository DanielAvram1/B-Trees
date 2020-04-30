#include "BTree.h"

BTree::BTree(int degree)
{
    root = NULL;
    this->degree = degree;
}

BTree::~BTree()
{
    delete root;
}

void BTree::traverse(){
    if(root){
        root->traverse();
    }
}

Node* BTree::find(int toFind){
    if(root){
        return root->find(toFind);
    }
}

void BTree::insert(int toInsert){

    if(!root){
        root = new Node(degree, true);
        root->key[0] = toInsert;
        root->n++;
    }
    else {
        if(root->n == 2*degree - 1){
            Node *s = new Node(degree, false);

            s->child[0] = root;

            s->splitChild(0, root);

            int i = 0;

            if(s->key[0] < toInsert)
                i++;
            s->child[i]->insertInNonFull(toInsert);
            root = s;
        }
        else {
            root->insertInNonFull(toInsert);
        }

    }

}

void BTree::erase(int toErase){

    if(!root){
        return;
    }

    root->erase(toErase);

    if(root->n == 0){
        Node* temp = root;
        if(root->leaf){
            root = NULL;
        }
        else
            root = root->child[0];
        delete temp;
    }

}

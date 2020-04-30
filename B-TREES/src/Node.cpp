#include "Node.h"

Node::Node(int degree, bool leaf)
{
    this->degree = degree;
    n = 0;
    this->leaf = leaf;
    key = new int[2*degree - 1];
    child = new Node *[2*degree];
}

Node::~Node()
{
   /* for(int i = 0;i<=2*degree;i++){
        if(child[i])
            delete child[i];
    }*/
}

void Node::traverse(){

    for(int i = 0;i<n;i++){
        if(!leaf){
            child[i]->traverse();
        }
        cout<<' '<<key[i];
    }
    if(!leaf){
        child[n]->traverse();
    }
    return;
}

Node* Node::find(int toFind){

    int i = 0;
    while(i < n && toFind > key[i])
        i++;
    if(i < n){
        if(key[i] == toFind){
            return this;
        }
    }

    if(leaf){
        return NULL;
    }

    return child[i]->find(toFind);
}

void Node::insertInNonFull(int toInsert){
    int i = n - 1;

    if(leaf){

        while(i >=0 && key[i] > toInsert){
            key[i+1] = key[i];
            i--;
        }

        key[i+1] = toInsert;
        n++;
    }
    else { ///nu e frunza

        while(i >= 0 && key[i] > toInsert){
            i--;
        }

        if(child[i+1]->n == 2*degree - 1){
            splitChild(i+1, child[i+1]);

            if(key[i+1] < toInsert)
                i++;
        }
        child[i+1]->insertInNonFull(toInsert);
    }
}

void Node::splitChild(int i, Node* y){
    Node* z = new Node(y->degree, y->leaf);
    z->n = degree - 1;

    for(int j = 0;j< degree- 1; j++)
        z->key[j] = y->key[j+degree];

    if(y->leaf){

        for(int j = 0;j<degree;j++){
            z->child[j] = y->child[j+degree];
        }
    }

    y->n = degree-1;

    for(int j = n; j>= i+1;j--){
        child[j+1] = child[j];
    }

    child[i+1] = z;

    for(int j = n - 1; j >= i;j--){
        key[j+1] = key[j];
    }
    key[i] = y->key[degree - 1];
    n++;

}

int Node::findInThis(int toFind){
    int i = 0;
    while(i < n && key[i] < toFind)
        i++;
    return i;
}

void Node::mergeWithNext(int toMerge){

    Node* curr = child[toMerge];
    Node* sibling = child[toMerge + 1];

    curr->key[degree - 1] = key[toMerge];

    for(int i = 0;i<sibling->n;i++){
        curr->key[i+degree] = sibling->key[i];
    }

    if(!curr->leaf){
        for(int i = 0;i<=sibling->n;i++)
            curr->child[i+degree] = sibling->child[i];
    }

    for(int i = toMerge + 1;i<n;i++)
        key[i - 1] = key[i];

    curr->n +=sibling->n + 1;
    n--;

    delete(sibling);
}

void Node::borrowFromNext(int index){
    Node* curr = child[index];
    Node* next = child[index+1];
    curr->key[degree] = key[index];
    if(!curr->leaf){
        curr->child[degree + 1] = next->child[0];
    }
    curr->n++;
    key[index] = next->key[0];

    for(int i =1;i<next->n;i++)
        next->key[i-1] = next->key[i];

    if(!next->leaf){
        for(int i =1;i<=next->n;i++)
        next->child[i-1] = next->child[i];
    }
    next->n--;

}

void Node::borrowFromPrev(int index){

    Node* curr = child[index];
    Node* prev = child[index - 1];

    for(int i = curr->n;i>=1;i--){
        curr->key[i] = curr->key[i - 1];
    }

    if(!curr->leaf){
        for(int i = curr->n + 1;i>=1;i--){
            curr->child[i] = curr->child[i - 1];
        }
    }

    curr->n++;
    curr->key[0] = key[index - 1];
    if(!curr->leaf)
        curr->child[0] = prev->child[prev->n];

    key[index - 1] = prev->key[prev->n - 1];

    prev->n--;



}

void Node::fillChildOfThis(int toFillIndex){

    if(toFillIndex > 0 && child[toFillIndex - 1]->n >=degree)
        borrowFromPrev(toFillIndex);

    else if(toFillIndex < n && child[toFillIndex + 1]->n >=degree){
        borrowFromNext(toFillIndex);
    }
    else {
        if(toFillIndex < n)
            mergeWithNext(toFillIndex);
        else
            mergeWithNext(toFillIndex - 1);
    }
}

void Node::eraseFromLeaf(int toEraseIndex){

    for(int i = toEraseIndex;i<n;i++)
        key[i] =key[i+1];
    n--;
}

int Node::getPred(int index){
    Node* curr = child[index];
    while(!curr->leaf){
        curr = curr->child[curr->n];
    }
    return curr->key[curr->n - 1];
}

int Node::getSucc(int index){
    Node* curr = child[index + 1];
    while(!curr->leaf){
        curr = curr->child[0];
    }
    return curr->key[0];
}

void Node::eraseFromNonLeaf(int toEraseIndex){

    int k = key[toEraseIndex];

    if(child[toEraseIndex]->n >= degree){
        int pred = getPred(toEraseIndex);
        key[toEraseIndex] = pred;
        child[toEraseIndex]->erase(pred);
    }
    else if(child[toEraseIndex + 1]->n >= degree){
        int succ = getSucc(toEraseIndex);
        key[toEraseIndex] = succ;
        child[toEraseIndex+1]->erase(succ);
    }
    else {
        mergeWithNext(toEraseIndex);
        child[toEraseIndex]->erase(k);
    }
}

void Node::erase(int toErase){

    int curr = findInThis(toErase);

    if(curr < n && key[curr] == toErase){
        if(leaf)
            eraseFromLeaf(curr);
        else
            eraseFromNonLeaf(curr);
    }
    else {

        if(leaf){
            return;
        }

        bool isLast = false;
        if(curr == n) isLast = true;

        if(child[curr]->n < degree)
            fillChildOfThis(curr);

        if(isLast && curr > n)
            child[curr-1]->erase(toErase);
        else
            child[curr]->erase(toErase);

    }

}




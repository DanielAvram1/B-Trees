#include <iostream>
#include "BTree.h"

using namespace std;
/*
20
3 10
1 5
1 7
1 12
1 13
1 14
2 7
6
1 20
1 21
1 23
1 24
1 100
1 101
1 102
1 8
1 10
3 5
4 11
6
*/
int main()
{
    BTree t(3);

    int n,x,y,q;
    cin>>n;
    while(n--){
        cin>>q;
        if(q == 1){
            cin>>x;
            t.insert(x);
        }
        if(q == 2){
            cin>>x;
            t.erase(x);
        }
        if(q == 3){
            cin>>x;
            cout<< (t.find(x) != NULL)<<'\n';
        }
        if(q == 4 || q == 5)
            cin>>x;

        if(q == 6){
            t.traverse();
            cout<<'\n';
        }

    }

    return 0;
}

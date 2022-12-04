#include <iostream>
#include <cstring>
using namespace std;
#include "bst copy.h"

int main()
{
    int val = 10;
    BST *a = new BST(val);
    a->Insert(30);
    a->Insert(50);
    a->Insert(3);
    a->Insert(40);
    a->Insert(28);

    cout << "前序遍历(非递归版):\t";
    a->PreOrder();

    cout << "前序遍历(递归版):\t";
    PreOrder(a->GetRoot());
    cout << endl;

    cout << "中序遍历(非递归版):\t";
    a->InOrder();

    cout << "中序遍历(递归版):\t";
    InOrder(a->GetRoot());
    cout << endl;

    cout << "后序遍历(递归版):\t";
    PostOrder(a->GetRoot());
    cout << endl;

    a->SetRoot(DeleteNode(a->GetRoot(), 30));

    cout << "前序遍历(非递归版):\t";
    a->PreOrder();

    cout << "中序遍历(非递归版):\t";
    a->InOrder();

    cout << "后序遍历(递归版):\t";
    PostOrder(a->GetRoot());
}
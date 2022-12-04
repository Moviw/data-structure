#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__

#include <iostream>
using namespace std;

template <class T>
class HuffmanTree
{
private:
    HuffmanTreeNode<T> *root;
    void MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T> *parent);
    void DeleteTree(HuffmanTreeNode<T> *root);

public:
    HuffmanTree(T weight[], int n);
    virtual ~HuffmanTree() { DeleteTree(root); };
};

#endif
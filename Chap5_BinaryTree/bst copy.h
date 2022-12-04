#ifndef __BST_H__
#define __BST_H__
#include <iostream>
#include <cstring>
#include <utility>
// #include "Chap3_stack_queue/stack/stack.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\stack\stack.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\queue\queue.h"
using namespace std;

class BSTNode
{
private:
    int info;       //二叉树结点数据域
    BSTNode *left;  //指向左子树
    BSTNode *right; //指向右子树
public:
    BSTNode() : info(0), left(nullptr), right(nullptr) // 默认构造函数
    {
    }
    BSTNode(const int &ele) : info(ele), left(nullptr), right(nullptr) // 给定数据的构造函数
    {
    }
    BSTNode(const int &ele, BSTNode *l, BSTNode *r) //子树构造结点
    {
        info = ele;
        left = l;
        right = r;
    }
    int GetValue() const { return this->info; }                           //返回当前结点的数据
    BSTNode *GetLeftChild() const { return left; }                        //返回当前结点的左子树
    BSTNode *GetRightChild() const { return right; }                      //返回当前结点的右子树
    void SetLeftchild(BSTNode *l) { this->left = l; }                     //设置当前结点的左子树
    void SetRightchild(BSTNode *r) { this->right = r; }                   //设置当前结点的右子树
    void SetValue(const int &val) { this->info = val; }                   //设置当前结点的数据域
    bool IsLeaf() const { return (left == nullptr && right == nullptr); } //判断当前结点是否为叶结点
    BSTNode &operator=(const BSTNode &Node)                               // 重载赋值操作符
    {
        if (&Node == this)
        {
            return *this;
        }
        info = Node.GetValue();
        left = Node.GetLeftChild();
        right = Node.GetRightChild();
        return *this;
    }
};

class BST
{
private:
    BSTNode *root = nullptr;              //根节点
    BSTNode *CreateInTree(/* char *s */); //补空法
public:
    BST() // 构造函数
    {     /*  root = new BSTNode();  */
    }
    BST(char *s) // 构造函数
    {
        root = CreateInTree();
    }
    BST(int val = 0)
    {
        root = new BSTNode(val);
    }
    ~BST() { DeleteBinaryintree(root); }                   // 析构函数
    bool IsEmpty() const { return root == nullptr; }       // 判定二叉树是否为空树
    BSTNode *GetRoot() { return root; }                    // 返回二叉树根结点
    void SetRoot(BSTNode *target) { this->root = target; } //设置二叉树根节点
    BSTNode *GetParent(BSTNode *current);                  // 返回当前结点的父结点
    void PreOrder();                                       // 前序周游二叉树(非递归)
    void InOrder();                                        // 中序周游二叉树(非递归)
    void LevelOrder();                                     // 按层次周游二叉树
    void DeleteBinaryintree(BSTNode *root);                // 删除给定的二叉树
    friend int Depth();                                    // 计算深度
    friend void PreOrder(BSTNode *root);                   // 前序周游二叉树(递归)
    friend void InOrder(BSTNode *root);                    // 中序周游二叉树(递归)
    friend void PostOrder(BSTNode *root);                  // 后序周游二叉树(递归)
    friend void LeafNum(BSTNode *root, int &num);          // 计算叶子数目

    /*
        以下为二叉搜索树的方法:
    */
    void Insert(int data);                                    //向二叉搜索树中插入
    bool IsHave(const int &data, BSTNode *ret = nullptr);     //在二叉搜索树中寻找是否有data
    friend BSTNode *DeleteNode(BSTNode *root, const int key); //根据值删除节点，并保持二叉搜索树的性质
};

BSTNode *BST::CreateInTree(/* char *s */)
{
    BSTNode *node;
    char ch;
    cin.get(ch);
    if (ch == '#')
    {
        // s++;
        node = nullptr;
    }
    else
    {
        node = new BSTNode(ch);
        node->SetLeftchild(CreateInTree());
        node->SetRightchild(CreateInTree());
    }
    return node;
}

void BST::DeleteBinaryintree(BSTNode *root) //删除给定的二叉树
{
    if (!this->IsEmpty())
    {
        //后序周游删除二叉树
        DeleteBinaryintree(root->GetLeftChild());
        DeleteBinaryintree(root->GetRightChild());
        delete root;
    }
}
int Depth(BSTNode *root)
{
    if (root == nullptr)
        return 0;
    else
    {

        int m = Depth(root->GetLeftChild());
        int n = Depth(root->GetRightChild());
        if (m > n)
            return (m + 1);
        else
            return (n + 1);
    }
}

void PreOrder(BSTNode *root) // 前序周游给定二叉树
{
    if (root)
    {
        cout << root->GetValue() << " ";
        PreOrder(root->GetLeftChild());
        PreOrder(root->GetRightChild());
    }
}

void InOrder(BSTNode *root) //中序周游给定二叉树
{
    if (root)
    {
        InOrder(root->GetLeftChild());
        cout << root->GetValue() << " ";
        InOrder(root->GetRightChild());
    }
}
void PostOrder(BSTNode *root) //后序周游给定二叉树
{
    if (root)
    {
        PostOrder(root->GetLeftChild());
        PostOrder(root->GetRightChild());
        cout << root->GetValue() << " ";
    }
}
void LeafNum(BSTNode *root, int &num)
{
    if (root == nullptr)
        return;
    if (root->GetLeftChild() == nullptr && root->GetRightChild() == nullptr)
        num++;

    LeafNum(root->GetLeftChild(), num);
    LeafNum(root->GetRightChild(), num);
}

void BST::PreOrder()
{
    Stack<BSTNode *> *s = new Stack<BSTNode *>(100);
    BSTNode *node = this->root;
    s->Push(nullptr); // 栈底监视哨
    while (node || !s->IsEmpty())
    {
        cout << node->GetValue() << " ";
        if (node->GetRightChild() != nullptr)
            s->Push(node->GetRightChild());
        if (node->GetLeftChild() != nullptr)
            s->Push(node->GetLeftChild());
        s->Pop(node);
    }
    cout << endl;
}

void BST::InOrder()
{
    Stack<BSTNode *> *s = new Stack<BSTNode *>(100);
    BSTNode *node = this->root;
    while (node || !s->IsEmpty())
    {
        if (node)
        {
            s->Push(node);
            node = node->GetLeftChild();
        }
        else
        {
            s->Pop(node);
            cout << node->GetValue() << " ";
            node = node->GetRightChild();
        }
    }
    cout << endl;
}

void BST::LevelOrder() //按层次周游二叉树
{
    Queue<BSTNode *> *q = new Queue<BSTNode *>();
    BSTNode *node = root;
    BSTNode *item;
    q->EnQueue(node);
    while (!q->IsEmpty())
    {
        q->DeQueue(item);
        cout << item->GetValue() << " ";
        if (item->GetLeftChild())
            q->EnQueue(item->GetLeftChild());
        if (item->GetRightChild())
            q->EnQueue(item->GetRightChild());
    }
    cout << endl;
}

BSTNode *BST::GetParent(BSTNode *current)
{
    if (this->IsEmpty() || !current)
    {
        return nullptr;
    }
    BSTNode *node = root;
    int num;
    LeafNum(this->GetRoot(), num);
    Stack<BSTNode *> *s = new Stack<BSTNode *>(num);
    while (!s->IsEmpty() || node)
    {
        if (node)
        {
            if (node->GetLeftChild() == current || node->GetRightChild() == current)
            {
                return node;
            }
            s->Push(node);
            node = node->GetLeftChild();
        }
        else
        {
            s->Pop(node);
            node = node->GetRightChild();
        }
    }
}

void BST::Insert(int data)
{
    if (this->IsEmpty())
    {
        root = new BSTNode(data);
        root->SetValue(data);
        return;
    }
    BSTNode *node = root;
    BSTNode *temp = new BSTNode(data);
    while (node)
    {
        if (data == node->GetValue())
            return;
        else if (data > node->GetValue())
        {
            if (node->GetRightChild())
                node = node->GetRightChild();
            else
            {
                node->SetRightchild(temp);
                return;
            }
        }
        else
        {
            if (node->GetLeftChild())
                node = node->GetLeftChild();
            else
            {
                node->SetLeftchild(temp);
                return;
            }
        }
    }
}

bool BST::IsHave(const int &data, BSTNode *ret) //用ret接当前这个节点
{
    if (this->IsEmpty())
    {
        cout << "树是空的\n";
        return false;
    }
    BSTNode *node = root;
    while (node)
    {
        if (node->GetValue() == data)
        {
            cout << "找着了 有\n";
            ret = node;
            return true;
        }
        else if (node->GetValue() < data)
        {
            if (!node->GetRightChild())
            {
                cout << "没找着\n";
                return false;
            }
            else
            {
                node = node->GetRightChild();
            }
        }
        else if (node->GetValue() > data)
        {
            if (!node->GetLeftChild())
            {
                cout << "没找着\n";
                return false;
            }
            else
            {
                node = node->GetLeftChild();
            }
        }
    }
    cout << "没找着\n";
    return false;
}

BSTNode *DeleteNode(BSTNode *root, const int key)
{
    if (!root)
        return nullptr;
    if (key < root->GetValue())
        root->SetLeftchild(DeleteNode(root->GetLeftChild(), key));
    else if (key > root->GetValue())
        root->SetRightchild(DeleteNode(root->GetRightChild(), key));
    else
    {
        if (!root->GetRightChild())
            return root->GetLeftChild();
        if (!root->GetLeftChild())
            return root->GetRightChild();

        BSTNode *r = root->GetRightChild();
        //找到右子树的最左子树
        while (r->GetLeftChild())
            r = r->GetLeftChild();

        r->SetLeftchild(root->GetLeftChild());
        root = root->GetRightChild();
    }
    return root;
}

#endif
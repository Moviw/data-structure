#ifndef __BST_H__
#define __BST_H__
#include <iostream>
#include <cstring>
#include <utility>
// #include "Chap3_stack_queue/stack/stack.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\stack\stack.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\queue\queue.h"
using namespace std;

template <class T>
class BSTNode
{
private:
    T info;            //二叉树结点数据域
    BSTNode<T> *left;  //指向左子树
    BSTNode<T> *right; //指向右子树
public:
    BSTNode() : info(0), left(nullptr), right(nullptr) // 默认构造函数
    {
    }
    BSTNode(const T &ele) : info(ele), left(nullptr), right(nullptr) // 给定数据的构造函数
    {
    }
    BSTNode(const T &ele, BSTNode<T> *l, BSTNode<T> *r) //子树构造结点
    {
        info = ele;
        left = l;
        right = r;
    }
    T GetValue() const { return this->info; }                             //返回当前结点的数据
    BSTNode<T> *GetLeftChild() const { return left; }                     //返回当前结点的左子树
    BSTNode<T> *GetRightChild() const { return right; }                   //返回当前结点的右子树
    void SetLeftChild(BSTNode<T> *l) { this->left = l; }                  //设置当前结点的左子树
    void SetRightChild(BSTNode<T> *r) { this->right = r; }                //设置当前结点的右子树
    void SetValue(const T &val) { this->info = val; }                     //设置当前结点的数据域
    bool IsLeaf() const { return (left == nullptr && right == nullptr); } //判断当前结点是否为叶结点
    BSTNode<T> &operator=(const BSTNode<T> &Node)                         // 重载赋值操作符
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

template <class T>
class BST
{
private:
    BSTNode<T> *root = nullptr;            //根节点
    BSTNode<T> *CreateTree(/* char *s */); //补空法
public:
    BST() // 构造函数
    {     /*  root = new BSTNode<T>();  */
    }
    BST(char *s) // 构造函数
    {
        root = CreateTree();
    }
    BST(int val = 0)
    {
        root = new BSTNode<T>(val);
    }
    void CreateTree(const T &info, BST<T> &leftTree, BST<T> &rightTree); // 构造新树
    ~BST() { DeleteBinaryTree(root); }                                   // 析构函数
    bool IsEmpty() const { return root == nullptr; }                     // 判定二叉树是否为空树
    BSTNode<T> *GetRoot() { return root; }                               //返回二叉树根结点
    BSTNode<T> *GetParent(BSTNode<T> *current);                          //返回当前结点的父结点
    void PreOrder();                                                     //前序周游二叉树(非递归)
    void InOrder();                                                      //中序周游二叉树(非递归)
    void LevelOrder();                                                   //按层次周游二叉树
    void DeleteBinaryTree(BSTNode<T> *root);                             //删除给定的二叉树
    friend int Depth();                                                  //计算深度
    friend void PreOrder(BSTNode<T> *root);                              //前序周游二叉树(递归)
    friend void InOrder(BSTNode<T> *root);                               //中序周游二叉树(递归)
    friend void PostOrder(BSTNode<T> *root);                             //后序周游二叉树(递归)
    friend void LeafNum(BSTNode<T> *root, int num);                      //计算叶子数目

    /*
        以下为二叉搜索树的方法:
    */
    void Insert(T data);                                   //向二叉搜索树中插入
    bool IsHave(const T &data, BSTNode<T> *ret = nullptr); //在二叉搜索树中寻找是否有data
    void DeleteNode(const T &data);                        //根据值删除节点，并保持二叉搜索树的性质
};

template <class T>
void BST<T>::DeleteBinaryTree(BSTNode<T> *root) //删除给定的二叉树
{
    if (!this->IsEmpty())
    {
        //后序周游删除二叉树
        DeleteBinaryTree(root->left);
        DeleteBinaryTree(root->right);
        delete root;
    }
}
template <class T>
int Depth(BSTNode<T> *root)
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

template <class T>
BSTNode<T> *BST<T>::CreateTree(/* char *s */)
{
    BSTNode<T> *node;
    char ch;
    cin.get(ch);
    if (ch == '#')
    {
        // s++;
        node = nullptr;
    }
    else
    {
        node = new BSTNode<T>(ch);
        node->SetLeftChild(CreateTree());
        node->SetRightChild(CreateTree());
    }
    return node;
}

template <class T>
void PreOrder(BSTNode<T> *root) // 前序周游给定二叉树
{
    if (root)
    {
        cout << root->GetValue();
        PreOrder(root->GetLeftChild());
        PreOrder(root->GetRightChild());
    }
}

template <class T>
void InOrder(BSTNode<T> *root) //中序周游给定二叉树
{
    if (root)
    {
        InOrder(root->GetLeftChild());
        cout << root->GetValue();
        InOrder(root->GetRightChild());
    }
}
template <class T>
void PostOrder(BSTNode<T> *root) //后序周游给定二叉树
{
    if (root)
    {
        PostOrder(root->GetLeftChild());
        PostOrder(root->GetRightChild());
        cout << root->GetValue();
    }
}
template <class T>
void LeafNum(BSTNode<T> *root, int &num)
{
    if (root == nullptr)
        return;
    if (root->GetLeftChild() == nullptr && root->GetRightChild() == nullptr)
        num++;

    LeafNum(root->GetLeftChild(), num);
    LeafNum(root->GetRightChild(), num);
}

template <class T>
void BST<T>::PreOrder()
{
    int num = 0;
    LeafNum(this->root, num);
    Stack<BSTNode<T> *> *s = new Stack<BSTNode<T> *>(num);
    BSTNode<T> *node = this->root;
    BSTNode<T> *item;
    s->push(nullptr); // 栈底监视哨
    while (node)
    {
        cout << node->GetValue();
        if (node->GetRightChild() != nullptr)
            s->push(node->GetRightChild());
        if (node->GetLeftChild() != nullptr)
            s->push(node->GetLeftChild());
        s->pop(node);
        // if (node)
        // {
        //     s->push(node);
        //     cout << node->GetValue();
        // }
        // else
        // {
        //     s->pop(item);
        //     node = item->GetLeftChild();
        //     node = item->GetRightChild();
        // }
    }
}

template <class T>
void BST<T>::InOrder()
{
    int num = 0;
    LeafNum(this->root, num);
    Stack<BSTNode<T> *> *s = new Stack<BSTNode<T> *>(num);
    BSTNode<T> *node = this->root;
    while (node || !s->IsEmpty())
    {
        if (node)
        {
            s->push(node);
            node = node->GetLeftChild();
        }
        else
        {
            s->pop(node);
            cout << node->GetValue();
            node = node->GetRightChild();
        }
    }
}

template <class T>
void BST<T>::LevelOrder() //按层次周游二叉树
{
    Queue<BSTNode<T> *> *q = new Queue<BSTNode<T> *>();
    BSTNode<T> *node = root;
    BSTNode<T> *item;
    q->enQueue(node);
    while (!q->IsEmpty())
    {
        q->deQueue(item);
        cout << item->GetValue();
        if (item->GetLeftChild())
            q->enQueue(item->GetLeftChild());
        if (item->GetRightChild())
            q->enQueue(item->GetRightChild());
    }
}

template <class T>
BSTNode<T> *BST<T>::GetParent(BSTNode<T> *current)
{
    if (this->IsEmpty() || !current)
    {
        return nullptr;
    }
    BSTNode<T> *node = root;
    int num;
    LeafNum(this->GetRoot(), num);
    Stack<BSTNode<T> *> *s = new Stack<BSTNode<T> *>(num);
    while (!s->IsEmpty() || node)
    {
        if (node)
        {
            if (node->GetLeftChild() == current || node->GetRightChild() == current)
            {
                return node;
            }
            s->push(node);
            node = node->GetLeftChild();
        }
        else
        {
            s->pop(node);
            node = node->GetRightChild();
        }
    }
}

template <class T>
void BST<T>::Insert(T data)
{
    if (this->IsEmpty())
    {
        root = new BSTNode<T>(data);
        root->SetValue(data);
        return;
    }
    BSTNode<T> *node = root;
    BSTNode<T> *temp = new BSTNode<T>(data);
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
                node->SetRightChild(temp);
                return;
            }
        }
        else
        {
            if (node->GetLeftChild())
                node = node->GetLeftChild();
            else
            {
                node->SetLeftChild(temp);
                return;
            }
        }
    }
}

template <class T>
bool BST<T>::IsHave(const T &data, BSTNode<T> *ret) //用ret接当前这个节点
{
    if (this->IsEmpty())
    {
        cout << "树是空的\n";
        return false;
    }
    BSTNode<T> *node = root;
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

template <class T>
void BST<T>::DeleteNode(const T &data)
{
    if (this->IsEmpty())
    {
        cout << "树是空的 没得删\n";
        return;
    }
    BSTNode<T> *pointer;
    if (this->IsHave(data, pointer))
    {
        BSTNode<T> *temppointer;                    //用于保存替换节点;
        BSTNode<T> *tempparent = nullptr;           //用于保存替换节点的父节点
        BSTNode<T> *parent = this->Parent(pointer); //用于保存待删除结点的父节点

        if (pointer->GetLeftChild() == nullptr)     // 如果待删除结点的左子树为空
            temppointer = pointer->GetRightChild(); // 替换结点赋值为其右子树的根
        else
        {
            // 待删除结点左子树不空,在左子树中
            // 寻找最大结点作为替换结点
            temppointer = pointer->GetLeftChild();
            while (temppointer->GetRightChild() != NULL)
            {
                //寻找左子树中的最大结点
                tempparent = temppointer;
                temppointer = temppointer->GetRightChild(); // 向右下降
            }
            if (tempparent == NULL)                                 // 如果替换结点就是被删结点的左子结点
                pointer->SetLeftChild(temppointer->GetLeftChild()); // 替换结点左子树挂接到被删结点的
            //左子树
            else
            {
                tempparent->SetRightChild(temppointer->GetLeftChild()); // 替换结点的左子树作为其父结点右
            }
            // 子树
            temppointer->SetLeftChild(pointer->GetLeftChild());   // 继承 pointer的左子树
            temppointer->SetRightChild(pointer->GetRightChild()); //继承pointer的右子树
        }
        // 下面用替换结点代替待删除结点
        if (parent == NULL)
            root = temppointer;
        else if (parent->GetLeftChild() == pointer)
            parent->SetLeftChild(temppointer);
        else
            parent->SetRightChild(temppointer);
        delete pointer; // 删除该结点
        pointer = NULL;
        return;
    }
}

// // template <class T>
// // void BST<T>::CreateTree(const T &info, BST<T> &leftTree, BST<T> &rightTree) // 构造新树
// // {
// //     root = new BSTNode<T>(info, leftTree.root, rightTree.root);
// //     leftTree.root = nullptr;  //防止非法访问
// //     rightTree.root = nullptr; //防止非法访问
// // }

// template <class T>
// void printRange(BSTNode<T> *n, T min, T max)
// {
//     if (n != NULL)
//         if (n->GetValue() >= min)
//             printRange(n->GetLeftChild(), min, max);
//     if (n->GetValue() >= min & n->GetValue() <= max)
//         cout << n->GetValue();
//     if (n->GetValue() <= max)
//         printRange(n->GetRightChild(), min, max);
// }

// template <class T>
// bool IsMinHeap(T *node)
// {
//     T *heapArray = node;
//     int i = 0;
//     int k = 0;
//     while (heapArray[i] != 0)
//     {
//         k = LeftChild(i);
//         T temp = heapArray[i];
//         if (heapArray[k] != 0)
//         {
//             if ((heapArray[k + 1] != 0) && (heapArray[k] > heapArray[k + 1]))
//             {
//                 k++;
//             }
//             if (temp > heapArray[k])
//             {
//                 return false;
//             }
//             i++;
//             return true;
//         }
//     }
// }

// template <class T>
// bool CompareTree(TreeNode<T> *root1, TreeNode<T> *root2) //
// {
//     T item1, item2;
//     if (root1 == NULL && root2 == NULL)
//         return true;
//     else if ((root1 != NULL && root2 == NULL) | (root1 == NULL && root2 != NULL))
//         return false;
//     else if (root1 != NULL && root2 != NULL)
//         item1 = root1->getValue();
//     item2 = root2->getValue();
//     if (item1 != item2)
//         return false;
//     else
//     {
//         if (CompareTree(root1->getLeftMostChild(), root2->getLeftMostChild()) && ConpareTree(root1->getRightsibling(), root2->getRightsibling()))
//             return true;
//     }
// }
// template <class T>
// class TreeNode
// {
//     int a;
// };

// template <class T>
// class Tree
// {
// };

// int Number(Tree<T> &t)
// {
//     Stack<TreeNode<T> *> s(10);
//     int num = 0;
//     TreeNode<T> *pointer = t.getRoot();
//     TreeNode<T> *p1;
//     s.push(NULL);
//     while (pointer != NULL)
//     {
//         num++;
//         if (pointer->Rightsibling() != NULL)
//         {
//             s.push(pointer->Rightsibling());
//         }
//         if (pointer->LeftMostchild() != NULL)
//         {
//             pointer = pointer->LeftMostchild();
//         }
//         else
//         {
//             s.ttop(pointer);
//             s.pop(p1);
//         }
//     }
//     return num;
// }

// template <class T>
// BST<T> func(TreeNode<T> *root)
// {
//     T temp;
//     BST<T> t1 = BST<T>();
//     BST<T> t2 = BST<T>();
//     BST<T> t3 = BST<T>();
//     BSTNode<T> *p = new BSTNode<T>();
//     if (root != NULL)
//     {
//         temp = root->value();
//         p->setvalue(temp);
//         t1->GetRoot() = p;
//         t3 = func(root->LeftMostchild());
//         t1.GetRoot()->setLeftchi1d(t3.GetRoot());
//         t2 = func(root->Rightsib1ing());
//         t1.GetRoot()->setRightchi1d(t2.GetRoot());
//         return t1;
//     }
//     else
//     {
//         t1.GetRoot() = NULL;
//         return t1;
//     }
// }
#endif
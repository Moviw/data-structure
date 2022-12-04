#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include "C:\Users\19735\Desktop\data_structure\Chap2_linear_list\Linked_List\Linked_List.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\queue\queue.h"
#include "C:\Users\19735\Desktop\data_structure\Chap3_stack_queue\stack\stack.h"
#include "C:\Users\19735\Desktop\data_structure\Chap2_linear_list\List\List.h"
using namespace std;

//邻接矩阵是无向图  邻接表是有向图
#define INF 65535
class Edge
{
public:
    int from, to, weight;
    Edge()
    {
        from = -1;
        to = -1;
        weight = 0;
    }
    Edge(int f, int t, int w)
    {
        from = f;
        to = t;
        weight = w;
    }
    bool IsEdge() { return weight; } // 是否是边 只需判断是否权重为0即可
};

//对于无向图:由于对称 行和列都是该顶点的度数
//对于有向图:行为出度，列为入度
template <class T>
class Graph
//图的抽象数据类型
{
protected:
    int numVertex; //顶点个数
    int numEdge;   //边条数
    int *Mark;     //访问标记  周游时候用
    int *Indegree; //入度
    int **matrix;  //邻接矩阵

public:
    Graph(int numVert)
    {
        numVertex = numVert;
        numEdge = 0;
        Indegree = new int[numVertex];
        Mark = new int[numVertex];
        for (int i = 0; i < numVertex; i++)
        {
            Mark[i] = 0;     //初始化访问标记均为0
            Indegree[i] = 0; //初始化所有点入度为0
        }
    }
    virtual ~Graph()
    {
        delete[] Mark;
        delete[] Indegree;
    }
    int VerticesNum() { return numVertex; } //返回图的顶点个数
    int EdgesNum() { return numEdge; }      //返回图的边数
    // virtual Edge FirstEdge(int oneVertex) = 0;                          //返回依附于顶点oneVertex的第一条边
    // virtual Edge NextEdge(Edge preEdge) = 0;                            //返回与preEdge有相同顶点的下一条边
    // virtual void setEdge(int fromVertex, int toVertex, int weight) = 0; //添加边
    // virtual void delEdge(int fromVertex, int toVertex) = 0;             //删除边
    int ToVertex(Edge e) { return e.to; } //返回边edge的终点
    // int FromVertex(Edge oneEdge);                                       // 返回oneEdge的始点
    // int ToVertex(Edge oneEdge);                                         //返回oneEdge的终点
    // int Weight(Edge oneEdge);                                           //返回oneEdge的权
};

template <class T>
class GraphAM : public Graph<T> //使用邻接矩阵存储图的关系
{
private:
    int **matrix;

public:
    GraphAM(int numVert) : Graph<T>(numVert)
    {
        //创建邻接矩阵
        matrix = (int **)new int[numVert];
        this->numEdge = 0;
        for (int i = 0; i < numVert; i++)
        {
            matrix[i] = new int[numVert];
        }
        for (int i = 0; i < numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    void ShowMatrix()
    {
        cout << "\t";
        for (int i = 0; i < this->numVertex; i++)
        {
            printf("%d\t", i);
        }
        cout << endl;
        for (int i = 0; i < this->numVertex; i++)
        {
            cout << i << "\t";
            for (int j = 0; j < this->numVertex; j++)
            {
                printf("%d\t", matrix[i][j]);
            }
            cout << endl;
        }
    }
    GraphAM(int numVert, int numEdge) : Graph<T>(numVert)
    {
        matrix = (int **)new int[numVert];

        this->numEdge = numEdge;

        for (int i = 0; i < numVert; i++)
        {
            matrix[i] = new int[numVert];
        }

        for (int i = 0; i < numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                matrix[i][j] = 0;
            }
        }

        for (int k = 0; k < this->numEdge; k++) /* 读入numEdges条边，建立邻接矩阵 */
        {
            int i, j, w;
            printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
            scanf("%d,%d,%d", &i, &j, &w); /* 输入边(vi,vj)上的权w */
            matrix[i][j] = w;
            matrix[j][i] = matrix[i][j]; /* 因为是无向图，矩阵对称 */
        }

        for (int i = 0; i < this->numVertex; i++) //为顶点表赋值
        {
            for (int j = 0; j < this->numVertex; j++)
                this->Indegree[i] += matrix[j][i]; //入度等于邻接矩阵的列之和
        }
    }
    virtual ~GraphAM()
    {
        for (int i = 0; i < this->VerticesNum(); i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    virtual Edge FirstEdge(int oneVertex)
    {
        Edge temp;
        temp.from = oneVertex;
        for (int i = 0; i < this->numVertex; i++)
        {
            if (matrix[oneVertex][i] != 0)
            {
                temp.to = i;
                temp.weight = matrix[oneVertex][i];
                break;
            }
        }
        return temp;
    }

    virtual Edge NextEdge(Edge preEdge)
    {
        Edge temp;
        temp.from = preEdge.from;
        if (preEdge.to < this->numVertex)
        {
            for (int i = preEdge.to + 1; i < this->numVertex; i++)
            {
                if (matrix[preEdge.from][i] != 0)
                {
                    temp.to = i;
                    temp.weight = matrix[preEdge.from][i];
                    break;
                }
            }
        }
        return temp;
    }

    void setEdge(int fromVertex, int toVertex, int weight = 1) //添加边
    {
        matrix[fromVertex][toVertex] = weight;
        matrix[toVertex][fromVertex] = weight;
        this->numEdge++;
        this->Indegree[toVertex]++;
        this->Indegree[fromVertex]++;
    }

    void delEdge(int fromVertex, int toVertex) //删除边
    {
        matrix[fromVertex][toVertex] = 0;
        matrix[toVertex][fromVertex] = 0;
        this->numEdge--;
        this->Indegree[toVertex]--;
        this->Indegree[fromVertex]--;
    }

    friend void DFSTraverse(GraphAM &g, int i) //深度优先遍历
    {
        int u, j;
        int temp;
        Stack<int> *s = new Stack<int>(g.VerticesNum());
        for (int i = 0; i < g.VerticesNum(); i++)
        {
            // Edge e = g.FirstEdge(i);
            if (g.Mark[i] == 0)
            {
                cout << i << "->";
                g.Mark[i] = 1;
                s->push(i);

                while (!s->isEmpty())
                {
                    s->pop(u);
                    for (j = 0; j < g.VerticesNum(); j++)
                    {
                        if ((g.Mark[j] == 0) && (g.matrix[u][j] == 1))
                        {
                            g.Mark[j] = 1;
                            s->push(j);
                            cout << j << "->";
                            break;
                        }
                    }
                }
            }
        }
    }

    friend void BFSTraverse(GraphAM &g, int i) //广度优先遍历
    {
        int u;
        Queue<int> *q = new Queue<int>(g.VerticesNum());
        for (size_t i = 0; i < g.VerticesNum(); i++)
        {
            if (g.Mark[i] == 0)
            {
                cout << i << "->";
                g.Mark[i] = 1;

                q->enQueue(i);
                while (!q->isEmpty())
                {
                    q->deQueue(u);
                    for (int i = 0; i < g.VerticesNum(); i++)
                    {
                        if (g.Mark[i] == 0 && g.matrix[u][i] == 1)
                        {
                            g.Mark[i] = 1;
                            q->enQueue(i);
                            cout << i << "->";
                        }
                    }
                }
            }
        }
        cout << endl;
    };

    void Topological_Sorting()
    {
        Queue<int> *q = new Queue<int>(this->VerticesNum());
        for (int i = 0; i < this->VerticesNum(); i++)
        {
            if (this->Indegree[i] == 0)
            {
                q->enQueue(i);
            }
        }

        while (!q->isEmpty())
        {
            int u;
            q->deQueue(u);
            cout << u << "->";
            this->Mark[u] = 1;
            for (Edge e = FirstEdge(u); e.IsEdge(); e = NextEdge(e))
            {
                this->Indegree[this->ToVertex(e)]--;
                if (this->Indegree[this->ToVertex(e)] == 0)
                {
                    q->enQueue(this->ToVertex(e)); //入度为0的顶点入队}
                }
            }
        }
        for (int i = 0; i < this->VerticesNum(); i++)
        {
            if (this->Mark[i] == 0)
            {
                printf("图有环"); //图有环
                break;
            }
        }
    }

    void Kruskal()
    {
    }
};

//边界点的结构体定义
typedef struct listUnit
{
    int vertex = -1;
    int weight = 0;
} listUnit;

ostream &operator<<(ostream &cout, listUnit &s)
{
    cout << s.vertex << "(weight=" << s.weight << ")->";
    return cout;
}

template <class T>
class Graphl : public Graph<T> //用邻接表储存
{
private:
    List<Linked_List<listUnit> *> *graList; //邻接表 这是一个数组 里面每一个元素都是一个个链表
public:
    Graphl(int numVert) : Graph<T>(numVert)
    {
        //创建邻接表
        graList = new List<Linked_List<listUnit> *>(numVert);
        for (int i = 0; i < numVert; i++)
        {
            graList->setValue(i, new Linked_List<listUnit>());
        }
        this->numEdge = 0;
    }

    Graphl(int numVert, int numEdge) : Graph<T>(numVert)
    {
        //创建邻接表
        graList = new List<Linked_List<listUnit> *>(numVert);
        for (int i = 0; i < numVert; i++)
        {
            graList->setValue(i, new Linked_List<listUnit>());
        }
        this->numEdge = numEdge;
    }

    void showLinkList()
    {
        for (int i = 0; i < this->VerticesNum(); i++)
        {
            cout << "node " << i << " connects with : ";
            Linked_List<listUnit> *temp;
            graList->getValue(i, temp);
            temp->Show();
        }
    }

    virtual ~Graphl()
    {

        delete[] graList;
    }

    virtual void setEdge(int fromVertex, int toVertex, int weight = 1) //添加边
    {
        Linked_List<listUnit> *i;
        graList->getValue(fromVertex, i);
        Link<listUnit> *temp = i->getHead();
        while (temp->next != NULL && temp->next->data.vertex < toVertex)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            //边不存在且最后一条边
            temp->next = new Link<listUnit>;
            temp->next->data.vertex = toVertex;
            temp->next->data.weight = weight;
            this->numEdge++;
            this->Indegree[toVertex]++;
            return;
        }
        if (temp->next->data.vertex == toVertex)
        {
            // 边存在
            temp->next->data.weight = weight;
            return;
        }
        if (temp->next->data.vertex > toVertex)
        {
            // 边不存在，但后边还有边
            Link<listUnit> *other = temp->next;
            temp->next = new Link<listUnit>;
            temp->next->data.vertex = toVertex;
            temp->next->data.weight = weight;
            temp->next->next = other;
            this->numEdge++;
            this->Indegree[toVertex]++;
            return;
        }
    }

    // virtual void delEdge(int fromVertex, int toVertex) //删除边
    // {
    //     Link<listUnit> *temp = graList[fromVertex].getHead();
    //     this->numEdge--;
    //     while (temp->next != NULL && temp->next->data.vertex < toVertex)
    //         temp = temp->next;
    //     if (temp->next == NULL)
    //         return;
    //     if (temp->next->data.vertex > toVertex)
    //         return;
    //     if (temp->next->data.vertex == toVertex)
    //     {
    //         Link<listUnit> *other = temp->next->next;
    //         delete temp->next;
    //         temp->next = other;
    //         this->Indegree[toVertex]--;
    //         return;
    //     }
    // }

    friend void DFSTraverse(Graphl &g, int i) //深度优先遍历
    {
        int u;
        int fei;
        Stack<int> *s = new Stack<int>(g.VerticesNum());
        for (size_t i = 0; i < g.VerticesNum(); i++)
        {
            if (g.Mark[i] == 0)
            {
                cout << i << "->";
                g.Mark[i] = 1;

                s->push(i);
                while (!s->isEmpty())
                {
                    s->topValue(u);
                    Linked_List<listUnit> *temp;
                    Link<listUnit> *p;
                    g.graList->getValue(u, temp);
                    p = temp->getHead()->next;

                    while (p)
                    {
                        int num = p->data.vertex;
                        if (g.Mark[num] == 0)
                        {
                            g.Mark[num] = 1;
                            s->push(num);
                            cout << num << "->";
                            g.graList->getValue(num, temp);
                            p = temp->getHead()->next;
                        }
                        else
                        {
                            p = p->next;
                        }
                    }
                    s->pop(fei);
                }
            }
        }
        cout << endl;
    }

    friend void BFSTraverse(Graphl &g, int i) //广度优先遍历
    {
        int u;
        Queue<int> *q = new Queue<int>(g.VerticesNum());
        for (size_t i = 0; i < g.VerticesNum(); i++)
        {
            if (g.Mark[i] == 0)
            {
                cout << i << "->";
                g.Mark[i] = 1;

                q->enQueue(i);
                while (!q->isEmpty())
                {
                    q->deQueue(u);
                    Linked_List<listUnit> *temp;
                    Link<listUnit> *p;
                    g.graList->getValue(u, temp);
                    p = temp->getHead()->next;

                    while (p)
                    {
                        int num = p->data.vertex;
                        if (g.Mark[num] == 0)
                        {
                            g.Mark[num] = 1;
                            q->enQueue(num);
                            cout << num << "->";
                        }
                        p = p->next;
                    }
                }
            }
        }
        cout << endl;
    }
};
#endif

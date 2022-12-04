#include <iostream>
using namespace std;
#include <algorithm>
#include <climits>
#define LIMIT 65535
#define rep(i, a, n) for (int i = a; i < n; i++)

using namespace std;

struct AMGraph
{
    int *visited;
    int **arcWeight;
    int currVex, currArc;
    int *bingcha; //并查集 判断是否成环时会用到
};

int find(AMGraph &g, int x) //并查集 找父亲的函数
//注意这里使用的是递归查找，可以让这个点（A）的父亲也认A的祖先做父亲，使得一次递归经过的所有点的父亲都变成祖先，大大降低了时间复杂度。
{
    if (g.bingcha[x] == x)
        return x;
    return g.bingcha[x] = find(g, g.bingcha[x]);
}

void createUND(AMGraph &G)
{
    cout << "分别输入顶点个数 和 边个数\n";
    cin >> G.currVex >> G.currArc;
    G.visited = new int[G.currVex];
    G.bingcha = new int[G.currVex];
    for (int i = 0; i < G.currVex; i++)
    {
        G.bingcha[i] = i; //重点！必须事先把每个点的父亲赋值为它自己，不然默认每个点父亲都是0，会出错。
    }
    G.arcWeight = new int *[G.currVex];
    for (int i = 0; i < G.currVex; i++)
    {
        G.arcWeight[i] = new int[G.currVex];
        for (int j = 0; j < G.currVex; j++)
            G.arcWeight[i][j] = LIMIT;
    }

    fill(G.visited, G.visited + G.currVex, 0); // 0代表还未访问过
    int v1, v2;
    int i, j, power;

    for (int k = 0; k < G.currArc; k++)
    {
        cout << "输入第" << k + 1 << "条边的信息(默认为无向图): "
             << "起、止点(从0开始)、权重" << endl;
        cin >> v1 >> v2 >> power;
        i = v1;
        j = v2;
        G.arcWeight[i][j] = power;
        G.arcWeight[j][i] = power;
    }
}

typedef struct edge
{
    int from;
    int to;
    int weight;
} edge;

bool operator<(edge &e1, edge &e2)
{
    return e1.weight < e2.weight;
}
void Kruskal(AMGraph &g)
{
    int i, j, k = 0;
    edge *edge_sorted = new edge[g.currArc];

    rep(i, 0, g.currVex) //获得所有的边
    {
        rep(j, i, g.currVex)
        {
            if (g.arcWeight[i][j] != LIMIT)
            {
                edge_sorted[k++] = edge{i, j, g.arcWeight[i][j]};
            }
        }
    }

    rep(i, 0, g.currArc) //选择排序
    {
        int min = i;
        for (int j = i + 1; j < g.currArc; j++)
        {
            if (edge_sorted[j] < edge_sorted[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            edge temp = edge_sorted[min];
            edge_sorted[min] = edge_sorted[i];
            edge_sorted[i] = temp;
        }
    }

    k = 0;
    edge *edge_needed = new edge[g.currVex - 1]; //所有需要的边 共n-1个
    rep(i, 0, g.currArc)
    {
        int from = edge_sorted[i].from;
        int to = edge_sorted[i].to;
        if (find(g, g.bingcha[from]) == find(g, g.bingcha[to]))
        {
            continue; //如果两个点的父亲相同（已经合并了），就不管它了
        }
        edge_needed[k++] = edge{from, to, edge_sorted[i].weight};
        g.bingcha[find(g, edge_sorted[i].from)] = find(g, edge_sorted[i].to);
    }

    rep(i, 0, g.currVex - 1)
    {
        cout << edge_needed[i].from << " " << edge_needed[i].to << " " << edge_needed[i].weight << endl;
    }
}

int main()
{
    AMGraph g;
    createUND(g);

    Kruskal(g);
}

/*
7 12
0 1 12
1 2 10
2 3 3
3 4 4
2 4 5
4 6 8
4 5 2
5 6 9
6 0 14
5 0 16
5 1 7
5 2 6
*/
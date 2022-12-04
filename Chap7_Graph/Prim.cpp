#include <iostream>
#include <algorithm>
#include <climits>
#define LIMIT INT_MAX

using namespace std;

struct AMGraph
{
    int *vertices;
    int *visited;
    int **arcWeight;
    int currVex, currArc;
};

void createUND(AMGraph &G)
{
    cout << "分别输入顶点个数 和 边个数\n";
    cin >> G.currVex >> G.currArc;
    G.vertices = new int[G.currVex];
    G.visited = new int[G.currVex];
    for (int i = 0; i < G.currVex; i++)
    {
        G.vertices[i] = i + 1;
    }
    G.arcWeight = new int *[G.currVex];
    for (int i = 0; i < G.currVex; i++)
    {
        G.arcWeight[i] = new int[G.currVex];
        for (int j = 0; j < G.currVex; j++)
            if (i == j)
                G.arcWeight[i][j] = 0;
            else
                G.arcWeight[i][j] = LIMIT;
    }

    fill(G.visited, G.visited + G.currVex, 0);
    int v1, v2;
    int i, j, power;
    for (int k = 0; k < G.currArc; k++)
    {
        cin >> v1 >> v2 >> power; //顶点从1开始
        i = v1 - 1;
        j = v2 - 1;
        G.arcWeight[i][j] = power;
        G.arcWeight[j][i] = power;
    }
    return;
}

typedef struct edge
{
    int from;
    int to;
    int weight;
} edge;

void Prim(AMGraph &G)
{
    int Min[G.currVex];
    edge ret[G.currVex - 1];
    fill(Min, Min + G.currVex, LIMIT);
    Min[0] = LIMIT;
    int MST = 0;
    G.visited[0] = 1;
    int h1 = -1, h2 = -1;
    int minWeight = LIMIT;

    for (int k = 1; k < G.currVex; k++)
    {
        for (int i = 0; i < G.currVex; i++)
        {
            for (int j = 0; j < G.currVex; j++)
            {
                if (G.visited[i] == 1 && G.visited[j] == 0 && G.arcWeight[i][j] < minWeight)
                {

                    minWeight = G.arcWeight[i][j];
                    h1 = i;
                    h2 = j;
                }
            }
        }

        if (h2 < h1)
        {
            // cout << minWeight << " " << h2 + 1 << " " << h1 + 1 << endl;
            ret[k - 1].from = h2 + 1;
            ret[k - 1].to = h1 + 1;
            ret[k - 1].weight = minWeight;
        }
        else
        {
            // cout << minWeight << " " << h1 + 1 << " " << h2 + 1 << endl;
            ret[k - 1].from = h1 + 1;
            ret[k - 1].to = h2 + 1;
            ret[k - 1].weight = minWeight;
        }
        G.visited[h2] = 1;
        minWeight = LIMIT; // minWeight重置
    }

    for (int i = 0; i < G.currVex - 2; i++)
    {
        int min = i;
        for (int j = i + 1; j < G.currVex - 1; j++)
        {
            if (ret[j].weight < ret[min].weight)
            {
                min = j;
            }
        }
        if (min != i)
        {
            edge temp = ret[i];
            ret[i] = ret[min];
            ret[min] = temp;
        }
    }

    for (int i = 0; i < G.currVex - 1; i++)
    {
        cout << ret[i].weight << " " << ret[i].from << " " << ret[i].to << endl;
    }
}

int main()
{
    AMGraph G;
    createUND(G);
    Prim(G);
    return 0;
}
/*
4 5
1 3 2
2 4 40
4 1 20
1 2 10
3 2 5
*/

/*
6 10
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 5 6
3 4 5
4 6 2
5 6 6
3 6 4
*/
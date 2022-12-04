#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

struct AMG_Graph
{
    int vex_num, edge_num;

    char Vex[MAX];
    int Edge[MAX][MAX];
};

struct AMG_Graph *Create_AMG_Graph(void);
void Show_AMG_Graph_dist_p(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);
void Floyd(struct AMG_Graph *graph);

double dist[MAX][MAX];
int p[MAX][MAX];

int main(void)
{
    struct AMG_Graph *d_graph;
    char start, end;
    int s, e;

    d_graph = Create_AMG_Graph();
    Show_AMG_Graph_dist_p(d_graph);

    Floyd(d_graph);
    printf("\n\nNow show the shortest distance matrix:\n");
    Show_AMG_Graph_dist_p(d_graph);

    printf("Please enter the start and end point:\n");
    scanf("%c %c", &start, &end);
    s = search_vex(d_graph, start);
    e = search_vex(d_graph, end);
    printf("The shortest distance between %c and %c is %.1f.\n", start, end, dist[s][e]);

    return 0;
}

struct AMG_Graph *Create_AMG_Graph(void)
{
    int i, j;
    char u, v;
    double l;

    struct AMG_Graph *graph;

    graph = (struct AMG_Graph *)malloc(sizeof(struct AMG_Graph));

    printf("Please enter the number of vex: ");
    scanf("%d", &graph->vex_num);
    printf("Please enter the number of edge: ");
    scanf("%d", &graph->edge_num);

    while (getchar() != '\n')
        ;

    printf("Please enter vertex:\n");
    for (i = 0; i < graph->vex_num; i++)
    {
        graph->Vex[i] = getchar();
        while (getchar() != '\n')
            ;
    }

    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
        {
            graph->Edge[i][j] = 0;

            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INFINITY;

            p[i][j] = -1;
        }
    }

    while (graph->edge_num--)
    {
        printf("Please enter the vex that connect each other by edge:\n");
        u = getchar();
        while (getchar() != '\n')
            ;
        v = getchar();
        while (getchar() != '\n')
            ;

        printf("Please enter the distance between the two vex:\n");
        scanf("%lf", &l);
        while (getchar() != '\n')
            ;

        i = search_vex(graph, u);
        j = search_vex(graph, v);

        if (i != -1 && j != -1)
        {
            graph->Edge[i][j] = 1;
            dist[i][j] = l;
            p[i][j] = i;
        }
        else
        {
            printf("You have entered wrong vex, please enter again.\n");
            graph->edge_num++;
        }
    }

    return graph;
}

void Show_AMG_Graph_dist_p(struct AMG_Graph *graph)
{
    int i, j;

    printf("Show the vex: \n");
    for (i = 0; i < graph->vex_num; i++)
        printf("%c ", graph->Vex[i]);
    printf("\n");

    printf("Show the adjacency matrices:\n");
    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            printf("%d\t", graph->Edge[i][j]);
        printf("\n");
    }

    printf("Show the distance matices:\n");
    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            printf("%.1f\t", dist[i][j]);
        printf("\n");
    }

    printf("Show the pre point matices:\n");
    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            printf("%d\t", p[i][j]);
        printf("\n");
    }
}

int search_vex(struct AMG_Graph *graph, char c)
{
    int i;

    for (i = 0; i < graph->vex_num; i++)
    {
        if (c == graph->Vex[i])
            return i;
    }

    return -1;
}

void Floyd(struct AMG_Graph *graph)
{
    int k, i, j;

    for (k = 0; k < graph->vex_num; k++)
    {
        for (i = 0; i < graph->vex_num; i++)
        {
            for (j = 0; j < graph->vex_num; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}

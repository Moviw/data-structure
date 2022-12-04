#include <iostream>
#include "Graph.h"
#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
    // GraphAM<int> g(7);
    // g.setEdge(0, 1);
    // g.setEdge(0, 2);
    // g.setEdge(0, 4);
    // g.setEdge(1, 2);
    // g.setEdge(2, 3);
    // g.setEdge(2, 4);
    // g.setEdge(3, 4);
    // g.setEdge(5, 6);

    // g.ShowMatrix();
    // BFSTraverse(g, 0);

    // Graphl<int> gl(7);
    // gl.setEdge(0, 1);
    // gl.setEdge(0, 2);
    // gl.setEdge(0, 4);
    // gl.setEdge(1, 2);
    // gl.setEdge(2, 3);
    // gl.setEdge(2, 4);
    // gl.setEdge(3, 4);
    // gl.setEdge(5, 6);
    // gl.showLinkList();
    // BFSTraverse(gl, 0);

    // GraphAM<int> g(5);
    // g.setEdge(0, 1);
    // g.setEdge(0, 2);
    // g.setEdge(0, 4);
    // g.setEdge(1, 2);
    // g.setEdge(2, 3);
    // g.setEdge(2, 4);
    // g.setEdge(3, 4);

    // g.ShowMatrix();
    // DFSTraverse(g, 0);
    // cout << endl;

    // Graphl<int> gl(5);
    // gl.setEdge(0, 1);
    // gl.setEdge(0, 2);
    // gl.setEdge(0, 4);
    // gl.setEdge(1, 2);
    // gl.setEdge(2, 3);
    // gl.setEdge(2, 4);
    // gl.setEdge(3, 4);
    // gl.showLinkList();
    // DFSTraverse(gl, 0);

    GraphAM<int> g(7);
    g.setEdge(0, 2);
    g.setEdge(0, 3);
    g.setEdge(1, 4);
    g.setEdge(1, 3);
    g.setEdge(3, 6);
    g.setEdge(4, 6);
    g.setEdge(2, 6);
    g.setEdge(2, 5);
    g.ShowMatrix();
    g.Topological_Sorting();
}
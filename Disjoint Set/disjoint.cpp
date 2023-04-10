#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int src, dest;
};

struct Graph {
    int V, E; // V: number of vertices, E: number of edges
    struct Edge* edges;
};

Graph createGraph(int V, int E) {
    Graph graph;
    graph.V = V;
    graph.E = E;
    graph.edges = (Edge*)malloc(sizeof(Edge) * E);
    return graph;
}

int findParent(int parent[], int pos) {
    // if (parent[pos] == pos) return pos;
    // return findParent(parent, parent[pos]);
    return (parent[pos] == pos) ? pos : findParent(parent, parent[pos]);
}

bool isCycle(Graph graph) {
    int parent[graph.V];

    //MAKE SETS
    for (int i = 0; i < graph.V; i++) {
        parent[i] = i;
    }

    //FIND SETS
    for (int i = 0; i < graph.E; i++) {
        int src = graph.edges[i].src;
        int dest = graph.edges[i].dest;

        int srcParent = findParent(parent, src);
        int destParent = findParent(parent, dest);

        if (srcParent == destParent) return true;

        //UNION
        parent[srcParent] = destParent;
    }
    return false;
}

int main() {
    int V = 4;
    int E = 4;
    Graph graph = createGraph(V, E);
    graph.edges[0].src = 0;
    graph.edges[0].dest = 1;
    // graph.edges[0] = {0, 1}; 
    graph.edges[1].src = 1;
    graph.edges[1].dest = 2;
    // graph.edges[2] = { 1, 2};
    graph.edges[2].src = 2;
    graph.edges[2].dest = 3;
    // graph.edges[3] = { 2, 3};
    graph.edges[3].src = 3;
    graph.edges[3].dest = 0;
    // graph.edges[4] = { 3, 0};

    printf("Graph is %s\n", isCycle(graph) ? "cyclic" : "safe");
    return 0;
}
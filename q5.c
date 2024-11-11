#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edge;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(graph->E * sizeof(Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);
}

void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)malloc(V * sizeof(int));

    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(parent, rank, x, y);
        }
    }

    printf("Edges in the MST (Kruskal's Algorithm):\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning Tree: %d\n", minimumCost);

    free(parent);
    free(rank);
}

void PrimMST(int graph[MAX][MAX], int V) {
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++) {
            if (mstSet[v] == 0 && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        int u = min_index;
        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edges in the MST (Prim's Algorithm):\n");
    int minimumCost = 0;
    for (int i = 1; i < V; i++) {
        printf("%d -- %d == %d\n", parent[i], i, graph[i][parent[i]]);
        minimumCost += graph[i][parent[i]];
    }
    printf("Minimum Cost Spanning Tree: %d\n", minimumCost);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    Graph* graph = createGraph(V, E);

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    int adjMatrix[MAX][MAX];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        adjMatrix[graph->edge[i].src][graph->edge[i].dest] = graph->edge[i].weight;
        adjMatrix[graph->edge[i].dest][graph->edge[i].src] = graph->edge[i].weight;
    }

    printf("Prim's Algorithm:\n");
    PrimMST(adjMatrix, V);

    printf("Kruskal's Algorithm:\n");
    KruskalMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}
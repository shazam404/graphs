#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void takeGraphInput(int V, int graph[V][V], int *E, int edges[V * (V - 1) / 2][3]) {
    printf("Enter the adjacency matrix (use -1 for infinity):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int input;
            scanf("%d", &input);
            if (input == -1) {
                graph[i][j] = INF;
            } else {
                graph[i][j] = input;
            }
            if (graph[i][j] != 0 && graph[i][j] != INF && i < j) {
                edges[*E][0] = i;
                edges[*E][1] = j;
                edges[*E][2] = graph[i][j];
                (*E)++;
            }
        }
    }
}

int minDistance(int dist[], int sptSet[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void dijkstra(int V, int graph[][V], int src) {
    int dist[V];
    int sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V);
}

void bellmanFord(int edges[][3], int E, int V, int src) {
    int dist[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            int weight = edges[j][2];
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printSolution(dist, V);
}

int main() {
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    int graph[V][V];
    int E = 0;
    int edges[V * (V - 1) / 2][3];

    takeGraphInput(V, graph, &E, edges);

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    printf("Dijkstra's Algorithm:\n");
    bellmanFord(edges, E, V, src);

    printf("Bellman-Ford Algorithm:\n");
    bellmanFord(edges, E, V, src);

    return 0;
}
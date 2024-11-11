#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}


void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void DFS_Display(Graph* graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    printf("DFS starting from vertex %d:\n", startVertex);
    DFS(graph, startVertex);
    printf("\n");
}


int DFS_Search(Graph* graph, int vertex, int key, int path[], int* pathIndex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    path[(*pathIndex)++] = vertex;

    if (vertex == key) {
        return 1;
    }

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            if (DFS_Search(graph, connectedVertex, key, path, pathIndex)) {
                return 1;
            }
        }
        temp = temp->next;
    }

    (*pathIndex)--;
    return 0;
}

void DFS_Connect(Graph* graph, int vertex) {
    DFS(graph, vertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            printf("Graph is not connected\n");
            return;
        }
    }
    printf("Graph is connected\n");
}


int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    DFS_Display(graph, startVertex);

    int key;
    printf("Enter the key to search in the graph: ");
    scanf("%d", &key);
    int path[MAX];
    int pathIndex = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    if (DFS_Search(graph, startVertex, key, path, &pathIndex)) {
        printf("Path to key %d: ", key);
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Key %d not found in the graph\n", key);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    DFS_Connect(graph, startVertex);

    return 0;
}

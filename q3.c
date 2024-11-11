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

typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

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
}

Stack* createStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    stack->items[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        return -1;
    }
    return stack->items[stack->top--];
}

void topologicalSortUtil(Graph* graph, int vertex, Stack* stack) {
    graph->visited[vertex] = 1;

    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            topologicalSortUtil(graph, connectedVertex, stack);
        }
        temp = temp->next;
    }

    push(stack, vertex);
}

void topologicalSort(Graph* graph) {
    Stack* stack = createStack();

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            topologicalSortUtil(graph, i, stack);
        }
    }

    printf("Topological Sort:\n");
    while (!isStackEmpty(stack)) {
        printf("%d ", pop(stack));
    }
    printf("\n");
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

    topologicalSort(graph);

    return 0;
}

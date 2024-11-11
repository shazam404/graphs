#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* adjList[MAX];
Node* transposedAdjList[MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int n = 0;

void insert(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void insertTransposed(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = transposedAdjList[u];
    transposedAdjList[u] = newNode;
}

void push(int v) {
    stack[++top] = v;
}

int pop() {
    if (top == -1)
        return -1;
    return stack[top--];
}

void DFS(int v, Node* adjList[]) {
    visited[v] = 1;

    Node* temp = adjList[v];
    while (temp) {
        int adjVertex = temp->data;
        if (!visited[adjVertex])
            DFS(adjVertex, adjList);
        temp = temp->next;
    }

    push(v);
}

void transposeGraph() {
    for (int v = 0; v < n; v++) {
        Node* temp = adjList[v];
        while (temp) {
            insertTransposed(temp->data, v);
            temp = temp->next;
        }
    }
}

int isStronglyConnected() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            DFS(i, adjList);
    }

    transposeGraph();

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int v = pop();
    DFS(v, transposedAdjList);

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            return 0;
    }
    return 1;
}

int main() {
    int choice, u, v;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
        transposedAdjList[i] = NULL;
    }

    while (1) {
        printf("\n1. Insert\n2. Check Strongly Connected\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the nodes to connect (u v): ");
                scanf("%d %d", &u, &v);
                insert(u, v);
                break;
            case 2:
                if (isStronglyConnected())
                    printf("The graph is strongly connected\n");
                else
                    printf("The graph is not strongly connected\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
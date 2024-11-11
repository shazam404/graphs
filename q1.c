#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;
int n = 0;

void insert(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

void enqueue(int v) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

void BFS_Display(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (front <= rear) {
        int current = dequeue();
        printf("%d ", current);

        for (int i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void BFS_Search(int start, int key) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (front <= rear) {
        int current = dequeue();
        printf("%d ", current);

        if (current == key) {
            printf("\nKey %d found\n", key);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\nKey %d not found\n", key);
}

int BFS_Connect() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    enqueue(0);
    visited[0] = 1;

    while (front <= rear) {
        int current = dequeue();

        for (int i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            return 0; // Graph is not connected
    }
    return 1; // Graph is connected
}

int main() {
    int choice, u, v, start, key;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    while (1) {
        printf("\n1. Insert\n2. BFS_Display\n3. BFS_Search\n4. BFS_Connect\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the nodes to connect (u v): ");
                scanf("%d %d", &u, &v);
                insert(u, v);
                break;
            case 2:
                printf("Enter the starting node: ");
                scanf("%d", &start);
                BFS_Display(start);
                break;
            case 3:
                printf("Enter the starting node: ");
                scanf("%d", &start);
                printf("Enter the key to search: ");
                scanf("%d", &key);
                BFS_Search(start, key);
                break;
            case 4:
                if (BFS_Connect())
                    printf("The graph is connected\n");
                else
                    printf("The graph is not connected\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
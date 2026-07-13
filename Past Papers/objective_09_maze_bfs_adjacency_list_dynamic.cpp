#include <stdio.h>
#include <stdlib.h>
struct AdjNode {
    int dest;
    struct AdjNode * next;
};
struct AdjList {
    struct AdjNode * head;
};
struct Graph {
    int numVertices;
    struct AdjList * array;
};
struct Graph * createGraph(int numVertices) {
    struct Graph * graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList *)malloc(numVertices * sizeof(struct AdjList));
    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}
void addEdge(struct Graph * graph, int src, int dest) {
    struct AdjNode * newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->dest = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}
struct QueueNode {
    int vertex;
    struct QueueNode * next;
};
struct Queue {
    struct QueueNode * front;
    struct QueueNode * rear;
};
struct Queue * createQueue() {
    struct Queue * q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
void enqueue(struct Queue * q, int value) {
    struct QueueNode * temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    temp->vertex = value;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}
int dequeue(struct Queue * q) {
    if (q->front == NULL) {
        return -1;
    }
    struct QueueNode * temp = q->front;
    int value = temp->vertex;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}
int isQueueEmpty(struct Queue * q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}
void printPath(int parent[], int j, int m) {
    if (parent[j] == -1) {
        printf("(%d, %d) ", j / m, j % m);
        return;
    }
    printPath(parent, parent[j], m);
    printf("-> (%d, %d) ", j / m, j % m);
}
void BFS(struct Graph * graph, int start, int end, int m) {
    int * visited = (int *)malloc(graph->numVertices * sizeof(int));
    int * parent = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    struct Queue * q = createQueue();
    visited[start] = 1;
    enqueue(q, start);
    while (isQueueEmpty(q) == 0) {
        int curr = dequeue(q);
        if (curr == end) {
            break; 
        }
        struct AdjNode * temp = graph->array[curr].head;
        while (temp != NULL) {
            int adjVertex = temp->dest;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                parent[adjVertex] = curr;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    if (visited[end] == 1) {
        printf("Path found: \n");
        printPath(parent, end, m);
        printf("\n");
    } else {
        printf("No path found to the destination.\n");
    }
    free(visited);
    free(parent);
    free(q);
}
int isValid(int r, int c, int n, int m, int ** grid) {
    if (r >= 0) {
        if (r < n) {
            if (c >= 0) {
                if (c < m) {
                    if (grid[r][c] == 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
int simpleRand() {
    static int seed = 12345;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return seed;
}
int main() {
    int n = 4;
    int m = 4;
    printf("Enter number of rows (n): ");
    scanf("%d", &n);
    printf("Enter number of columns (m): ");
    scanf("%d", &m);
    if(n <= 0) n = 4;
    if(m <= 0) m = 4;
    int ** grid = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grid[i] = (int *)malloc(m * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int randNum = simpleRand() % 100;
            if (randNum < 75) {
                grid[i][j] = 0;
            } else {
                grid[i][j] = 1;
            }
        }
    }
    grid[0][0] = 0;
    grid[n-1][m-1] = 0;
    printf("\nMaze Grid (0 = Open, 1 = Blocked):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    struct Graph * graph = createGraph(n * m);
    int rowNum[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int colNum[] = {-1,  0,  1, -1, 1, -1, 0, 1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                int u = i * m + j;
                for (int k = 0; k < 8; k++) {
                    int r = i + rowNum[k];
                    int c = j + colNum[k];
                    if (isValid(r, c, n, m, grid) == 1) {
                        int v = r * m + c;
                        addEdge(graph, u, v);
                    }
                }
            }
        }
    }
    int startNode = 0;
    int endNode = (n - 1) * m + (m - 1);
    BFS(graph, startNode, endNode, m);
    for(int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
    return 0;
}

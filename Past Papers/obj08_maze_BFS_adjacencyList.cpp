/*
============================================================
OBJECTIVE #08 - MOUSE MAZE (BFS ON GRAPH, ADJACENCY LIST)
============================================================

PROBLEM SUMMARY:
  Write a program that uses an array A of size n×m
  (allocated dynamically; n and m are user inputs).

  A is treated as a MAZE:
  • A[i][j] = 0 → mouse CAN step on (i,j)
  • A[i][j] = 1 → mouse CANNOT step on (i,j)

  Mouse starts at A[0][0] and must reach A[n-1][m-1].
  Mouse can move in any of 8 directions
  (up, down, left, right, and 4 diagonals).

  Entries are filled RANDOMLY.

  SOLVE using BFS on a GRAPH represented as an ADJACENCY LIST.
  Output the indices of 2-D array cells covered in the path.

HOW WE MAP MAZE → GRAPH:
  Each cell (i,j) is a VERTEX.
  We assign it a unique vertex ID: id = i*m + j
  (so (0,0)=0, (0,1)=1, ..., (i,j)=i*m+j)

  An EDGE exists between (i,j) and (r,c) if:
  1. Both cells are 0 (passable)
  2. (r,c) is one of the 8 neighbors of (i,j)

  We store the graph as an ADJACENCY LIST using linked lists
  (matching the linked-list style of existing code).

BFS gives the SHORTEST PATH from (0,0) to (n-1,m-1).
We then trace back using parent[] array to find the path.
============================================================
*/

#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
using namespace std;

// ─── ADJACENCY LIST NODE ──────────────────────────────────────────────────────
// Each node in the adjacency list stores a neighbor vertex ID
struct AdjNode {
    int      vertexID;   // ID of the neighboring cell
    AdjNode* next;       // next neighbor in the list
};

// ─── GRAPH STRUCTURE ──────────────────────────────────────────────────────────
// Array of adjacency list heads (one per vertex)
struct Graph {
    int       numVertices;   // total cells = n * m
    AdjNode** adjList;       // array of adjacency list heads
};

// ─── QUEUE NODE (for BFS) ────────────────────────────────────────────────────
// Same style as existing dynamicQueue.cpp
struct QNode {
    int    vertexID;
    QNode* next;
};

QNode* qFront = NULL;
QNode* qRear  = NULL;

void enqueue(int v) {
    QNode* temp   = new QNode();
    temp->vertexID = v;
    temp->next     = NULL;
    if (qFront == NULL) {
        qFront = qRear = temp;
    } else {
        qRear->next = temp;
        qRear       = temp;
    }
}

int dequeue() {
    if (qFront == NULL) return -1;
    QNode* temp = qFront;
    int v       = temp->vertexID;
    qFront      = qFront->next;
    if (qFront == NULL) qRear = NULL;
    delete temp;
    return v;
}

bool queueEmpty() { return qFront == NULL; }

// ─── CREATE GRAPH ─────────────────────────────────────────────────────────────
Graph* createGraph(int totalVertices) {
    Graph* g        = new Graph();
    g->numVertices  = totalVertices;
    g->adjList      = new AdjNode*[totalVertices];
    for (int i = 0; i < totalVertices; i++) {
        g->adjList[i] = NULL;   // all adjacency lists start empty
    }
    return g;
}

// ─── ADD EDGE (undirected) ────────────────────────────────────────────────────
void addEdge(Graph* g, int u, int v) {
    // Add v to u's adjacency list
    AdjNode* newNode  = new AdjNode();
    newNode->vertexID = v;
    newNode->next     = g->adjList[u];   // prepend to list
    g->adjList[u]     = newNode;

    // Add u to v's adjacency list (undirected)
    AdjNode* newNode2  = new AdjNode();
    newNode2->vertexID = u;
    newNode2->next     = g->adjList[v];
    g->adjList[v]      = newNode2;
}

// ─── 8-DIRECTION ARRAYS ───────────────────────────────────────────────────────
// All 8 possible moves from any cell: N, NE, E, SE, S, SW, W, NW
int dr[] = {-1, -1,  0,  1,  1,  1,  0, -1};   // row    delta
int dc[] = { 0,  1,  1,  1,  0, -1, -1, -1};   // column delta

// ─── BUILD GRAPH FROM MAZE ────────────────────────────────────────────────────
// For every cell (i,j) with A[i][j]=0, add edges to reachable neighbors
Graph* buildGraph(int** A, int n, int m) {
    int totalCells = n * m;
    Graph* g = createGraph(totalCells);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (A[i][j] == 1) continue;   // blocked cell → no edges

            int u = i * m + j;   // vertex ID of (i,j)

            // Check all 8 neighbors
            for (int d = 0; d < 8; d++) {
                int r = i + dr[d];   // neighbor row
                int c = j + dc[d];   // neighbor column

                // Bounds check + passable check
                if (r < 0 || r >= n || c < 0 || c >= m) continue;
                if (A[r][c] == 1) continue;   // neighbor is blocked

                int v = r * m + c;   // vertex ID of (r,c)

                // Only add edge once (when u < v to avoid duplicates)
                if (u < v) {
                    addEdge(g, u, v);
                }
            }
        }
    }

    return g;
}

// ─── BFS: FIND SHORTEST PATH ─────────────────────────────────────────────────
// Returns true if a path exists from 'start' to 'end'.
// Fills parent[] array: parent[v] = the vertex we came from to reach v.
// parent[start] = -1 (no parent for start).
bool bfs(Graph* g, int start, int end, int* parent) {

    bool* visited = new bool[g->numVertices];
    for (int i = 0; i < g->numVertices; i++) {
        visited[i] = false;
        parent[i]  = -1;
    }

    visited[start] = true;
    enqueue(start);

    while (!queueEmpty()) {
        int u = dequeue();

        if (u == end) {
            delete[] visited;
            return true;   // found the destination!
        }

        // Visit all neighbors of u
        AdjNode* curr = g->adjList[u];
        while (curr != NULL) {
            int v = curr->vertexID;
            if (!visited[v]) {
                visited[v] = true;
                parent[v]  = u;     // record how we got to v
                enqueue(v);
            }
            curr = curr->next;
        }
    }

    delete[] visited;
    return false;   // no path found
}

// ─── PRINT PATH ───────────────────────────────────────────────────────────────
// Traces back from 'end' to 'start' using parent[] and prints (row,col)
void printPath(int* parent, int end, int m) {
    if (end == -1) return;              // base case: no parent means we're at start
    printPath(parent, parent[end], m); // recurse to print predecessors first

    if (parent[end] == -1 && end == -1) return;   // safety

    // Convert vertex ID back to (row, col)
    int row = end / m;
    int col = end % m;
    cout << "(" << row << "," << col << ")";

    if (parent[end] != -1 || end > 0) cout << " → ";   // separator
}

// Iterative path printing (cleaner for output)
void printPathIterative(int* parent, int start, int end, int m) {

    // Collect path from end back to start using parent[]
    int path[1000];
    int pathLen = 0;
    int curr    = end;

    while (curr != -1) {
        path[pathLen++] = curr;
        curr            = parent[curr];
    }

    // Print path in reverse (start → end)
    cout << "Path: ";
    for (int i = pathLen - 1; i >= 0; i--) {
        int row = path[i] / m;
        int col = path[i] % m;
        cout << "(" << row << "," << col << ")";
        if (i > 0) cout << " → ";
    }
    cout << endl;
    cout << "Total cells visited: " << pathLen << endl;
}

// ─── PRINT MAZE ───────────────────────────────────────────────────────────────
void printMaze(int** A, int n, int m) {
    cout << "Maze (0=open, 1=blocked):" << endl;
    cout << "     ";
    for (int j = 0; j < m; j++) cout << "c" << j << " ";
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "r" << i << ":  ";
        for (int j = 0; j < m; j++) {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }
}

// ─── FREE GRAPH ───────────────────────────────────────────────────────────────
void freeGraph(Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        AdjNode* curr = g->adjList[i];
        while (curr != NULL) {
            AdjNode* temp = curr;
            curr          = curr->next;
            delete temp;
        }
    }
    delete[] g->adjList;
    delete g;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    srand((unsigned)time(NULL));   // seed random number generator

    // --- Get maze dimensions from user ---
    int n, m;
    cout << "=== Mouse Maze Solver (BFS + Adjacency List) ===" << endl << endl;
    cout << "Enter maze dimensions (n rows, m cols): ";
    cin >> n >> m;

    // --- Dynamically allocate n×m maze array ---
    int** A = new int*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new int[m];
    }

    // --- Fill maze RANDOMLY (as required by problem) ---
    // Start (0,0) and End (n-1,m-1) MUST be 0 (passable)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = rand() % 2;   // 0 or 1 randomly
        }
    }
    A[0][0]         = 0;   // start must be passable
    A[n-1][m-1]     = 0;   // end must be passable

    // --- Print the maze ---
    cout << endl;
    printMaze(A, n, m);

    // --- Build graph from maze ---
    Graph* g = buildGraph(A, n, m);

    cout << endl << "Graph built with " << (n*m) << " vertices." << endl;

    // --- BFS to find path from (0,0) to (n-1,m-1) ---
    int startVertex = 0;               // (0,0) → ID 0
    int endVertex   = (n-1)*m + (m-1); // (n-1,m-1)

    int* parent = new int[n * m];

    cout << "Searching path from (0,0) to (" << (n-1) << "," << (m-1) << ")..." << endl;

    bool pathExists = bfs(g, startVertex, endVertex, parent);

    if (pathExists) {
        cout << "PATH FOUND!" << endl;
        printPathIterative(parent, startVertex, endVertex, m);
    } else {
        cout << "NO PATH EXISTS from (0,0) to ("
             << (n-1) << "," << (m-1) << ")." << endl;
        cout << "The mouse is trapped!" << endl;
    }

    // --- Print adjacency list (for small mazes) ---
    if (n * m <= 20) {
        cout << endl << "Adjacency List:" << endl;
        for (int i = 0; i < n * m; i++) {
            int row = i / m, col = i % m;
            cout << "(" << row << "," << col << ") [" << i << "]: ";
            AdjNode* curr = g->adjList[i];
            while (curr != NULL) {
                int r = curr->vertexID / m, c = curr->vertexID % m;
                cout << "(" << r << "," << c << ") ";
                curr = curr->next;
            }
            cout << endl;
        }
    }

    // --- Cleanup ---
    freeGraph(g);
    delete[] parent;
    for (int i = 0; i < n; i++) delete[] A[i];
    delete[] A;

    return 0;
}

/*
EXAMPLE (from image — 3×3 maze):

     c0 c1 c2
r0:  0  1  0
r1:  0  0  0
r2:  1  1  0

Vertices: (0,0)=0  (0,1)=1  (0,2)=2
          (1,0)=3  (1,1)=4  (1,2)=5
          (2,0)=6  (2,1)=7  (2,2)=8

Blocked: (0,1), (2,0), (2,1) → no edges for vertex 1, 6, 7

Open edges (from the image's graph):
  (0,0) ↔ (1,0), (0,0) ↔ (1,1)
  (0,2) ↔ (1,1), (0,2) ↔ (1,2)
  (1,0) ↔ (1,1), (1,1) ↔ (1,2), (1,1) ↔ (2,2)
  (1,2) ↔ (2,2)

BFS from 0 → 8:
  Queue: [0]
  Visit 0 → enqueue neighbors: 3(1,0), 4(1,1)
  Visit 3 → enqueue: 4(1,1) (already queued, skip)
  Visit 4 → enqueue: 2(0,2), 5(1,2), 8(2,2)
  Visit 2 → neighbors already visited
  Visit 5 → neighbors already visited
  Visit 8 → FOUND!  parent[8]=4(1,1)

Path trace: 8→4→0 (backwards)
Printed: (0,0) → (1,1) → (2,2) ✓

Time complexity:  O(V + E) where V=n*m, E=edges
Space complexity: O(V + E) for adjacency list + O(V) for BFS arrays
*/

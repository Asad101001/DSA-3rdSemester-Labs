/*
============================================================
OBJECTIVE #11 - MOUSE MAZE BFS (WITH EXAMPLE FROM IMAGE)
============================================================

PROBLEM SUMMARY (identical requirements to Obj 08):
  Write a program using array A of size n×m (dynamically allocated).
  A is treated as a maze:
  • A[i][j] = 0 → mouse CAN step on (i,j)
  • A[i][j] = 1 → mouse CANNOT step on (i,j)

  Mouse starts at A[0][0] and must reach A[n-1][m-1].
  Can move in any of the 8 directions.
  Entries filled RANDOMLY.

  Solve using BFS, mapping to a GRAPH with ADJACENCY LIST ONLY.
  Output: indices of 2-D array covered in the path.

DIFFERENCE from Objective 08:
  → This version includes the EXACT EXAMPLE from the image:
      3×3 maze:
         0  1  2
      0 [0][1][0]
      1 [0][0][0]
      2 [1][1][0]

  → Demonstrates that the graph formed matches the diagram in the image:
      Nodes: (0,0), (0,2), (1,0), (1,1), (1,2), (2,2)
      Blocked (no edges): (0,1), (2,0), (2,1)
      Graph edges match the star-pattern diagram shown

  → Also handles random mazes as per the problem requirement

SAME GRAPH/BFS APPROACH as Obj08, presented more verbosely.
============================================================
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ─── ADJACENCY LIST NODE ──────────────────────────────────────────────────────
struct AdjNode {
    int      vertex;   // neighbor vertex ID
    AdjNode* next;
};

// ─── GRAPH ────────────────────────────────────────────────────────────────────
struct Graph {
    int       V;          // number of vertices
    AdjNode** adj;        // adjacency lists (array of linked lists)
};

// ─── BFS QUEUE ────────────────────────────────────────────────────────────────
struct QNode {
    int    v;
    QNode* next;
};

QNode* qFront = NULL;
QNode* qRear  = NULL;

void enq(int v) {
    QNode* t = new QNode(); t->v = v; t->next = NULL;
    if (!qFront) { qFront = qRear = t; }
    else { qRear->next = t; qRear = t; }
}

int deq() {
    if (!qFront) return -1;
    QNode* t = qFront; int v = t->v;
    qFront = qFront->next;
    if (!qFront) qRear = NULL;
    delete t; return v;
}

bool qEmpty() { return qFront == NULL; }

// ─── CREATE AND BUILD GRAPH ───────────────────────────────────────────────────
Graph* createGraph(int V) {
    Graph* g = new Graph();
    g->V     = V;
    g->adj   = new AdjNode*[V];
    for (int i = 0; i < V; i++) g->adj[i] = NULL;
    return g;
}

// Add directed edge u → v to adjacency list
void addDirectedEdge(Graph* g, int u, int v) {
    AdjNode* n = new AdjNode();
    n->vertex  = v;
    n->next    = g->adj[u];
    g->adj[u]  = n;
}

// Add undirected edge (both directions)
void addEdge(Graph* g, int u, int v) {
    addDirectedEdge(g, u, v);
    addDirectedEdge(g, v, u);
}

// 8 directional deltas: N NE E SE S SW W NW
int DR[] = {-1,-1, 0, 1, 1, 1, 0,-1};
int DC[] = { 0, 1, 1, 1, 0,-1,-1,-1};

// Build graph: vertices = cells, edges = adjacent passable cells
Graph* buildGraph(int** A, int n, int m) {
    Graph* g = createGraph(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 1) continue;     // blocked → skip

            int u = i * m + j;              // vertex ID of (i,j)

            for (int d = 0; d < 8; d++) {
                int r = i + DR[d];
                int c = j + DC[d];
                if (r < 0 || r >= n || c < 0 || c >= m) continue;
                if (A[r][c] == 1) continue;

                int v = r * m + c;
                if (u < v) addEdge(g, u, v);  // add each edge once
            }
        }
    }
    return g;
}

// ─── BFS ─────────────────────────────────────────────────────────────────────
bool bfs(Graph* g, int src, int dst, int* parent) {
    bool* vis = new bool[g->V];
    for (int i = 0; i < g->V; i++) { vis[i] = false; parent[i] = -1; }

    vis[src] = true;
    enq(src);

    while (!qEmpty()) {
        int u = deq();
        if (u == dst) { delete[] vis; return true; }

        for (AdjNode* a = g->adj[u]; a; a = a->next) {
            if (!vis[a->vertex]) {
                vis[a->vertex]    = true;
                parent[a->vertex] = u;
                enq(a->vertex);
            }
        }
    }
    delete[] vis;
    return false;
}

// ─── PRINT PATH ───────────────────────────────────────────────────────────────
void printPath(int* parent, int src, int dst, int m) {
    // Collect path by tracing back from dst to src
    int path[500], len = 0, cur = dst;
    while (cur != -1) { path[len++] = cur; cur = parent[cur]; }

    cout << "Path (" << len << " cells): ";
    for (int i = len - 1; i >= 0; i--) {
        cout << "(" << path[i]/m << "," << path[i]%m << ")";
        if (i > 0) cout << " → ";
    }
    cout << endl;
}

// ─── PRINT MAZE ───────────────────────────────────────────────────────────────
void printMaze(int** A, int n, int m) {
    cout << "Maze:" << endl << "    ";
    for (int j = 0; j < m; j++) cout << " c" << j;
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << " r" << i << ": ";
        for (int j = 0; j < m; j++) {
            // Show S for start, E for end
            if (i==0 && j==0)     cout << " S";
            else if (i==n-1 && j==m-1) cout << " E";
            else                  cout << " " << A[i][j];
        }
        cout << endl;
    }
}

// ─── PRINT ADJACENCY LIST ─────────────────────────────────────────────────────
void printAdjList(Graph* g, int m) {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < g->V; i++) {
        if (g->adj[i] == NULL) continue;  // skip isolated/blocked vertices
        cout << "  (" << i/m << "," << i%m << "): ";
        for (AdjNode* a = g->adj[i]; a; a = a->next) {
            cout << "(" << a->vertex/m << "," << a->vertex%m << ") ";
        }
        cout << endl;
    }
}

// ─── FREE GRAPH ───────────────────────────────────────────────────────────────
void freeGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        AdjNode* c = g->adj[i];
        while (c) { AdjNode* t = c; c = c->next; delete t; }
    }
    delete[] g->adj;
    delete g;
}

// ─── SOLVE MAZE ───────────────────────────────────────────────────────────────
void solveMaze(int** A, int n, int m) {
    printMaze(A, n, m);

    Graph* g = buildGraph(A, n, m);

    cout << endl;
    printAdjList(g, m);

    int* parent = new int[n * m];
    int  src    = 0;
    int  dst    = (n-1)*m + (m-1);

    cout << endl << "Running BFS from S(0,0) to E(" << (n-1) << "," << (m-1) << ")..." << endl;

    if (bfs(g, src, dst, parent)) {
        cout << "PATH FOUND!" << endl;
        printPath(parent, src, dst, m);
    } else {
        cout << "NO PATH — mouse is trapped!" << endl;
    }

    freeGraph(g);
    delete[] parent;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Mouse Maze BFS with Adjacency List ===" << endl << endl;

    // ── DEMO 1: Exact example from the image ─────────────────────────────
    // 3×3 maze from Objective 11 image:
    //    c0 c1 c2
    // r0: 0  1  0
    // r1: 0  0  0
    // r2: 1  1  0
    cout << "══════════════════════════════════════" << endl;
    cout << "DEMO 1: Exact example from image" << endl;
    cout << "══════════════════════════════════════" << endl;

    int n1 = 3, m1 = 3;
    int** imageExample = new int*[n1];
    for (int i = 0; i < n1; i++) imageExample[i] = new int[m1];

    imageExample[0][0]=0; imageExample[0][1]=1; imageExample[0][2]=0;
    imageExample[1][0]=0; imageExample[1][1]=0; imageExample[1][2]=0;
    imageExample[2][0]=1; imageExample[2][1]=1; imageExample[2][2]=0;

    solveMaze(imageExample, n1, m1);

    for (int i = 0; i < n1; i++) delete[] imageExample[i];
    delete[] imageExample;

    // ── DEMO 2: Random maze ────────────────────────────────────────────────
    cout << endl << "══════════════════════════════════════" << endl;
    cout << "DEMO 2: Random maze" << endl;
    cout << "══════════════════════════════════════" << endl;

    srand((unsigned)time(NULL));

    int n2, m2;
    cout << "Enter dimensions (n m): ";
    cin >> n2 >> m2;

    int** A2 = new int*[n2];
    for (int i = 0; i < n2; i++) {
        A2[i] = new int[m2];
        for (int j = 0; j < m2; j++) A2[i][j] = rand() % 2;
    }
    A2[0][0]       = 0;   // start passable
    A2[n2-1][m2-1] = 0;   // end   passable

    solveMaze(A2, n2, m2);

    for (int i = 0; i < n2; i++) delete[] A2[i];
    delete[] A2;

    return 0;
}

/*
WALKTHROUGH — IMAGE EXAMPLE:

Maze:
     c0 c1 c2
  r0: S  1  0
  r1: 0  0  0
  r2: 1  1  E

Vertex IDs (id = row*3 + col):
  (0,0)=0  (0,1)=1  (0,2)=2
  (1,0)=3  (1,1)=4  (1,2)=5
  (2,0)=6  (2,1)=7  (2,2)=8

Blocked: (0,1)=1, (2,0)=6, (2,1)=7 → no edges added for these

Open cells: 0, 2, 3, 4, 5, 8

Edges (checking all 8 neighbors for open cells only):
  0(0,0) neighbors: (1,0)=3✓, (1,1)=4✓, (0,1)=1✗ → edges: 0-3, 0-4
  2(0,2) neighbors: (1,1)=4✓, (1,2)=5✓             → edges: 2-4, 2-5
  3(1,0) neighbors: (0,0)=0✓, (1,1)=4✓, (2,0)=6✗  → edges already added
  4(1,1) neighbors: all open around it              → 4-3, 4-5, 4-2, 4-0, 4-8(via 2,2)
  5(1,2) neighbors: (0,2)=2✓, (1,1)=4✓, (2,2)=8✓  → edges: 5-8
  8(2,2) neighbors: (1,1)=4✓, (1,2)=5✓             → already added

Adjacency List:
  (0,0): (1,1) (1,0)
  (0,2): (1,2) (1,1)
  (1,0): (1,1) (0,0)
  (1,1): (2,2) (1,2) (0,2) (1,0) (0,0)
  (1,2): (2,2) (1,1) (0,2)
  (2,2): (1,2) (1,1)

BFS from 0 to 8:
  Enqueue: 0
  Visit 0 → neighbors: 3,4  → enqueue 3,4; parent[3]=0, parent[4]=0
  Visit 3 → neighbors: 4(visited), 0(visited)
  Visit 4 → neighbors: 8,5,2,3(v),0(v) → enqueue 8,5,2; parent[8]=4
  Visit 8 → THIS IS THE DESTINATION!

Path: trace parent[]
  8 → parent[8]=4 → parent[4]=0 → parent[0]=-1 (start)
  Printed: (0,0) → (1,1) → (2,2) ✓

This matches the graph shown in the image!
*/

/*
============================================================
OBJECTIVE #02 - HEAP-ORDER BINARY TREE + MIRROR IMAGE
============================================================

PROBLEM SUMMARY:
  Build a Binary Tree by inserting elements the same way
  nodes are inserted in a heap (i.e., level by level,
  left to right — NOT a BST ordering rule).

  Each node holds a FLOAT value.

  Given a pointer to the root, find its MIRROR IMAGE:
    → The mirror is a new tree where left and right children
      are swapped at every node.
    → "left child of root is now the right child and
       right is now the left."

EXAMPLE (from image):
  Input Tree:
            89
           /  \
         122   12
         /    /  \
        75   99   68

  Mirror Image:
            89
           /  \
          12  122
         /  \     \
        68  99     75

APPROACH:
  - Use a Queue (BFS order) to insert nodes level-by-level
    (exactly like a min/max heap positions elements)
  - Build the mirror by recursively swapping children
  - Display both trees using level-order (BFS) traversal
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
// Each node holds a float (as required) + left/right children
struct Node {
    float data;
    Node* left;
    Node* right;
};

// ─── QUEUE FOR LEVEL-ORDER INSERTION ─────────────────────────────────────────
// We need a simple queue of Node* pointers to track
// which nodes still need children assigned.
// Re-uses the same linked-list queue pattern from dynamicQueue.cpp
struct QNode {
    Node*  data;    // stores a pointer to a tree Node
    QNode* next;
};

QNode* qFront = NULL;   // front of insertion queue
QNode* qRear  = NULL;   // rear  of insertion queue

void enqueue(Node* treeNode) {
    QNode* temp = new QNode();
    temp->data  = treeNode;
    temp->next  = NULL;
    if (qFront == NULL) {
        qFront = qRear = temp;
    } else {
        qRear->next = temp;
        qRear       = temp;
    }
}

Node* dequeue() {
    if (qFront == NULL) return NULL;   // queue empty
    QNode* temp  = qFront;
    Node*  value = temp->data;
    qFront       = qFront->next;
    if (qFront == NULL) qRear = NULL;  // queue is now empty
    delete temp;
    return value;
}

bool queueEmpty() { return qFront == NULL; }

// ─── TREE ROOT ───────────────────────────────────────────────────────────────
Node* root = NULL;

// ─── HEAP-STYLE INSERT (Level-order / BFS insertion) ─────────────────────────
// Uses the same queue that held "next available parent".
// When a node is added:
//   1. If it has no left child  → set as left child
//   2. Else if no right child   → set as right child
//   3. If now has both children → remove from queue (no more slots)
//   4. Add the new node to queue (it will eventually accept children)
Node* insertHeapStyle(float val) {

    // Create the new node
    Node* newNode   = new Node();
    newNode->data   = val;
    newNode->left   = NULL;
    newNode->right  = NULL;

    // CASE: tree is empty → this becomes the root
    if (root == NULL) {
        root = newNode;
        enqueue(root);    // root is now waiting for children
        return newNode;
    }

    // CASE: tree not empty → peek at front of queue
    // Front of queue = leftmost node that still has an open child slot
    Node* parent = qFront->data;   // don't dequeue yet

    if (parent->left == NULL) {
        // Fill left child first
        parent->left = newNode;
    } else {
        // Fill right child
        parent->right = newNode;
        // Parent is now full (both slots taken) → dequeue it
        dequeue();
    }

    // The new node is ready to accept its own children later
    enqueue(newNode);

    return newNode;
}

// ─── BUILD MIRROR (Recursive) ────────────────────────────────────────────────
// Creates a completely NEW tree that is the mirror image.
// At each node: swap left and right children.
Node* buildMirror(Node* curr) {
    if (curr == NULL) return NULL;   // base case: nothing to mirror

    // Create a new mirrored node with same data
    Node* mirrorNode   = new Node();
    mirrorNode->data   = curr->data;

    // KEY SWAP: left of mirror ← right of original
    //           right of mirror ← left of original
    mirrorNode->left   = buildMirror(curr->right);   // swap!
    mirrorNode->right  = buildMirror(curr->left);    // swap!

    return mirrorNode;
}

// ─── LEVEL-ORDER DISPLAY (BFS) ───────────────────────────────────────────────
// Prints tree level by level (like reading a heap array)
// Uses a second temporary queue — doesn't disturb the insertion queue
void displayLevelOrder(Node* treeRoot) {

    if (treeRoot == NULL) {
        cout << "(empty tree)" << endl;
        return;
    }

    // Temporary display queue (local, won't touch global qFront/qRear)
    // We'll use a simple array-based approach for clarity
    Node* displayQueue[100];   // simple array queue
    int   dFront = 0, dRear = 0;

    displayQueue[dRear++] = treeRoot;   // enqueue root

    int level = 1;
    cout << "Level " << level << ": ";

    // We track how many nodes are on the current level
    int currentLevelCount = 1;
    int nextLevelCount    = 0;

    while (dFront < dRear) {
        Node* curr = displayQueue[dFront++];   // dequeue
        cout << curr->data << "  ";
        currentLevelCount--;

        // Enqueue children
        if (curr->left  != NULL) { displayQueue[dRear++] = curr->left;  nextLevelCount++; }
        if (curr->right != NULL) { displayQueue[dRear++] = curr->right; nextLevelCount++; }

        // When current level is exhausted, move to next
        if (currentLevelCount == 0 && dFront < dRear) {
            level++;
            cout << endl << "Level " << level << ": ";
            currentLevelCount = nextLevelCount;
            nextLevelCount    = 0;
        }
    }
    cout << endl;
}

// ─── IN-ORDER DISPLAY ────────────────────────────────────────────────────────
void inOrder(Node* curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    cout << curr->data << "  ";
    inOrder(curr->right);
}

// ─── CLEANUP MEMORY ──────────────────────────────────────────────────────────
void freeTree(Node* curr) {
    if (curr == NULL) return;
    freeTree(curr->left);
    freeTree(curr->right);
    delete curr;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    // --- Part 1: Build heap-order tree ---
    // Values from the image: 89, 122, 12, 75, 99, 68
    // Inserted left-to-right, level by level (heap order)
    float values[] = {89, 122, 12, 75, 99, 68};
    int   n        = sizeof(values) / sizeof(values[0]);

    cout << "=== Inserting in Heap Order ===" << endl;
    for (int i = 0; i < n; i++) {
        insertHeapStyle(values[i]);
        cout << "Inserted: " << values[i] << endl;
    }

    cout << endl << "=== Input Tree (Level-Order) ===" << endl;
    displayLevelOrder(root);

    cout << endl << "=== Input Tree (InOrder) ===" << endl;
    inOrder(root);
    cout << endl;

    // --- Part 2: Build mirror image ---
    // Reset the display queue pointers (global queue no longer needed)
    // (The insertion queue may still have entries, but we are done inserting)
    Node* mirrorRoot = buildMirror(root);

    cout << endl << "=== Mirror Image (Level-Order) ===" << endl;
    displayLevelOrder(mirrorRoot);

    cout << endl << "=== Mirror Image (InOrder) ===" << endl;
    inOrder(mirrorRoot);
    cout << endl;

    // --- Verify: InOrder of mirror should be reverse of original's InOrder ---
    cout << endl << "Note: InOrder of mirror is the reverse of InOrder of original." << endl;

    // Cleanup
    freeTree(root);
    freeTree(mirrorRoot);

    return 0;
}

/*
HOW IT WORKS — WALKTHROUGH:

HEAP-ORDER INSERTION (values: 89, 122, 12, 75, 99, 68):

  Step 1: Insert 89 → root
          Queue: [89]
          Tree:   89

  Step 2: Insert 122 → left child of 89
          Queue: [89, 122]
          Tree:   89
                 /
               122

  Step 3: Insert 12 → right child of 89 (parent now full → dequeue 89)
          Queue: [122, 12]
          Tree:   89
                 /  \
               122   12

  Step 4: Insert 75 → left child of 122
          Queue: [122, 12, 75]
          Tree:   89
                 /  \
               122   12
               /
              75

  Step 5: Insert 99 → right child of 122 (122 now full → dequeued)
          Queue: [12, 75, 99]
          Tree:   89
                 /  \
               122   12
               / \
              75  99

  Step 6: Insert 68 → left child of 12
          Queue: [12, 75, 99, 68]
          Tree:   89
                 /  \
               122   12
               / \   /
              75  99 68

MIRROR (swap left ↔ right at every node recursively):

          89
         /  \
        12  122
       /    / \
      68   99  75
*/

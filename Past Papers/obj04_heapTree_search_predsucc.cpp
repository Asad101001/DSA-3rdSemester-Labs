/*
============================================================
OBJECTIVE #04 - HEAP-ORDER BINARY TREE: SEARCH, PRED/SUCC, COUNT
============================================================

PROBLEM SUMMARY:
  Build a Binary Tree by inserting elements in the same manner
  as nodes are inserted in the heap (i.e., from LEFT to RIGHT,
  level by level). Each node holds a FLOAT value.

  Given a pointer to the root of the binary tree:
  1. Given element x, search if x is present in the tree or not
  2. Find the PREDECESSORS and SUCCESSORS of x (if x exists)
  3. Find the TOTAL NUMBER OF NODES in the tree

  Example from image: Elements = {12, 24, 19, 26, 96}

NOTE ON PREDECESSOR/SUCCESSOR:
  In a HEAP-ORDER tree (not a BST), predecessor and successor
  are defined by LEVEL-ORDER (BFS) traversal position:
  → Predecessor = node that appears BEFORE x in level-order
  → Successor   = node that appears AFTER  x in level-order
  This is the natural "left neighbor / right neighbor" when
  the tree is read as a heap array.
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
struct Node {
    float data;
    Node* left;
    Node* right;
};

// ─── QUEUE (for BFS / heap-style operations) ─────────────────────────────────
// Same linked-list queue pattern as dynamicQueue.cpp
struct QNode {
    Node*  data;
    QNode* next;
};

// ─── GLOBAL TREE ROOT ─────────────────────────────────────────────────────────
Node* root = NULL;

// ─── SIMPLE QUEUE HELPERS ─────────────────────────────────────────────────────
// Using an array-based approach for the insertion queue (clean and simple)
// MAX_SIZE covers any reasonable tree in this problem
const int MAX_SIZE = 200;

Node* insertionQueue[MAX_SIZE];   // queue for heap-style insertion
int   iqFront = 0;                // front index
int   iqRear  = 0;                // rear index (next empty slot)

bool iq_empty() { return iqFront == iqRear; }
void iq_push(Node* n) { insertionQueue[iqRear++] = n; }
Node* iq_front() { return insertionQueue[iqFront]; }
void iq_pop()  { iqFront++; }

// ─── HEAP-STYLE INSERT ────────────────────────────────────────────────────────
// Inserts node at the next available position (left to right, level by level).
// Same logic as obj02 — maintained separately for completeness.
void insert(float val) {
    Node* newNode   = new Node();
    newNode->data   = val;
    newNode->left   = NULL;
    newNode->right  = NULL;

    if (root == NULL) {
        root = newNode;
        iq_push(root);
        return;
    }

    // The front of the insertion queue = leftmost node awaiting a child
    Node* parent = iq_front();

    if (parent->left == NULL) {
        parent->left = newNode;           // fill left slot
    } else {
        parent->right = newNode;          // fill right slot
        iq_pop();                         // parent is now full → remove from queue
    }

    iq_push(newNode);   // new node will eventually need children
}

// ─── OPERATION 3: COUNT TOTAL NODES ──────────────────────────────────────────
// Recursive: count = 1 (current) + count(left) + count(right)
int countNodes(Node* curr) {
    if (curr == NULL) return 0;
    return 1 + countNodes(curr->left) + countNodes(curr->right);
}

// ─── LEVEL-ORDER ARRAY BUILDER ────────────────────────────────────────────────
// Fills 'arr' with all node pointers in BFS (level-order) sequence.
// Returns the number of nodes placed into 'arr'.
// We need this to implement predecessor/successor in BFS order.
int buildLevelOrderArray(Node* treeRoot, Node* arr[], int maxSize) {
    if (treeRoot == NULL) return 0;

    // Simple BFS using a local array-based queue
    Node* bfsQueue[MAX_SIZE];
    int   bFront = 0, bRear = 0;
    bfsQueue[bRear++] = treeRoot;

    int count = 0;

    while (bFront < bRear && count < maxSize) {
        Node* curr     = bfsQueue[bFront++];
        arr[count++]   = curr;                 // store in level-order array

        if (curr->left  != NULL) bfsQueue[bRear++] = curr->left;
        if (curr->right != NULL) bfsQueue[bRear++] = curr->right;
    }

    return count;
}

// ─── OPERATION 1: SEARCH ─────────────────────────────────────────────────────
// Searches the entire tree (BFS) for value x.
// Returns the Node* if found, NULL if not found.
// Also reports the level-order position (1-based index) of the found node.
Node* searchNode(float x, int* position) {
    Node* levelOrder[MAX_SIZE];
    int   total = buildLevelOrderArray(root, levelOrder, MAX_SIZE);

    for (int i = 0; i < total; i++) {
        if (levelOrder[i]->data == x) {
            *position = i + 1;   // 1-based position
            return levelOrder[i];
        }
    }

    *position = -1;
    return NULL;   // not found
}

// ─── OPERATION 2: PREDECESSOR AND SUCCESSOR ──────────────────────────────────
// In level-order (BFS) traversal:
//   Predecessor = node at position (pos-1) in the BFS array
//   Successor   = node at position (pos+1) in the BFS array
// If x is at the very first position → no predecessor
// If x is at the very last  position → no successor
void findPredecessorSuccessor(float x) {

    Node* levelOrder[MAX_SIZE];
    int   total = buildLevelOrderArray(root, levelOrder, MAX_SIZE);

    // Find position of x in BFS array
    int foundAt = -1;
    for (int i = 0; i < total; i++) {
        if (levelOrder[i]->data == x) {
            foundAt = i;
            break;
        }
    }

    // Element not found in tree
    if (foundAt == -1) {
        cout << x << " not found in tree. Cannot find predecessor/successor." << endl;
        return;
    }

    // Predecessor
    cout << "--- Predecessor of " << x << " ---" << endl;
    if (foundAt == 0) {
        cout << "No predecessor (x is the first node in level-order / root)." << endl;
    } else {
        cout << "Predecessor = " << levelOrder[foundAt - 1]->data
             << "  (level-order position " << foundAt << ")" << endl;
    }

    // Successor
    cout << "--- Successor of " << x << " ---" << endl;
    if (foundAt == total - 1) {
        cout << "No successor (x is the last node in level-order)." << endl;
    } else {
        cout << "Successor = " << levelOrder[foundAt + 1]->data
             << "  (level-order position " << (foundAt + 2) << ")" << endl;
    }
}

// ─── DISPLAY TREE (Level-order) ───────────────────────────────────────────────
void displayLevelOrder() {
    if (root == NULL) {
        cout << "(tree is empty)" << endl;
        return;
    }

    Node* levelOrder[MAX_SIZE];
    int   total = buildLevelOrderArray(root, levelOrder, MAX_SIZE);

    int level = 1;
    int nodesOnThisLevel = 1;         // root level has 1 node
    int nodesPrinted     = 0;

    cout << "Level " << level << ": ";
    for (int i = 0; i < total; i++) {
        cout << levelOrder[i]->data << "  ";
        nodesPrinted++;

        if (nodesPrinted == nodesOnThisLevel && i < total - 1) {
            // Move to next level
            level++;
            cout << endl << "Level " << level << ": ";
            nodesOnThisLevel *= 2;    // each level can have double the nodes
            nodesPrinted      = 0;
        }
    }
    cout << endl;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Heap-Order Binary Tree: Search, Pred/Succ, Count ===" << endl << endl;

    // --- Build the tree from image: {12, 24, 19, 26, 96} ---
    float values[] = {12, 24, 19, 26, 96};
    int   n        = sizeof(values) / sizeof(values[0]);

    cout << "--- Inserting Elements (Heap / Level-Order) ---" << endl;
    for (int i = 0; i < n; i++) {
        insert(values[i]);
        cout << "Inserted: " << values[i] << endl;
    }

    /*
       Resulting tree (heap-order insertion):
              12
             /  \
           24    19
          /  \
        26   96
    */

    cout << endl << "--- Tree (Level-Order Display) ---" << endl;
    displayLevelOrder();

    // --- Operation 3: Total node count ---
    cout << endl << "--- Operation 3: Total Node Count ---" << endl;
    int total = countNodes(root);
    cout << "Total nodes in tree: " << total << endl;

    // --- Operation 1: Search ---
    cout << endl << "--- Operation 1: Search ---" << endl;

    float searchTargets[] = {19, 26, 99};   // 99 doesn't exist
    for (int i = 0; i < 3; i++) {
        float x = searchTargets[i];
        int   pos;
        Node* found = searchNode(x, &pos);

        if (found != NULL) {
            cout << x << " FOUND at level-order position " << pos << endl;
        } else {
            cout << x << " NOT FOUND in the tree." << endl;
        }
    }

    // --- Operation 2: Predecessor and Successor ---
    cout << endl << "--- Operation 2: Predecessor and Successor ---" << endl;

    float psTargets[] = {12, 24, 19, 26, 96};
    for (int i = 0; i < 5; i++) {
        cout << endl << "[x = " << psTargets[i] << "]" << endl;
        findPredecessorSuccessor(psTargets[i]);
    }

    // --- Interactive menu ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice;
    float val;

    do {
        cout << "\n1. Insert\n2. Display Tree\n3. Search\n4. Predecessor/Successor\n5. Count Nodes\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                insert(val);
                cout << "Inserted " << val << endl;
                break;

            case 2:
                displayLevelOrder();
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                {
                    int pos;
                    Node* f = searchNode(val, &pos);
                    if (f) cout << val << " found at level-order position " << pos << endl;
                    else   cout << val << " not found." << endl;
                }
                break;

            case 4:
                cout << "Enter value: ";
                cin >> val;
                findPredecessorSuccessor(val);
                break;

            case 5:
                cout << "Total nodes: " << countNodes(root) << endl;
                break;

            case 6:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 6);

    return 0;
}

/*
EXAMPLE WALKTHROUGH (with values {12, 24, 19, 26, 96}):

TREE STRUCTURE (heap/level-order insertion):
       12         ← Level 1
      /  \
    24    19      ← Level 2
   /  \
  26   96         ← Level 3

LEVEL-ORDER ARRAY: [12, 24, 19, 26, 96]
                    pos: 1   2   3   4   5

SEARCH(19):
  Scan array → found at position 3. ✓

PREDECESSOR/SUCCESSOR of 19:
  Position 3 in array
  Predecessor = array[2] = 24
  Successor   = array[4] = 26

PREDECESSOR/SUCCESSOR of 12:
  Position 1 → no predecessor (it's the root)
  Successor = array[2] = 24

COUNT NODES:
  countNodes(12)
  = 1 + countNodes(24) + countNodes(19)
  = 1 + (1 + countNodes(26) + countNodes(96)) + (1 + 0 + 0)
  = 1 + (1 + 1 + 1) + 1
  = 5  ✓
*/

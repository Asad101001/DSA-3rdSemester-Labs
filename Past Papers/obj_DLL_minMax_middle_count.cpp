/*
============================================================
OBJECTIVE - DOUBLY LINKED LIST OPERATIONS
============================================================

PROBLEM SUMMARY (from New Text Document (2).txt):
  Using a DOUBLY LINKED LIST:
  1. Insert Node
  2. Delete Node
  3. Print Nodes
  4. Find MIN and MOVE it to the FIRST node (head)
  5. Find MAX and MOVE it to the LAST node (tail)
  6. Find TOTAL NUMBER of nodes
  7. Find the MIDDLE VALUE of the linked list

APPROACH:
  - Min/Max move: don't create a new node, UNLINK the min/max node
    and relink it at the front/back (preserving original data)
  - Middle value: use the "slow-fast pointer" technique
    (slow moves 1 step, fast moves 2 steps → when fast reaches end,
     slow is at middle)
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
struct Node {
    int   data;
    Node* next;
    Node* prev;
};

// ─── GLOBAL HEAD ─────────────────────────────────────────────────────────────
Node* head = NULL;

// ─── HELPER: CREATE NODE ─────────────────────────────────────────────────────
Node* createNode(int val) {
    Node* temp  = new Node();
    temp->data  = val;
    temp->next  = NULL;
    temp->prev  = NULL;
    return temp;
}

// ─── OPERATION 1: INSERT (at end) ────────────────────────────────────────────
// Same pattern as existing doublyLinkedList.cpp but with full prev wiring
void insertNode(int val) {
    Node* newNode = createNode(val);

    if (head == NULL) {
        head = newNode;
        return;
    }

    // Walk to tail
    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;

    curr->next    = newNode;   // tail → new node
    newNode->prev = curr;      // new node ← tail
}

// ─── OPERATION 2: DELETE NODE ────────────────────────────────────────────────
// Deletes the first node with value 'val'
void deleteNode(int val) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* curr = head;

    // Find the node to delete
    while (curr != NULL && curr->data != val) {
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << val << " not found in list." << endl;
        return;
    }

    // Unlink the node
    if (curr->prev != NULL) curr->prev->next = curr->next;  // bypass curr (forward)
    else                    head              = curr->next;  // curr was head → update head

    if (curr->next != NULL) curr->next->prev = curr->prev;  // bypass curr (backward)

    delete curr;
    cout << val << " deleted." << endl;
}

// ─── OPERATION 3: PRINT ──────────────────────────────────────────────────────
void printList() {
    if (head == NULL) {
        cout << "(empty list)" << endl;
        return;
    }
    Node* curr = head;
    cout << "NULL ← ";
    while (curr != NULL) {
        cout << "[" << curr->data << "]";
        if (curr->next != NULL) cout << " ↔ ";
        curr = curr->next;
    }
    cout << " → NULL" << endl;
}

// ─── HELPER: UNLINK A NODE (without deleting it) ─────────────────────────────
// Removes 'node' from its current position in the list,
// fixing up prev/next links. Does NOT free memory.
void unlinkNode(Node* node) {
    if (node->prev != NULL) node->prev->next = node->next;
    else                    head              = node->next;   // node was head

    if (node->next != NULL) node->next->prev = node->prev;

    // Detach the node's own pointers so it's a clean standalone node
    node->next = NULL;
    node->prev = NULL;
}

// ─── HELPER: PREPEND (insert at front) ────────────────────────────────────────
void prependNode(Node* node) {
    node->next = head;
    node->prev = NULL;
    if (head != NULL) head->prev = node;
    head = node;
}

// ─── HELPER: APPEND (insert at back) ─────────────────────────────────────────
void appendNode(Node* node) {
    node->next = NULL;
    if (head == NULL) {
        node->prev = NULL;
        head       = node;
        return;
    }
    // Walk to tail
    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = node;
    node->prev = curr;
}

// ─── OPERATION 4: FIND MIN AND MOVE TO FIRST ─────────────────────────────────
// Finds the node with the minimum data value.
// Unlinks it from its current position.
// Prepends it (makes it the new head).
void moveMinToFirst() {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    // Find the min node
    Node* minNode = head;
    Node* curr    = head->next;
    while (curr != NULL) {
        if (curr->data < minNode->data) minNode = curr;
        curr = curr->next;
    }

    cout << "Min value = " << minNode->data << endl;

    // If min is already at head → nothing to do
    if (minNode == head) {
        cout << "Min already at first position." << endl;
        return;
    }

    // Unlink min from its current position
    unlinkNode(minNode);

    // Prepend it to the front
    prependNode(minNode);

    cout << "Min moved to first. List: ";
    printList();
}

// ─── OPERATION 5: FIND MAX AND MOVE TO LAST ──────────────────────────────────
// Same idea as above but for maximum value, moved to tail.
void moveMaxToLast() {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    // Find the max node
    Node* maxNode = head;
    Node* curr    = head->next;
    while (curr != NULL) {
        if (curr->data > maxNode->data) maxNode = curr;
        curr = curr->next;
    }

    cout << "Max value = " << maxNode->data << endl;

    // Walk to tail to check if max is already at tail
    Node* tail = head;
    while (tail->next != NULL) tail = tail->next;

    if (maxNode == tail) {
        cout << "Max already at last position." << endl;
        return;
    }

    // Unlink max from current position
    unlinkNode(maxNode);

    // Append to tail
    appendNode(maxNode);

    cout << "Max moved to last. List: ";
    printList();
}

// ─── OPERATION 6: TOTAL NUMBER OF NODES ──────────────────────────────────────
int countNodes() {
    int count = 0;
    Node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

// ─── OPERATION 7: FIND MIDDLE VALUE ──────────────────────────────────────────
// Uses the SLOW-FAST POINTER (Floyd's algorithm) technique:
//   slow moves 1 step at a time
//   fast moves 2 steps at a time
//   When fast reaches the end, slow is at the middle
//
// For an even-length list, this returns the FIRST of the two middle nodes.
void findMiddle() {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* slow = head;   // moves 1 step per iteration
    Node* fast = head;   // moves 2 steps per iteration

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;         // advance slow by 1
        fast = fast->next->next;   // advance fast by 2
    }

    // When loop ends: slow is at the middle node
    cout << "Middle value: " << slow->data << endl;
    cout << "(List has " << countNodes() << " nodes)" << endl;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Doubly Linked List: Min/Max Move, Count, Middle ===" << endl << endl;

    // --- Build initial list ---
    cout << "--- Inserting Nodes ---" << endl;
    int values[] = {35, 10, 78, 22, 5, 91, 47, 63, 18};
    int n        = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) insertNode(values[i]);

    cout << "List: ";
    printList();

    // --- Operation 6: Total node count ---
    cout << endl << "--- Operation 6: Total Nodes ---" << endl;
    cout << "Total nodes: " << countNodes() << endl;

    // --- Operation 7: Middle ---
    cout << endl << "--- Operation 7: Middle Value ---" << endl;
    findMiddle();

    // --- Operation 4: Min to first ---
    cout << endl << "--- Operation 4: Min to First ---" << endl;
    moveMinToFirst();

    // --- Operation 5: Max to last ---
    cout << endl << "--- Operation 5: Max to Last ---" << endl;
    moveMaxToLast();

    // --- Operation 2: Delete ---
    cout << endl << "--- Operation 2: Delete ---" << endl;
    deleteNode(47);
    printList();
    deleteNode(999);   // not in list

    // --- Interactive Menu ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice, val;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Print\n4. Min to First\n5. Max to Last\n6. Count Nodes\n7. Find Middle\n8. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                insertNode(val);
                printList();
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                deleteNode(val);
                break;
            case 3:
                printList();
                break;
            case 4:
                moveMinToFirst();
                break;
            case 5:
                moveMaxToLast();
                break;
            case 6:
                cout << "Total nodes: " << countNodes() << endl;
                break;
            case 7:
                findMiddle();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 8);

    return 0;
}

/*
MIDDLE VALUE — SLOW-FAST POINTER EXPLAINED:

List: [35] ↔ [10] ↔ [78] ↔ [22] ↔ [5] ↔ [91] ↔ [47] ↔ [63] ↔ [18]
       1       2       3       4      5      6       7       8       9 nodes

Step 1: slow=35, fast=35
Step 2: slow=10, fast=78  (slow+1, fast+2)
Step 3: slow=78, fast=5   (slow+1, fast+2)
Step 4: slow=22, fast=47  (slow+1, fast+2)
Step 5: slow=5,  fast=18  (slow+1, fast+2)
Step 6: slow=91, fast=NULL (fast->next == NULL → stop)

Middle = 91? No wait — let me recount:
9 nodes → middle should be position 5 = 5th node = [5]

Actually: fast reaches NULL when slow = node 5 for ODD-length lists.
  After step 4: slow=5th node, fast=9th node
  fast->next = NULL → loop stops
  Middle = 5 ✓

MIN-TO-FIRST:
  Min = 5 (at position 5)
  Unlink 5: [35]↔[10]↔[78]↔[22]↔[91]↔[47]↔[63]↔[18]
  Prepend 5: [5]↔[35]↔[10]↔[78]↔[22]↔[91]↔[47]↔[63]↔[18] ✓

MAX-TO-LAST:
  Max = 91 (at some position)
  Unlink, append → ends up at tail ✓
*/

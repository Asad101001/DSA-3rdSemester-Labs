/*
============================================================
OBJECTIVE #09 - DOUBLY LINKED LIST: REVERSE BY SWAPPING POINTERS
============================================================

PROBLEM SUMMARY (from image 9):
  Implement a DOUBLY LINKED LIST with:
  1. INSERT an element
  2. PRINT list
  3. REVERSE: When user calls reverse, the WHOLE LIST is reversed
     by CHANGING POINTERS (prev ↔ next swapped in each node,
     and start/head now points to the last node).
     → The list is UPDATED (not a copy — the original list is modified)
  4. FIND MINIMUM element
  5. FIND MAXIMUM element

KEY DISTINCTION from Objective 6's copy-reverse:
  → This reversal MODIFIES the existing list IN-PLACE
  → It swaps prev and next pointers of EVERY node
  → After reversal, the head pointer points to what was the tail
  → "remember now list is updated" — subsequent operations
     (min, max, insert) work on the reversed/updated list
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

// ─── INSERT (at end) ──────────────────────────────────────────────────────────
// Same as existing doublyLinkedList.cpp, appends to tail
void insert(int val) {
    Node* temp   = new Node();
    temp->data   = val;
    temp->next   = NULL;
    temp->prev   = NULL;

    if (head == NULL) {
        head = temp;
        return;
    }

    // Walk to tail
    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;

    curr->next = temp;   // tail → new node
    temp->prev = curr;   // new node ← tail
}

// ─── PRINT LIST ──────────────────────────────────────────────────────────────
void printList() {
    if (head == NULL) {
        cout << "(empty list)" << endl;
        return;
    }

    cout << "NULL ← ";
    Node* curr = head;
    while (curr != NULL) {
        cout << "[" << curr->data << "]";
        if (curr->next != NULL) cout << " ↔ ";
        curr = curr->next;
    }
    cout << " → NULL" << endl;
}

// ─── REVERSE (IN-PLACE, BY SWAPPING POINTERS) ────────────────────────────────
// Algorithm:
//   Walk through every node.
//   For each node: swap its next and prev pointers.
//   After all nodes are processed, the old tail (curr = last node reached)
//   has prev = its old prev (now pointing to the next node in original order),
//   and next = NULL (it was the tail). So after swapping, the old tail's
//   "next" (which is now its "prev" field) points to the rest.
//
//   We then update head to point to the OLD TAIL (new head).
//
//   Traversal: we walk using the ORIGINAL 'next' pointer BEFORE swapping it.
//   So we save curr->next, do the swap, then move to saved pointer.
void reverseList() {
    if (head == NULL || head->next == NULL) {
        cout << "List has 0 or 1 element — nothing to reverse." << endl;
        return;
    }

    Node* curr    = head;
    Node* newHead = NULL;   // will end up pointing to old tail

    while (curr != NULL) {
        // Save the next pointer BEFORE we overwrite it
        Node* nextNode = curr->next;

        // SWAP next and prev for this node
        // (what was next becomes prev, what was prev becomes next)
        curr->next = curr->prev;   // next ← old prev
        curr->prev = nextNode;     // prev ← old next

        // The node that has prev=nextNode and next=old-prev is now "reversed"
        // The last node we process (where nextNode==NULL) is the new head
        newHead = curr;

        // Move to the next node in the ORIGINAL direction
        // (which is stored in 'nextNode', the saved value)
        curr = nextNode;
    }

    // Update head to the old tail (which is now the first node)
    head = newHead;

    cout << "List reversed (pointers swapped, head updated)." << endl;
}

// ─── FIND MINIMUM ────────────────────────────────────────────────────────────
void findMin() {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    int   minVal  = head->data;
    Node* curr    = head->next;
    while (curr != NULL) {
        if (curr->data < minVal) minVal = curr->data;
        curr = curr->next;
    }

    cout << "Minimum element: " << minVal << endl;
}

// ─── FIND MAXIMUM ────────────────────────────────────────────────────────────
void findMax() {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    int   maxVal  = head->data;
    Node* curr    = head->next;
    while (curr != NULL) {
        if (curr->data > maxVal) maxVal = curr->data;
        curr = curr->next;
    }

    cout << "Maximum element: " << maxVal << endl;
}

// ─── VALIDATE BIDIRECTIONAL LINKS ────────────────────────────────────────────
// After reversal, verify all next/prev links are consistent
bool validateLinks() {
    if (head == NULL) return true;

    Node* curr = head;
    while (curr->next != NULL) {
        if (curr->next->prev != curr) return false;   // prev link broken
        curr = curr->next;
    }

    // Walk backward
    while (curr->prev != NULL) {
        if (curr->prev->next != curr) return false;   // next link broken
        curr = curr->prev;
    }

    return (curr == head);   // backward walk should land on head
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== DLL: Reverse by Pointer Swap, Min, Max ===" << endl << endl;

    // --- Build initial list ---
    cout << "--- Inserting Elements ---" << endl;
    int values[] = {30, 10, 70, 20, 60, 50, 90, 40};
    int n        = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) insert(values[i]);

    cout << "Original list:   ";
    printList();

    // --- Min and Max ---
    findMin();
    findMax();

    // --- Reverse (first time) ---
    cout << endl << "--- Reversing List ---" << endl;
    reverseList();
    cout << "After reversal:  ";
    printList();

    // Validate that pointers are correct after reversal
    cout << "Pointer integrity: "
         << (validateLinks() ? "PASS ✓" : "FAIL ✗") << endl;

    // --- Min/Max still work on reversed list ---
    cout << endl << "--- Min/Max on reversed list ---" << endl;
    findMin();
    findMax();

    // --- Reverse again (should restore original) ---
    cout << endl << "--- Reversing Again (should restore original) ---" << endl;
    reverseList();
    cout << "After 2nd reversal: ";
    printList();

    // --- Insert into reversed list (problem says list is updated) ---
    cout << endl << "--- Insert 5 then reverse ---" << endl;
    insert(5);
    cout << "After inserting 5: ";
    printList();
    reverseList();
    cout << "After reversal:    ";
    printList();

    // --- Interactive Menu ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice, val;

    do {
        cout << "\n1. Insert\n2. Print List\n3. Reverse\n4. Find Min\n5. Find Max\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                insert(val);
                printList();
                break;
            case 2:
                printList();
                break;
            case 3:
                reverseList();
                printList();
                break;
            case 4:
                findMin();
                break;
            case 5:
                findMax();
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
REVERSE BY POINTER SWAP — STEP BY STEP:

Before:  head→[30]↔[10]↔[70]↔[20]→NULL
         30.prev=NULL  30.next=10
         10.prev=30    10.next=70
         70.prev=10    70.next=20
         20.prev=70    20.next=NULL

Processing each node (swap next↔prev):

  curr=30:
    nextNode = 30.next = 10  (save it!)
    30.next  = 30.prev = NULL
    30.prev  = nextNode = 10
    newHead  = 30
    curr     = nextNode = 10

  curr=10:
    nextNode = 10.next = 70  (save it!)
    10.next  = 10.prev = 30
    10.prev  = nextNode = 70
    newHead  = 10
    curr     = nextNode = 70

  curr=70:
    nextNode = 70.next = 20  (save it!)
    70.next  = 70.prev = 10
    70.prev  = nextNode = 20
    newHead  = 70
    curr     = nextNode = 20

  curr=20:
    nextNode = 20.next = NULL  (save it!)
    20.next  = 20.prev = 70
    20.prev  = nextNode = NULL
    newHead  = 20
    curr     = nextNode = NULL

  Loop ends. head = newHead = 20

After: head→[20]↔[70]↔[10]↔[30]→NULL
       20.prev=NULL  20.next=70  ✓
       70.prev=20    70.next=10  ✓
       10.prev=70    10.next=30  ✓
       30.prev=10    30.next=NULL ✓

Original order was 30→10→70→20
After reversal:    20→70→10→30 ✓
*/

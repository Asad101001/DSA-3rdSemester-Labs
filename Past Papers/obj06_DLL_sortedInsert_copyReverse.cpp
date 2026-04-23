/*
============================================================
OBJECTIVE #06 - DOUBLY LINKED LIST: SORTED INSERT + COPY-REVERSE
============================================================

PROBLEM SUMMARY:
  Use a DOUBLY LINKED LIST to perform:
  1. SORTED INSERT: Sort the value at the TIME OF INSERTION.
     (Every insert keeps the DLL in ascending order)
  2. COPY-REVERSE: Copy the REVERSE of the first list
     into a COMPLETELY NEW doubly linked list.

DIFFERENCE from Objective 05 (singly linked list):
  → Nodes have BOTH next AND prev pointers
  → Sorted insert must update BOTH prev and next correctly
  → Copy-reverse must also correctly wire prev pointers
  → Traversal can go both directions (forward and backward)

DIFFERENCE from existing doublyLinkedList.cpp:
  → Always inserts in sorted order (not just at end)
  → Adds copy-reverse to new DLL functionality
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
// Double-linked: each node knows its previous and next neighbor
struct Node {
    int   data;
    Node* next;   // points to next node (→)
    Node* prev;   // points to previous node (←)
};

// ─── TWO LISTS ────────────────────────────────────────────────────────────────
Node* list        = NULL;   // original sorted DLL
Node* reversedList = NULL;  // copy-reversed DLL

// ─── HELPER: CREATE A NEW NODE ────────────────────────────────────────────────
Node* createNode(int val) {
    Node* temp  = new Node();
    temp->data  = val;
    temp->next  = NULL;
    temp->prev  = NULL;
    return temp;
}

// ─── OPERATION 1: SORTED INSERT (DLL) ────────────────────────────────────────
// Insert 'val' maintaining ascending sorted order.
// Must correctly wire BOTH next AND prev pointers at the insertion point.
//
// Cases:
//  A: List is empty               → simple single-node list
//  B: val <= head->data           → insert before head (new head)
//  C: val should go in middle     → find position, link both directions
//  D: val > all existing values   → insert at tail
void sortedInsert(int val) {

    Node* newNode = createNode(val);

    // ── Case A: empty list ────────────────────────────────────────────
    if (list == NULL) {
        list = newNode;
        return;
    }

    // ── Case B: val belongs before the current head ───────────────────
    if (val <= list->data) {
        newNode->next = list;   // new node → old head
        list->prev    = newNode; // old head → new node (backward link)
        list          = newNode; // update head
        return;
    }

    // ── Cases C & D: traverse to find insertion point ─────────────────
    Node* curr = list;

    // Advance while: there IS a next node AND next node's data < val
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }

    // Now insert newNode BETWEEN curr and curr->next
    //
    // Before:  [curr] ←→ [curr->next]  (or curr->next == NULL)
    // After:   [curr] ←→ [newNode] ←→ [curr->next]

    newNode->next = curr->next;    // newNode → curr->next (or NULL)
    newNode->prev = curr;          // newNode ← curr

    if (curr->next != NULL) {
        curr->next->prev = newNode;  // curr->next ← newNode (prev link)
    }

    curr->next = newNode;          // curr → newNode
}

// ─── DISPLAY FORWARD ─────────────────────────────────────────────────────────
void displayForward(Node* head) {
    if (head == NULL) {
        cout << "(empty)" << endl;
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

// ─── DISPLAY BACKWARD ─────────────────────────────────────────────────────────
// Walk to tail first, then traverse backward using prev pointers
void displayBackward(Node* head) {
    if (head == NULL) {
        cout << "(empty)" << endl;
        return;
    }

    // Walk to tail
    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;

    // Now traverse backward
    cout << "NULL ← ";
    while (curr != NULL) {
        cout << "[" << curr->data << "]";
        if (curr->prev != NULL) cout << " ↔ ";
        curr = curr->prev;
    }
    cout << " → NULL" << endl;
}

// ─── OPERATION 2: COPY-REVERSE (DLL) ─────────────────────────────────────────
// Creates a completely new DLL that is the reverse of the original.
//
// Strategy: walk original forward, PREPEND each node's data to new DLL.
// → This naturally reverses the order.
// → Each new node gets both next and prev properly wired.
//
// Returns the head of the new reversed DLL.
Node* copyReverse(Node* original) {

    if (original == NULL) return NULL;

    Node* newHead = NULL;   // head of the new reversed DLL

    Node* curr = original;
    while (curr != NULL) {

        // Create a new independent node
        Node* newNode  = createNode(curr->data);

        // PREPEND to new list (insert at front)
        // newNode becomes the new head
        newNode->next = newHead;   // new node → current front

        if (newHead != NULL) {
            newHead->prev = newNode;   // old front ← new node (prev link)
        }

        newHead = newNode;   // update head pointer

        curr = curr->next;   // advance through original
    }

    // newHead->prev should be NULL (it's the new head, nothing before it)
    // (It already is NULL from createNode)

    return newHead;
}

// ─── FREE A DLL ──────────────────────────────────────────────────────────────
void freeDLL(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
}

// ─── VALIDATE DLL INTEGRITY ───────────────────────────────────────────────────
// Walk forward, then backward, verifying all prev/next links are consistent
bool validateDLL(Node* head) {
    if (head == NULL) return true;

    // Forward pass: check prev links
    Node* curr = head;
    while (curr->next != NULL) {
        if (curr->next->prev != curr) {
            cout << "ERROR: prev link broken at " << curr->data << endl;
            return false;
        }
        curr = curr->next;
    }
    // curr is now at tail

    // Backward pass: verify we get back to head
    Node* tail = curr;
    while (tail->prev != NULL) {
        if (tail->prev->next != tail) {
            cout << "ERROR: next link broken at " << tail->data << endl;
            return false;
        }
        tail = tail->prev;
    }

    if (tail != head) {
        cout << "ERROR: backward pass did not reach head!" << endl;
        return false;
    }

    return true;
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Doubly Linked List: Sorted Insert + Copy-Reverse ===" << endl << endl;

    // --- Part 1: Sorted Insert ---
    cout << "--- Part 1: Sorted Insert (DLL) ---" << endl;

    int values[] = {45, 15, 75, 5, 55, 25, 65, 35};
    int n        = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        sortedInsert(values[i]);
        cout << "Insert " << values[i] << " → ";
        displayForward(list);
    }

    cout << endl << "Final sorted DLL (forward):  ";
    displayForward(list);

    cout << "Final sorted DLL (backward): ";
    displayBackward(list);

    cout << endl << "DLL integrity check: "
         << (validateDLL(list) ? "PASS ✓" : "FAIL ✗") << endl;

    // --- Part 2: Copy-Reverse ---
    cout << endl << "--- Part 2: Copy-Reverse (DLL) ---" << endl;
    reversedList = copyReverse(list);

    cout << "Original   (ascending):    ";
    displayForward(list);

    cout << "Reversed copy (descending): ";
    displayForward(reversedList);

    cout << "Reversed (backward check): ";
    displayBackward(reversedList);

    cout << endl << "Reversed DLL integrity: "
         << (validateDLL(reversedList) ? "PASS ✓" : "FAIL ✗") << endl;

    cout << endl << "Original unchanged: ";
    displayForward(list);

    // --- Interactive Menu ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice, val;

    do {
        cout << "\n1. Sorted Insert\n2. Display Forward\n3. Display Backward\n4. Copy-Reverse\n5. Display Reversed\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                sortedInsert(val);
                cout << "List: ";
                displayForward(list);
                break;

            case 2:
                cout << "Forward: ";
                displayForward(list);
                break;

            case 3:
                cout << "Backward: ";
                displayBackward(list);
                break;

            case 4:
                freeDLL(reversedList);
                reversedList = copyReverse(list);
                cout << "Reversed copy created." << endl;
                break;

            case 5:
                if (reversedList == NULL)
                    cout << "No reversed list yet. Use option 4 first." << endl;
                else {
                    cout << "Reversed: ";
                    displayForward(reversedList);
                }
                break;

            case 6:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 6);

    freeDLL(list);
    freeDLL(reversedList);

    return 0;
}

/*
SORTED INSERT WALKTHROUGH (DLL):

Insert 45:  NULL ← [45] → NULL
Insert 15:  NULL ← [15] ↔ [45] → NULL     (15 < 45 → new head)
Insert 75:  NULL ← [15] ↔ [45] ↔ [75] → NULL
Insert 5:   NULL ← [5] ↔ [15] ↔ [45] ↔ [75] → NULL  (new head)
...continuing...
Final: [5] ↔ [15] ↔ [25] ↔ [35] ↔ [45] ↔ [55] ↔ [65] ↔ [75]

COPY-REVERSE WALKTHROUGH:

Walk original: 5 → 15 → 25 → 35 → 45 → 55 → 65 → 75

Prepend each to new DLL:
  5:  newHead = [5]
  15: newHead = [15] ↔ [5]   (15 prepended, 5's prev = 15)
  25: newHead = [25] ↔ [15] ↔ [5]
  ...
  75: newHead = [75] ↔ [65] ↔ [55] ↔ [45] ↔ [35] ↔ [25] ↔ [15] ↔ [5]

Result = reversed order ✓
Original = unchanged ✓
All prev/next links = correct ✓
*/

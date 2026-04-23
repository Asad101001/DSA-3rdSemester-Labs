/*
============================================================
OBJECTIVE #03 - DOUBLY LINKED LIST WITH TAIL + QUICKSORT
============================================================

PROBLEM SUMMARY:
  Implement a DOUBLY LINKED LIST with:
  1. Insert operation
  2. Print operation
  3. Store address of LAST element (tail pointer) — in addition to start/head
  4. Each node has an INDEX field = count/position of the node in the list
  5. Implement QUICK SORT on this doubly linked list

KEY DIFFERENCES from existing doublyLinkedList.cpp:
  → Also maintain a 'tail' pointer (to last node)
  → Each node stores its 'index' (1-based position counter)
  → QuickSort implemented directly on the list (swapping data)

HOW QUICKSORT ON LINKED LIST WORKS:
  - Choose pivot = last node's data
  - Partition: walk from head to tail-1, swap data if < pivot
  - Recursively sort left and right partitions
  - Since we have index fields, we can identify partition boundaries
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
// Compared to existing doublyLinkedList.cpp:
//   → Added 'index' field (position in the list)
//   → We also maintain a global 'tail' pointer below
struct Node {
    int   data;    // value stored
    int   index;   // position of this node in the list (1-based)
    Node* next;    // pointer to next node
    Node* prev;    // pointer to previous node
};

// ─── GLOBAL POINTERS ─────────────────────────────────────────────────────────
Node* head = NULL;   // pointer to first node (start)
Node* tail = NULL;   // pointer to last node  (as required by the problem)
int   nodeCount = 0; // total number of nodes (used to assign index)

// ─── INSERT (at tail / end of list) ──────────────────────────────────────────
// Updates both head AND tail pointers.
// Assigns index = current nodeCount after incrementing.
void insert(int val) {

    // Create new node
    Node* temp  = new Node();
    temp->data  = val;
    temp->next  = NULL;
    temp->prev  = NULL;

    nodeCount++;             // increment count before assigning index
    temp->index = nodeCount; // index = position in list (1-based)

    // CASE: list is empty
    if (head == NULL) {
        head = tail = temp;  // both head and tail point to the only node
        return;
    }

    // CASE: list has at least one node → append at tail
    tail->next = temp;   // old tail's next = new node
    temp->prev = tail;   // new node's prev = old tail
    tail       = temp;   // update tail to new node
}

// ─── PRINT LIST ──────────────────────────────────────────────────────────────
// Prints: data and index of each node, head→→→tail direction
void printList() {
    if (head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    cout << "HEAD";
    Node* curr = head;
    while (curr != NULL) {
        cout << " <-> [" << curr->data << " (idx:" << curr->index << ")]";
        curr = curr->next;
    }
    cout << " <-> TAIL" << endl;

    // Also show tail to verify tail pointer is correct
    cout << "Tail node = " << tail->data
         << "  |  Head node = " << head->data << endl;
}

// ─── UPDATE INDICES ───────────────────────────────────────────────────────────
// After QuickSort rearranges data (by swapping node data fields),
// the index fields also need to be refreshed to reflect new positions.
void updateIndices() {
    Node* curr = head;
    int   idx  = 1;
    while (curr != NULL) {
        curr->index = idx++;
        curr        = curr->next;
    }
}

// ─── QUICKSORT HELPERS ───────────────────────────────────────────────────────
// We sort by SWAPPING DATA VALUES inside nodes (not relinking nodes).
// This is simpler and still O(n log n) on average.
// 'low' and 'high' are Node pointers marking partition boundaries.

// Partition: choose high->data as pivot
//            rearrange so elements < pivot come before pivot position
//            return the node that ends up at the pivot position
Node* partition(Node* low, Node* high) {

    int   pivot   = high->data;  // pivot is the data of 'high' node
    Node* swapPos = low;         // swapPos = boundary of "less than pivot" region
                                 // we'll swap data into swapPos and advance it

    Node* curr = low;            // iterator

    // Walk from 'low' to the node BEFORE 'high'
    while (curr != high) {

        if (curr->data <= pivot) {
            // curr's data belongs in the "≤ pivot" region
            // swap curr's data with swapPos's data
            int temp       = swapPos->data;
            swapPos->data  = curr->data;
            curr->data     = temp;

            swapPos = swapPos->next;   // advance the boundary
        }

        curr = curr->next;   // move to next node
    }

    // Place pivot at swapPos (swap swapPos and high)
    int temp       = swapPos->data;
    swapPos->data  = high->data;
    high->data     = temp;

    return swapPos;   // return the pivot's final position
}

// Recursive QuickSort on doubly linked list
// 'low' = leftmost node of current partition
// 'high' = rightmost node of current partition
void quickSort(Node* low, Node* high) {

    // BASE CASE: empty or single-element partition
    if (low == NULL || high == NULL || low == high || high->next == low)
        return;

    // Partition and get pivot's final position
    Node* pivot = partition(low, high);

    // Recursively sort the left part (before pivot)
    // The node just before pivot is pivot->prev
    quickSort(low, pivot->prev);

    // Recursively sort the right part (after pivot)
    quickSort(pivot->next, high);
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Doubly Linked List with Tail Pointer + QuickSort ===" << endl << endl;

    // --- Part 1: Insert elements ---
    cout << "--- Inserting Elements ---" << endl;
    int values[] = {42, 17, 88, 5, 63, 29, 91, 11};
    int n        = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insert(values[i]);
        cout << "Inserted: " << values[i] << "  (index = " << nodeCount << ")" << endl;
    }

    cout << endl << "--- List Before Sorting ---" << endl;
    printList();

    // --- Part 2: QuickSort ---
    cout << endl << "--- Applying QuickSort ---" << endl;
    quickSort(head, tail);

    // After sorting, data values have shifted; update index fields
    updateIndices();

    cout << endl << "--- List After Sorting ---" << endl;
    printList();

    // --- Part 3: Verify tail pointer still correct ---
    cout << endl << "--- Verification ---" << endl;
    cout << "head->data (should be smallest): " << head->data << endl;
    cout << "tail->data (should be largest):  " << tail->data << endl;
    cout << "head->prev (should be NULL): "
         << (head->prev == NULL ? "NULL ✓" : "NOT NULL ✗") << endl;
    cout << "tail->next (should be NULL): "
         << (tail->next == NULL ? "NULL ✓" : "NOT NULL ✗") << endl;

    // --- Part 4: Interactive demo ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice, val;
    do {
        cout << "\n1. Insert\n2. Print List\n3. QuickSort\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                insert(val);
                cout << "Inserted " << val << " at index " << nodeCount << endl;
                break;

            case 2:
                printList();
                break;

            case 3:
                quickSort(head, tail);
                updateIndices();
                cout << "Sorted!" << endl;
                printList();
                break;

            case 4:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 4);

    return 0;
}

/*
HOW QUICKSORT WORKS ON LINKED LIST — STEP BY STEP:

List: 42 <-> 17 <-> 88 <-> 5 <-> 63 <-> 29 <-> 91 <-> 11

quickSort(head=42, tail=11):
  pivot = 11 (tail's data)
  Partition:
    curr=42: 42 <= 11? No
    curr=17: 17 <= 11? No
    curr=88: No
    curr=5:  5  <= 11? YES → swap(swapPos=42, curr=5)  → list: 5 17 88 42 63 29 91 11
             swapPos advances → swapPos=17
    curr=63: No
    curr=29: No
    curr=91: No
  Final: swap(swapPos=17, high=11) → list: 5 11 88 42 63 29 91 17
                                            ^  ^
                                         pivot's position returned = node holding 11

  Left: quickSort(5, node-before-11=5) → single node, done
  Right: quickSort(88, 17) → recurse on {88, 42, 63, 29, 91, 17}

... and so on recursively until fully sorted.

Time Complexity:  O(n log n) average, O(n²) worst
Space Complexity: O(log n) recursion stack
*/

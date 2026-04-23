/*
============================================================
OBJECTIVE #05 - SINGLY LINKED LIST: SORTED INSERT + COPY-REVERSE
============================================================

PROBLEM SUMMARY:
  Use a linked list to perform:
  1. SORTED INSERT: Sort the value at the TIME OF INSERTION.
     (Every insert keeps the list in ascending order)
  2. COPY-REVERSE: Copy the list into a COMPLETELY NEW list
     and reverse it (new list is in descending order).

DIFFERENCE from existing linkedlist.cpp:
  → Existing code inserts at the END (no sorting).
  → This file inserts IN SORTED POSITION (ascending).
  → This file adds a copy-reverse function that
    creates a brand new list (not in-place reversal).
============================================================
*/

#include <iostream>
using namespace std;

// ─── NODE STRUCTURE ──────────────────────────────────────────────────────────
// Same as existing linked list code
struct Node {
    int   data;
    Node* next;
};

// ─── TWO SEPARATE LISTS ───────────────────────────────────────────────────────
Node* list        = NULL;   // original sorted list
Node* reversedList = NULL;  // copy-reversed list (created by copyReverse)

// ─── OPERATION 1: SORTED INSERT ───────────────────────────────────────────────
// Inserts 'val' such that the list remains sorted ascending.
//
// Three cases:
//  Case A: List is empty                → just create node, done
//  Case B: val < head->data             → insert BEFORE head (new head)
//  Case C: val goes somewhere in middle/end → find correct position, link
void sortedInsert(int val) {

    // Create the new node (same as existing insert())
    Node* temp = new Node();
    temp->data = val;
    temp->next = NULL;

    // ── Case A: list is empty ─────────────────────────────────────────
    if (list == NULL) {
        list = temp;
        return;
    }

    // ── Case B: val is smaller than current head ─────────────────────
    // New node becomes the new head
    if (val <= list->data) {
        temp->next = list;   // new node points to old head
        list       = temp;   // update head pointer
        return;
    }

    // ── Case C: find position in middle or end ────────────────────────
    // Walk until we find a node whose NEXT is either:
    //  • NULL (reached the end), or
    //  • has data >= val (insert before that next node)
    Node* curr = list;
    while (curr->next != NULL && curr->next->data < val) {
        curr = curr->next;
    }

    // Insert between curr and curr->next
    temp->next  = curr->next;   // new node → whatever was after curr
    curr->next  = temp;         // curr → new node
}

// ─── DISPLAY LIST ─────────────────────────────────────────────────────────────
void displayList(Node* head) {
    if (head == NULL) {
        cout << "(empty list)" << endl;
        return;
    }

    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data;
        if (curr->next != NULL) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> NULL" << endl;
}

// ─── OPERATION 2: COPY-REVERSE ────────────────────────────────────────────────
// Creates a COMPLETELY NEW list that is:
//  • A copy of 'list' (every node duplicated — not the same memory)
//  • Reversed in order (last element of original becomes first)
//
// Strategy (prepend each element → natural reversal):
//  Walk through the original list left-to-right.
//  For each node, create a new node and INSERT AT THE FRONT of the new list.
//  → First element of original ends up at the back of new list
//  → Last element of original ends up at the front of new list
//  → Result: reversed copy
Node* copyReverse(Node* original) {

    Node* newHead = NULL;   // head of the new reversed list

    Node* curr = original;
    while (curr != NULL) {

        // Create a brand-new node (new memory, not reusing original nodes)
        Node* newNode  = new Node();
        newNode->data  = curr->data;
        newNode->next  = NULL;

        // Prepend: new node → existing newHead
        newNode->next = newHead;   // new node points to current front
        newHead       = newNode;   // update front to new node

        curr = curr->next;   // advance through original
    }

    return newHead;   // head of the new reversed list
}

// ─── FREE A LIST ─────────────────────────────────────────────────────────────
// Releases all nodes of a list from memory.
void freeList(Node*& head) {
    while (head != NULL) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
}

// ─── MAIN ────────────────────────────────────────────────────────────────────
int main() {

    cout << "=== Singly Linked List: Sorted Insert + Copy-Reverse ===" << endl << endl;

    // --- Part 1: Sorted Insert ---
    cout << "--- Part 1: Sorted Insert ---" << endl;

    // Insert in non-sorted order to demonstrate sorting happens automatically
    int values[] = {50, 20, 80, 10, 60, 30, 70, 40};
    int n        = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        sortedInsert(values[i]);
        cout << "Insert " << values[i] << "  → ";
        displayList(list);
    }

    cout << endl << "Final sorted list:" << endl;
    displayList(list);

    // --- Part 2: Copy-Reverse ---
    cout << endl << "--- Part 2: Copy-Reverse ---" << endl;
    reversedList = copyReverse(list);

    cout << "Original (ascending):  ";
    displayList(list);

    cout << "Reversed copy (descending): ";
    displayList(reversedList);

    // Verify original is unchanged
    cout << endl << "Original still intact: ";
    displayList(list);

    // Verify memory is separate (modify reversed list without affecting original)
    // Insert into reversed list → should not change original
    Node* temp   = new Node();
    temp->data   = 999;
    temp->next   = reversedList;
    reversedList = temp;

    cout << "After adding 999 to reversed list:" << endl;
    cout << "  Reversed: ";
    displayList(reversedList);
    cout << "  Original (unchanged): ";
    displayList(list);

    // --- Interactive Menu ---
    cout << endl << "=== Interactive Menu ===" << endl;
    int choice, val;

    do {
        cout << "\n1. Sorted Insert\n2. Display Original List\n3. Copy-Reverse\n4. Display Reversed List\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                sortedInsert(val);
                cout << "Inserted. List: ";
                displayList(list);
                break;

            case 2:
                cout << "Original list: ";
                displayList(list);
                break;

            case 3:
                freeList(reversedList);   // free old reversed list
                reversedList = copyReverse(list);
                cout << "Created reversed copy." << endl;
                break;

            case 4:
                if (reversedList == NULL)
                    cout << "No reversed list yet. Use option 3 first." << endl;
                else {
                    cout << "Reversed list: ";
                    displayList(reversedList);
                }
                break;

            case 5:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 5);

    // Clean up memory
    freeList(list);
    freeList(reversedList);

    return 0;
}

/*
STEP-BY-STEP WALKTHROUGH:

SORTED INSERT:
  Start: (empty)
  Insert 50: [50]
  Insert 20: [20 → 50]    (20 < 50 → inserted before 50)
  Insert 80: [20 → 50 → 80]
  Insert 10: [10 → 20 → 50 → 80]   (10 < 20 → new head)
  Insert 60: [10 → 20 → 50 → 60 → 80]
  Insert 30: [10 → 20 → 30 → 50 → 60 → 80]
  Insert 70: [10 → 20 → 30 → 50 → 60 → 70 → 80]
  Insert 40: [10 → 20 → 30 → 40 → 50 → 60 → 70 → 80]

COPY-REVERSE:
  Original: 10 → 20 → 30 → 40 → 50 → 60 → 70 → 80

  Walk original left to right, prepend each to new list:
    Process 10: newList = [10]
    Process 20: newList = [20 → 10]
    Process 30: newList = [30 → 20 → 10]
    ...
    Process 80: newList = [80 → 70 → 60 → 50 → 40 → 30 → 20 → 10]

  Result: 80 → 70 → 60 → 50 → 40 → 30 → 20 → 10 → NULL  ✓
  Original: 10 → 20 → 30 → 40 → 50 → 60 → 70 → 80 → NULL  (unchanged ✓)

MEMORY: Original and reversed are completely independent copies.
*/

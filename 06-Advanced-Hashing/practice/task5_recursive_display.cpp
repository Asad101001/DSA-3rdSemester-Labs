/*
================================================================================
LINKED LIST - RECURSIVE FORWARD AND REVERSE DISPLAY
================================================================================

RECURSION:
----------
Function that calls itself to solve smaller subproblems.

Base case: Stop condition (prevents infinite recursion)
Recursive case: Call itself with smaller problem

Think of Russian dolls - each doll contains smaller doll until smallest one.

Python:
def display(node):
    if node:  # Base case
        print(node.data)
        display(node.next)  # Recursive case
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;  // Global list head

void insert(int val) {
    Node* curr = new Node;
    curr->data = val;
    curr->next = NULL;
    
    if (head == NULL) {
        head = curr;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr;
    }
}

void displayForward(Node* node) {
    if (node == NULL) {
        return;  // Base case: reached end
    }
    
    cout << node->data << " ";     // Print current
    displayForward(node->next);    // Recurse on rest
}

void displayReverse(Node* node) {
    if (node == NULL) {
        return;  // Base case
    }
    
    displayReverse(node->next);    // Recurse FIRST
    cout << node->data << " ";     // Print AFTER recursion
}

int main() {
    cout << "=== RECURSIVE LINKED LIST ===\n\n";
    
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);
    
    cout << "List: 10→20→30→40→50→NULL\n\n";
    
    displayForward(head);
    cout << endl;
    
    displayReverse(head);
    cout << endl;
    
    
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}

/*
EXPLANATION:
------------

1. WHAT IS RECURSION?
   Function calling itself
   
   Must have:
   - Base case (stop condition)
   - Recursive case (call itself)
   
   Without base case = infinite recursion = crash!

2. FORWARD DISPLAY
   
   void displayForward(Node* node) {
       if (node == NULL) return;  // Base case
       cout << node->data;         // Process
       displayForward(node->next); // Recurse
   }
   
   Pattern: PROCESS → RECURSE
   
   Like reading a book page by page:
   Read page 1, then rest of book
   Read page 2, then rest of book
   ...

3. REVERSE DISPLAY
   
   void displayReverse(Node* node) {
       if (node == NULL) return;   // Base case
       displayReverse(node->next); // Recurse FIRST
       cout << node->data;          // Process AFTER
   }
   
   Pattern: RECURSE → PROCESS
   
   Like stacking plates and removing:
   Stack all plates (going down)
   Remove from top (coming back up)

4. RECURSION STACK
   Computer uses call stack to track function calls
   
   Each call stores:
   - Parameters (node pointer)
   - Local variables
   - Return address
   
   Stack grows as we recurse
   Stack shrinks as we return

5. TIME AND SPACE
   Time: O(n) - visit each node once
   Space: O(n) - recursion stack depth
   
   Iterative would be O(1) space
   But recursion is more elegant!

6. WHEN TO USE RECURSION?
   ✓ Tree traversals
   ✓ Divide and conquer (merge sort, quicksort)
   ✓ Backtracking problems
   ✓ Problems with recursive structure
   
   ✗ Simple loops (wasteful)
   ✗ Very deep recursion (stack overflow)

7. RECURSION vs ITERATION
   
   Recursive (reverse):
   void displayReverse(Node* n) {
       if (!n) return;
       displayReverse(n->next);
       cout << n->data;
   }
   
   Iterative (reverse - needs extra space):
   void displayReverse(Node* head) {
       int arr[100];
       int i = 0;
       Node* curr = head;
       while (curr) {
           arr[i++] = curr->data;
           curr = curr->next;
       }
       for (int j = i-1; j >= 0; j--)
           cout << arr[j];
   }
   
   Recursive is cleaner for reverse!
*/

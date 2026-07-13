/*
================================================================================
QUEUE USING LINKED LIST
================================================================================

CONCEPT:
--------
Queue where elements are stored in nodes connected by pointers.
Dynamic size - grows and shrinks as needed.

STRUCTURE:
front → [10]→[20]→[30]→NULL ← rear

WHY TWO POINTERS?
- front: Remove from here (O(1))
- rear: Add to here (O(1))

With only front, adding would need O(n) traversal.

Python equivalent:
from collections import deque
q = deque()
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
    int size;
};

Queue q;  // Global queue

void enqueue(int val) {
    Node* curr = new Node;  // Allocate memory
    curr->data = val;
    curr->next = NULL;
    
    if (q.rear == NULL) {
        // First element
        q.front = curr;
        q.rear = curr;
    } else {
        // Add to rear
        q.rear->next = curr;
        q.rear = curr;
    }
    q.size++;
    cout << "Enqueued: " << val << endl;
}

int dequeue() {
    if (q.front == NULL) {
        cout << "Queue EMPTY!" << endl;
        return -1;
    }
    
    int val = q.front->data;
    Node* temp = q.front;
    q.front = q.front->next;
    
    // CRITICAL: If empty now, update rear too!
    if (q.front == NULL) {
        q.rear = NULL;
    }
    
    delete temp;  // Free memory
    q.size--;
    return val;
}

void display() {
    if (q.front == NULL) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    cout << "Queue: ";
    Node* curr = q.front;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "(size=" << q.size << ")" << endl;
}

int main() {
    // Initialize
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
    
    cout << "=== LINKED LIST QUEUE ===\n\n";
    
    // Add elements
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();
    
    // Remove 2
    cout << "\nRemoving 2:\n";
    cout << "Dequeued: " << dequeue() << endl;
    cout << "Dequeued: " << dequeue() << endl;
    display();
    
    // Add more (shows dynamic growth)
    cout << "\nAdding more (grows dynamically):\n";
    enqueue(60);
    enqueue(70);
    enqueue(80);
    display();
    
    // Remove all
    cout << "\nRemoving all:\n";
    while (q.front != NULL) {
        cout << dequeue() << " ";
    }
    cout << endl;
    display();
    
    return 0;
}

/*
EXPLANATION:
------------

1. DYNAMIC MEMORY (new/delete)
   new Node - Allocates memory on heap
              Returns address (pointer)
              Memory persists until delete
              
   delete temp - Frees memory
                 Prevents memory leaks

2. WHY UPDATE rear WHEN EMPTY?
   Last element removed:
   Before: front→[10]→NULL ← rear
   After dequeue: front=NULL, but rear still points to old node!
   
   This is DANGLING POINTER - points to freed memory
   Must set: rear = NULL

3. LINKED LIST vs ARRAY
   Linked List:
   ✓ Dynamic size (no fixed limit)
   ✓ Efficient add/remove
   ✗ Extra memory for pointers
   ✗ Scattered in memory (cache unfriendly)
   
   Array (Circular):
   ✓ Contiguous memory (cache friendly)
   ✓ Less memory overhead
   ✗ Fixed size
   ✗ Need modulo arithmetic

4. TIME COMPLEXITY:
   enqueue: O(1) - direct access to rear
   dequeue: O(1) - direct access to front
   
5. SPACE:
   O(n) where n = number of elements
   Each node: data + pointer
*/

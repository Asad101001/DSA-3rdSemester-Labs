/*
================================================================================
STACK AND QUEUE COMPARISON
================================================================================

STACK: LIFO (Last In, First Out)
Like a stack of plates - last one added is first removed

QUEUE: FIFO (First In, First Out)  
Like a line of people - first in line is first served

Python:
stack = []
stack.append(x)  # push
stack.pop()      # pop

queue = deque()
queue.append(x)     # enqueue
queue.popleft()     # dequeue
*/

#include <iostream>
using namespace std;

//==============================================================================
// STACK
//==============================================================================

struct StackNode {
    int data;
    StackNode* next;
};

struct Stack {
    StackNode* top;
    int size;
};

Stack s;  // Global stack

void push(int val) {
    StackNode* curr = new StackNode;
    curr->data = val;
    curr->next = s.top;
    s.top = curr;
    s.size++;
}

int pop() {
    if (s.top == NULL) {
        cout << "Stack EMPTY!" << endl;
        return -1;
    }
    
    int val = s.top->data;
    StackNode* temp = s.top;
    s.top = s.top->next;
    delete temp;
    s.size--;
    return val;
}

void displayStack() {
    if (s.top == NULL) {
        cout << "Stack empty" << endl;
        return;
    }
    
    cout << "Stack (top→bottom): ";
    StackNode* curr = s.top;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

//==============================================================================
// QUEUE
//==============================================================================

struct QueueNode {
    int data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
};

Queue q;  // Global queue

void enqueue(int val) {
    QueueNode* curr = new QueueNode;
    curr->data = val;
    curr->next = NULL;
    
    if (q.rear == NULL) {
        q.front = curr;
        q.rear = curr;
    } else {
        q.rear->next = curr;
        q.rear = curr;
    }
    q.size++;
}

int dequeue() {
    if (q.front == NULL) {
        cout << "Queue EMPTY!" << endl;
        return -1;
    }
    
    int val = q.front->data;
    QueueNode* temp = q.front;
    q.front = q.front->next;
    
    if (q.front == NULL) {
        q.rear = NULL;
    }
    
    delete temp;
    q.size--;
    return val;
}

void displayQueue() {
    if (q.front == NULL) {
        cout << "Queue empty" << endl;
        return;
    }
    
    cout << "Queue (front→rear): ";
    QueueNode* curr = q.front;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

//==============================================================================
// MAIN
//==============================================================================

int main() {
    // Initialize stack
    s.top = NULL;
    s.size = 0;
    
    // Initialize queue
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
    
    cout << "=== STACK vs QUEUE ===\n\n";
    
    // Demonstrate Stack (LIFO)
    cout << "--- STACK (LIFO) ---\n";
    cout << "Push: 10, 20, 30, 40, 50\n";
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    displayStack();
    
    cout << "\nPop twice:\n";
    cout << "Popped: " << pop() << endl;  // 50 (last in)
    cout << "Popped: " << pop() << endl;  // 40
    displayStack();
    
    // Demonstrate Queue (FIFO)
    cout << "\n--- QUEUE (FIFO) ---\n";
    cout << "Enqueue: 10, 20, 30, 40, 50\n";
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    displayQueue();
    
    cout << "\nDequeue twice:\n";
    cout << "Dequeued: " << dequeue() << endl;  // 10 (first in)
    cout << "Dequeued: " << dequeue() << endl;  // 20
    displayQueue();
    
    // Show the difference
    cout << "\n--- KEY DIFFERENCE ---\n";
    cout << "Input: 1, 2, 3, 4, 5\n\n";
    
    Stack s2;
    s2.top = NULL;
    s2.size = 0;
    
    Queue q2;
    q2.front = NULL;
    q2.rear = NULL;
    q2.size = 0;
    
    // Add same data to both
    for (int i = 1; i <= 5; i++) {
        StackNode* sn = new StackNode;
        sn->data = i;
        sn->next = s2.top;
        s2.top = sn;
        
        QueueNode* qn = new QueueNode;
        qn->data = i;
        qn->next = NULL;
        if (q2.rear == NULL) {
            q2.front = qn;
            q2.rear = qn;
        } else {
            q2.rear->next = qn;
            q2.rear = qn;
        }
    }
    
    // Remove all and show order
    cout << "Stack output (LIFO): ";
    while (s2.top != NULL) {
        cout << s2.top->data << " ";
        StackNode* temp = s2.top;
        s2.top = s2.top->next;
        delete temp;
    }
    cout << "\n";
    
    cout << "Queue output (FIFO): ";
    while (q2.front != NULL) {
        cout << q2.front->data << " ";
        QueueNode* temp = q2.front;
        q2.front = q2.front->next;
        delete temp;
    }
    cout << "\n";
    
    return 0;
}

/*
EXPLANATION:
------------

1. STACK (LIFO - Last In, First Out)
   
   Operations:
   push(x) - Add to top
   pop() - Remove from top
   
   Visual:
   push(1): [1]
   push(2): [2]→[1]
   push(3): [3]→[2]→[1]  ← top is 3
   pop(): returns 3 (last pushed)
   
   Like stacking plates:
   - Add on top
   - Remove from top
   - Last plate added is first removed

2. QUEUE (FIFO - First In, First Out)
   
   Operations:
   enqueue(x) - Add to rear
   dequeue() - Remove from front
   
   Visual:
   enqueue(1): front→[1]←rear
   enqueue(2): front→[1]→[2]←rear
   enqueue(3): front→[1]→[2]→[3]←rear
   dequeue(): returns 1 (first added)
   
   Like waiting in line:
   - Join at back (rear)
   - Leave from front
   - First person in line is first served

3. WHEN TO USE WHAT?
   
   Use Stack when:
   - Need to reverse order
   - Undo operations
   - Function call tracking
   - Expression evaluation
   - Backtracking algorithms
   
   Use Queue when:
   - Need to maintain order
   - Task scheduling
   - Breadth-first search
   - Print queue
   - Buffer management

4. IMPLEMENTATION
   Both use linked lists here:
   - Stack: One pointer (top)
   - Queue: Two pointers (front, rear)
   
   Both O(1) time for operations

5. MEMORY
   new - allocates memory
   delete - frees memory
   Must delete to prevent memory leaks!
*/

#include <iostream>
using namespace std;
struct StackNode {
    int data;
    StackNode* next;
};
struct Stack {
    StackNode* top;
    int size;
};
Stack s;  
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
struct QueueNode {
    int data;
    QueueNode* next;
};
struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
};
Queue q;  
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
int main() {
    s.top = NULL;
    s.size = 0;
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
    cout << "=== STACK vs QUEUE ===\n\n";
    cout << "--- STACK (LIFO) ---\n";
    cout << "Push: 10, 20, 30, 40, 50\n";
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    displayStack();
    cout << "\nPop twice:\n";
    cout << "Popped: " << pop() << endl;  
    cout << "Popped: " << pop() << endl;  
    displayStack();
    cout << "\n--- QUEUE (FIFO) ---\n";
    cout << "Enqueue: 10, 20, 30, 40, 50\n";
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    displayQueue();
    cout << "\nDequeue twice:\n";
    cout << "Dequeued: " << dequeue() << endl;  
    cout << "Dequeued: " << dequeue() << endl;  
    displayQueue();
    cout << "\n--- KEY DIFFERENCE ---\n";
    cout << "Input: 1, 2, 3, 4, 5\n\n";
    Stack s2;
    s2.top = NULL;
    s2.size = 0;
    Queue q2;
    q2.front = NULL;
    q2.rear = NULL;
    q2.size = 0;
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

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
Queue q;  
void enqueue(int val) {
    Node* curr = new Node;  
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
    if (q.front == NULL) {
        q.rear = NULL;
    }
    delete temp;  
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
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
    cout << "=== LINKED LIST QUEUE ===\n\n";
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();
    cout << "\nRemoving 2:\n";
    cout << "Dequeued: " << dequeue() << endl;
    cout << "Dequeued: " << dequeue() << endl;
    display();
    cout << "\nAdding more (grows dynamically):\n";
    enqueue(60);
    enqueue(70);
    enqueue(80);
    display();
    cout << "\nRemoving all:\n";
    while (q.front != NULL) {
        cout << dequeue() << " ";
    }
    cout << endl;
    display();
    return 0;
}

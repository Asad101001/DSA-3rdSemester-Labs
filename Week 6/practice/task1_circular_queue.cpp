#include <iostream>
using namespace std;

struct CircularQueue {
    int arr[10];
    int front;
    int rear;
    int count;
    int capacity;
};

CircularQueue q;  // Global queue

void enqueue(int val) {
    if (q.count == q.capacity) {
        cout << "Queue FULL! Cannot add " << val << endl;
        return;
    }
    
    q.rear = (q.rear + 1) % q.capacity;  // Circular increment
    q.arr[q.rear] = val;
    q.count++;
    cout << "Enqueued: " << val << endl;
}

int dequeue() {
    if (q.count == 0) {
        cout << "Queue EMPTY!" << endl;
        return -1;
    }
    
    int val = q.arr[q.front];
    q.front = (q.front + 1) % q.capacity;  // Circular increment
    q.count--;
    return val;
}

void display() {
    if (q.count == 0) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    cout << "Queue: ";
    int i = q.front;
    for (int c = 0; c < q.count; c++) {
        cout << q.arr[i] << " ";
        i = (i + 1) % q.capacity;
    }
    cout << endl;
}

int main() {

    q.front = 0;
    q.rear = -1;
    q.count = 0;
    q.capacity = 5;

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();
    
    enqueue(60);

    cout << "Dequeued: " << dequeue() << endl;
    cout << "Dequeued: " << dequeue() << endl;
    display();
    
    enqueue(60);
    enqueue(70);
    display();
    
    cout << "front=" << q.front << ", rear=" << q.rear << endl;
    
    return 0;
}

/*
EXPLANATION:
------------

1. MODULO OPERATOR (%)
   Returns remainder after division
   7 % 5 = 2  (7 divided by 5 = 1 remainder 2)
   
   For circular:
   index 0,1,2,3,4, then (4+1)%5 = 0  <- back to start

2. WHY count VARIABLE?
   Can't tell empty from full using just front/rear
   
   Empty: count = 0
   Full: count = capacity

3. OPERATIONS:
   enqueue: Add at rear, move rear circularly
   dequeue: Remove from front, move front circularly
   
   Both O(1) time!

4. ADVANTAGE:
   No wasted space - reuses freed positions
   
5. DISADVANTAGE:
   Fixed size - can't grow beyond capacity
*/

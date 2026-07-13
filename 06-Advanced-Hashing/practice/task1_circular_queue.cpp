#include <iostream>
using namespace std;
struct CircularQueue {
    int arr[10];
    int front;
    int rear;
    int count;
    int capacity;
};
CircularQueue q;  
void enqueue(int val) {
    if (q.count == q.capacity) {
        cout << "Queue FULL! Cannot add " << val << endl;
        return;
    }
    q.rear = (q.rear + 1) % q.capacity;  
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
    q.front = (q.front + 1) % q.capacity;  
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

#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct StackNode {
    T data;              
    StackNode<T>* next;  
};
template <typename T>
struct Stack {
    StackNode<T>* top;  
    int size;           
};
template <typename T>
void initStack(Stack<T>* stack) {
    stack->top = nullptr;
    stack->size = 0;
}
template <typename T>
bool isStackEmpty(Stack<T>* stack) {
    return stack->top == nullptr;
}
template <typename T>
int getStackSize(Stack<T>* stack) {
    return stack->size;
}
template <typename T>
void push(Stack<T>* stack, T value) {
    StackNode<T>* newNode = new StackNode<T>;
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}
template <typename T>
T pop(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Error: Stack underflow!" << endl;
        exit(1);
    }
    T value = stack->top->data;
    StackNode<T>* temp = stack->top;
    stack->top = stack->top->next;
    delete temp;
    stack->size--;
    return value;
}
template <typename T>
T peek(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Error: Stack is empty!" << endl;
        exit(1);
    }
    return stack->top->data;
}
template <typename T>
void displayStack(Stack<T>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Stack is empty" << endl;
        return;
    }
    cout << "Stack (top to bottom): ";
    StackNode<T>* current = stack->top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
template <typename T>
void destroyStack(Stack<T>* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
}
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
};
template <typename T>
struct Queue {
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int size;
};
template <typename T>
void initQueue(Queue<T>* queue) {
    queue->front = nullptr;
    queue->rear = nullptr;
    queue->size = 0;
}
template <typename T>
bool isQueueEmpty(Queue<T>* queue) {
    return queue->front == nullptr;
}
template <typename T>
int getQueueSize(Queue<T>* queue) {
    return queue->size;
}
template <typename T>
void enqueue(Queue<T>* queue, T value) {
    QueueNode<T>* newNode = new QueueNode<T>;
    newNode->data = value;
    newNode->next = nullptr;
    if (queue->rear == nullptr) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}
template <typename T>
T dequeue(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Error: Queue underflow!" << endl;
        exit(1);
    }
    T value = queue->front->data;
    QueueNode<T>* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == nullptr) {
        queue->rear = nullptr;
    }
    delete temp;
    queue->size--;
    return value;
}
template <typename T>
T frontElement(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Error: Queue is empty!" << endl;
        exit(1);
    }
    return queue->front->data;
}
template <typename T>
void displayQueue(Queue<T>* queue) {
    if (isQueueEmpty(queue)) {
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue (front to rear): ";
    QueueNode<T>* current = queue->front;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
template <typename T>
void destroyQueue(Queue<T>* queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
}
struct Student {
    string name;
    int rollNumber;
    double gpa;
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.name << ", Roll:" << s.rollNumber << ", GPA:" << s.gpa << "]";
        return os;
    }
};
void demonstrateStackTemplates() {
    cout << "\n====================================================\n";
    cout << "  STACK TEMPLATE DEMONSTRATIONS\n";
    cout << "====================================================\n\n";
    cout << "1. Stack<int> - Integer Stack:\n";
    Stack<int> intStack;
    initStack(&intStack);
    push(&intStack, 10);
    push(&intStack, 20);
    push(&intStack, 30);
    displayStack(&intStack);
    cout << "   Popped: " << pop(&intStack) << endl;
    displayStack(&intStack);
    cout << "\n2. Stack<double> - Double Stack:\n";
    Stack<double> doubleStack;
    initStack(&doubleStack);
    push(&doubleStack, 3.14);
    push(&doubleStack, 2.718);
    push(&doubleStack, 1.414);
    displayStack(&doubleStack);
    cout << "   Top: " << peek(&doubleStack) << endl;
    cout << "\n3. Stack<string> - String Stack:\n";
    Stack<string> stringStack;
    initStack(&stringStack);
    push(&stringStack, string("Hello"));
    push(&stringStack, string("World"));
    push(&stringStack, string("Templates"));
    displayStack(&stringStack);
    cout << "\n4. Stack<Student> - Custom Type Stack:\n";
    Stack<Student> studentStack;
    initStack(&studentStack);
    Student s1 = {"Alice", 101, 3.8};
    Student s2 = {"Bob", 102, 3.6};
    Student s3 = {"Charlie", 103, 3.9};
    push(&studentStack, s1);
    push(&studentStack, s2);
    push(&studentStack, s3);
    displayStack(&studentStack);
    cout << "   Popped: " << pop(&studentStack) << endl;
    displayStack(&studentStack);
    destroyStack(&intStack);
    destroyStack(&doubleStack);
    destroyStack(&stringStack);
    destroyStack(&studentStack);
}
void demonstrateQueueTemplates() {
    cout << "\n====================================================\n";
    cout << "  QUEUE TEMPLATE DEMONSTRATIONS\n";
    cout << "====================================================\n\n";
    cout << "1. Queue<int> - Integer Queue:\n";
    Queue<int> intQueue;
    initQueue(&intQueue);
    enqueue(&intQueue, 100);
    enqueue(&intQueue, 200);
    enqueue(&intQueue, 300);
    displayQueue(&intQueue);
    cout << "   Dequeued: " << dequeue(&intQueue) << endl;
    displayQueue(&intQueue);
    cout << "\n2. Queue<char> - Character Queue:\n";
    Queue<char> charQueue;
    initQueue(&charQueue);
    enqueue(&charQueue, 'A');
    enqueue(&charQueue, 'B');
    enqueue(&charQueue, 'C');
    displayQueue(&charQueue);
    cout << "   Front: " << frontElement(&charQueue) << endl;
    cout << "\n3. Queue<string> - String Queue:\n";
    Queue<string> stringQueue;
    initQueue(&stringQueue);
    enqueue(&stringQueue, string("First"));
    enqueue(&stringQueue, string("Second"));
    enqueue(&stringQueue, string("Third"));
    displayQueue(&stringQueue);
    cout << "\n4. Queue<Student> - Custom Type Queue:\n";
    Queue<Student> studentQueue;
    initQueue(&studentQueue);
    Student s1 = {"Diana", 201, 3.7};
    Student s2 = {"Eve", 202, 3.85};
    Student s3 = {"Frank", 203, 3.75};
    enqueue(&studentQueue, s1);
    enqueue(&studentQueue, s2);
    enqueue(&studentQueue, s3);
    displayQueue(&studentQueue);
    cout << "   Dequeued: " << dequeue(&studentQueue) << endl;
    displayQueue(&studentQueue);
    destroyQueue(&intQueue);
    destroyQueue(&charQueue);
    destroyQueue(&stringQueue);
    destroyQueue(&studentQueue);
}
template <>
void displayStack<bool>(Stack<bool>* stack) {
    if (isStackEmpty(stack)) {
        cout << "Stack is empty" << endl;
        return;
    }
    cout << "Bool Stack (top to bottom): ";
    StackNode<bool>* current = stack->top;
    while (current != nullptr) {
        cout << (current->data ? "true" : "false") << " ";
        current = current->next;
    }
    cout << endl;
}
void demonstrateSpecialization() {
    cout << "\n====================================================\n";
    cout << "  TEMPLATE SPECIALIZATION EXAMPLE\n";
    cout << "====================================================\n\n";
    cout << "Stack<bool> with specialized display:\n";
    Stack<bool> boolStack;
    initStack(&boolStack);
    push(&boolStack, true);
    push(&boolStack, false);
    push(&boolStack, true);
    displayStack(&boolStack);  
    destroyStack(&boolStack);
}
void demonstrateApplication() {
    cout << "\n====================================================\n";
    cout << "  APPLICATION: Reverse Polish Notation Calculator\n";
    cout << "====================================================\n\n";
    Stack<int> calcStack;
    initStack(&calcStack);
    cout << "RPN Expression: 5 3 + 2 *\n";
    cout << "Calculation steps:\n";
    push(&calcStack, 5);
    cout << "  Push 5: ";
    displayStack(&calcStack);
    push(&calcStack, 3);
    cout << "  Push 3: ";
    displayStack(&calcStack);
    int b = pop(&calcStack);
    int a = pop(&calcStack);
    push(&calcStack, a + b);
    cout << "  Operator +: pop " << b << " and " << a << ", push " << (a+b) << ": ";
    displayStack(&calcStack);
    push(&calcStack, 2);
    cout << "  Push 2: ";
    displayStack(&calcStack);
    b = pop(&calcStack);
    a = pop(&calcStack);
    push(&calcStack, a * b);
    cout << "  Operator *: pop " << b << " and " << a << ", push " << (a*b) << ": ";
    displayStack(&calcStack);
    cout << "\nResult: " << pop(&calcStack) << endl;
    destroyStack(&calcStack);
}
int main() {
    cout << "========================================================\n";
    cout << "  TASK 3: UTILIZING TEMPLATES ON STACK AND QUEUE\n";
    cout << "========================================================\n";
    demonstrateStackTemplates();
    demonstrateQueueTemplates();
    demonstrateSpecialization();
    demonstrateApplication();
    cout << "\n========================================================\n";
    cout << "  Template demonstrations completed!\n";
    cout << "========================================================\n\n";
    return 0;
}

#include <iostream>
using namespace std;

int main() {
    
    int stackVar = 10;
    
    int* heapVar = new int(20);  
    cout << "Heap variable value: " << *heapVar << endl;
    delete heapVar;  
    
    cout << "\n=== SINGLE VARIABLE ALLOCATION ===" << endl;
    
    int* ptr = new int;    
    *ptr = 42;
    cout << "Allocated int: " << *ptr << endl;
    delete ptr;           
    
    int* ptr2 = new int(100); 
    cout << "Initialized int: " << *ptr2 << endl;
    delete ptr2;
    
    cout << "\n=== DYNAMIC ARRAY ALLOCATION ===" << endl;
    
    int size;
    cout << "Enter array size: ";
    cin >> size;
    
    
    int* dynamicArray = new int[size];
    
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 10;
    }
    
    cout << "Dynamic array contents: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    delete[] dynamicArray;
    

    cout << "\n=== 2D DYNAMIC ARRAY ===" << endl;
    
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    
    int counter = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = counter++;
        }
    }
    
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];  
    }
    delete[] matrix; 
    

    cout << "\n=== MEMORY LEAK EXAMPLE ===" << endl;
    
    for (int i = 0; i < 3; i++) {
        int* leak = new int(i);
        cout << "Allocated: " << *leak << endl;
    }
    
    for (int i = 0; i < 3; i++) {
        int* noLeak = new int(i);
        cout << "Allocated and cleaned: " << *noLeak << endl;
    }
    
    cout << "\n=== DANGLING POINTER DANGER ===" << endl;
    
    int* ptr3 = new int(50);
    cout << "Value: " << *ptr3 << endl;
    delete ptr3;
    
    
    if (ptr3 != nullptr) {
        cout << "Safe to use" << endl;
    } else {
        cout << "Pointer is null - don't dereference" << endl;
    }
    
    return 0;
}

CRITICAL MEMORY RULES:

1. EVERY 'new' MUST HAVE A 'delete'
   new int      →  delete ptr
   new int[10]  →  delete[] ptr

2. STACK vs HEAP:
   Stack: Fast, automatic, limited size (~1-8 MB)
   Heap: Slower, manual, large size (GBs available)

3. WHEN TO USE HEAP:
   - Size unknown at compile time
   - Need data to outlive current scope
   - Large data structures (arrays, trees, etc.)
   - Implementing DSA structures

4. COMMON ERRORS:
   - Memory leak: Allocating without deleting
   - Dangling pointer: Using pointer after delete
   - Double delete: Deleting same memory twice
   - delete vs delete[]: Using wrong one

WHY THIS MATTERS FOR DSA:

Linked List Node:
   struct Node {
       int data;
       Node* next;
   };

Dynamic Array (like vector implementation):
   - Start with small capacity
   - Allocate larger array when needed
   - Copy data to new array
   - Delete old array

Binary Tree:
   - Each node allocated dynamically
   - Recursive deletion needed for cleanup

Graph:
   - Adjacency lists with dynamic arrays
   - Nodes in heap for flexibility

PYTHON COMPARISON:
Python: list = [1, 2, 3]  # Automatic memory management

The power (and responsibility) is yours!
*/
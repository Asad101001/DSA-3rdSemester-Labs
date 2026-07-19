
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
using namespace std;


void demonstrateArrays() {
    cout << "=== ARRAYS ===" << endl;

    int arr[5] = {1, 2, 3, 4, 5};

    cout << "Array elements: ";
    for(int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Vector after adding 6: ";
    for(int num : vec) {
        cout << num << " ";
    }
    cout << endl << endl;
}


struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void demonstrateLinkedList() {
    cout << "=== LINKED LISTS ===" << endl;

    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    cout << "Linked list: ";
    Node* current = head;
    while(current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    list<int> myList = {1, 2, 3};
    myList.push_back(4);
    cout << "std::list: ";
    for(int num : myList) {
        cout << num << " ";
    }
    cout << endl << endl;

    delete head->next->next;
    delete head->next;
    delete head;
}


void demonstrateStack() {
    cout << "=== STACKS ===" << endl;

    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Stack top: " << s.top() << endl;
    s.pop();
    cout << "After pop, top: " << s.top() << endl;

    cout << "Manual stack operations: ";
    vector<int> manualStack;
    manualStack.push_back(1);
    manualStack.push_back(2);
    manualStack.push_back(3);
    cout << "Top: " << manualStack.back() << endl;
    manualStack.pop_back();
    cout << "After pop, top: " << manualStack.back() << endl << endl;
}


void demonstrateQueue() {
    cout << "=== QUEUES ===" << endl;

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "Queue front: " << q.front() << endl;
    q.pop();
    cout << "After dequeue, front: " << q.front() << endl;

    cout << "Manual queue operations: ";
    deque<int> manualQueue;
    manualQueue.push_back(1);
    manualQueue.push_back(2);
    manualQueue.push_back(3);
    cout << "Front: " << manualQueue.front() << endl;
    manualQueue.pop_front();
    cout << "After dequeue, front: " << manualQueue.front() << endl << endl;
}


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; i++) {
        int minIdx = i;
        for(int j = i+1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void demonstrateSorting() {
    cout << "=== SORTING ALGORITHMS ===" << endl;

    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array: ";
    for(int num : arr) cout << num << " ";
    cout << endl;

    vector<int> bubbleArr = arr;
    bubbleSort(bubbleArr);
    cout << "Bubble Sort: ";
    for(int num : bubbleArr) cout << num << " ";
    cout << endl;

    vector<int> insertArr = arr;
    insertionSort(insertArr);
    cout << "Insertion Sort: ";
    for(int num : insertArr) cout << num << " ";
    cout << endl;

    vector<int> selectArr = arr;
    selectionSort(selectArr);
    cout << "Selection Sort: ";
    for(int num : selectArr) cout << num << " ";
    cout << endl << endl;
}


int linearSearch(const vector<int>& arr, int target) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == target) return i;
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        else if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void demonstrateSearching() {
    cout << "=== SEARCHING ALGORITHMS ===" << endl;

    vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;

    int linearResult = linearSearch(arr, target);
    cout << "Linear Search for " << target << ": ";
    if(linearResult != -1) cout << "Found at index " << linearResult << endl;
    else cout << "Not found" << endl;

    int binaryResult = binarySearch(arr, target);
    cout << "Binary Search for " << target << ": ";
    if(binaryResult != -1) cout << "Found at index " << binaryResult << endl;
    else cout << "Not found" << endl << endl;
}


void demonstrateTimeComplexity() {
    cout << "=== TIME COMPLEXITY BASICS ===" << endl;
    cout << "O(1): Constant time - accessing array element" << endl;
    cout << "O(log n): Logarithmic time - binary search" << endl;
    cout << "O(n): Linear time - linear search" << endl;
    cout << "O(n log n): Linearithmic time - merge sort, quick sort" << endl;
    cout << "O(n^2): Quadratic time - bubble sort, nested loops" << endl;
    cout << "O(2^n): Exponential time - recursive fibonacci without memoization" << endl;
    cout << endl;
}

int main() {
    cout << "WELCOME TO DSA CONCEPTS IN C++ FOR BEGINNERS!" << endl;
    cout << "This program demonstrates fundamental data structures and algorithms." << endl << endl;

    demonstrateArrays();
    demonstrateLinkedList();
    demonstrateStack();
    demonstrateQueue();
    demonstrateSorting();
    demonstrateSearching();
    demonstrateTimeComplexity();

    cout << "Congratulations! You've completed the DSA introduction." << endl;
    cout << "Next steps: Practice implementing these concepts, solve problems on platforms like LeetCode," << endl;
    cout << "and explore more advanced topics like trees, graphs, and dynamic programming." << endl;

    return 0;
}

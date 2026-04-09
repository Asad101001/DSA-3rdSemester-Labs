#include <iostream>
#include <stdlib.h>
using namespace std;

int arr[100];
int size = sizeof(arr) / sizeof(arr[0]);
int heapsize = 0;

int insertElement(int val){
    for (int i = 0; i < 9;i++){
        cout << "Enter the value to be entered" << endl;
        cin >> val;
        arr[i] = val;
        if (arr[i]>)
                upHeapify(i);
    }
}

void upHeapfiy(int index){
    if (i==0)
        return;

    int parent = i - 1 / 2;
    if(arr[parent]<arr[i]){
        swap(arr[parent], arr[i]);
        upHeapfiy(parent);
    }
}

void downHeapify(int index){
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;

}

void deletee(){

}

int heapSort(){
    while ()
    {
        /* code */
    }
    
}
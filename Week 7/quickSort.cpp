#include <iostream>
using namespace std;

int setPivot(int arr[], int L, int R) {
    int pivot = arr[R];      
    int i = L - 1;

    for (int j = L; j < R; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[R]);
    return i + 1;            
}

void quickSort(int arr[], int L, int R) {
    if (L < R) {
        int p = setPivot(arr, L, R);
        quickSort(arr, L, p - 1);
        quickSort(arr, p + 1, R);
    }
}

int main() {
    int array[10] = {77,82,11,54,76,57,25,98,59,101};

    quickSort(array, 0, 9);

    for (int i = 0; i < 10; i++) {
        cout << array[i] << " ";
    }
}

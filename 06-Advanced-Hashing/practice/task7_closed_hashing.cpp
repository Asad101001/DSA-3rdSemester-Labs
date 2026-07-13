#include <iostream>
using namespace std;
struct Entry {
    int data;
    int status;  
};
Entry HT[10];
int Size = 10;
void insert(int val) {
    int index = val % Size;
    int i = 0;
    while (i < Size) {
        int pos = (index + i) % Size;  
        if (HT[pos].status != 1) {  
            HT[pos].data = val;
            HT[pos].status = 1;
            cout << "Inserted " << val << " at index " << pos;
            if (i > 0) cout << " (probed " << i << " times)";
            cout << endl;
            return;
        }
        i++;
    }
    cout << "Table FULL!" << endl;
}
void search(int val) {
    int index = val % Size;
    int i = 0;
    while (i < Size) {
        int pos = (index + i) % Size;
        if (HT[pos].status == 0) {  
            cout << val << " not found" << endl;
            return;
        }
        if (HT[pos].status == 1 && HT[pos].data == val) {
            cout << "Found " << val << " at index " << pos << endl;
            return;
        }
        i++;
    }
    cout << val << " not found" << endl;
}
void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < Size; i++) {
        cout << i << ": ";
        if (HT[i].status == 1) {
            cout << HT[i].data;
        } else if (HT[i].status == 2) {
            cout << "DELETED";
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}
int main() {
    for (int i = 0; i < Size; i++) {
        HT[i].data = -1;
        HT[i].status = 0;  
    }
    cout << "=== CLOSED HASHING (OPEN ADDRESSING) ===\n\n";
    insert(3);
    insert(13);   
    insert(23);   
    insert(5);
    insert(15);   
    insert(7);
    display();
    cout << "\nSearching:\n";
    search(13);
    search(23);
    search(5);
    search(100);
    return 0;
}

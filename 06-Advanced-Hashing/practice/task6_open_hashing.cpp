#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node HT[10];      
int Size = 10;
void insert(int val) {
    int index = val % Size;  
    if (HT[index].data == -1) {
        HT[index].data = val;
    } else {
        Node* curr = new Node;
        curr->data = val;
        curr->next = HT[index].next;
        HT[index].next = curr;
    }
    cout << "Inserted " << val << " at index " << index << endl;
}
void search(int val) {
    int index = val % Size;
    if (HT[index].data == val) {
        cout << "Found " << val << " at index " << index << " (position 0)" << endl;
        return;
    }
    Node* temp = HT[index].next;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == val) {
            cout << "Found " << val << " at index " << index << " (position " << pos << ")" << endl;
            return;
        }
        temp = temp->next;
        pos++;
    }
    cout << val << " not found" << endl;
}
void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < Size; i++) {
        cout << i << ": ";
        if (HT[i].data == -1) {
            cout << "EMPTY";
        } else {
            cout << HT[i].data;
            Node* temp = HT[i].next;
            while (temp != NULL) {
                cout << "→" << temp->data;
                temp = temp->next;
            }
        }
        cout << endl;
    }
}
int main() {
    for (int i = 0; i < Size; i++) {
        HT[i].data = -1;
        HT[i].next = NULL;
    }
    cout << "=== OPEN HASHING (SEPARATE CHAINING) ===\n\n";
    insert(3);
    insert(13);   
    insert(23);   
    insert(5);
    insert(15);   
    insert(7);
    insert(27);   
    display();
    cout << "\nSearching:\n";
    search(13);
    search(5);
    search(27);
    search(100);
    return 0;
}

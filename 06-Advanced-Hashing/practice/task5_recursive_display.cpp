#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = NULL;  
void insert(int val) {
    Node* curr = new Node;
    curr->data = val;
    curr->next = NULL;
    if (head == NULL) {
        head = curr;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr;
    }
}
void displayForward(Node* node) {
    if (node == NULL) {
        return;  
    }
    cout << node->data << " ";     
    displayForward(node->next);    
}
void displayReverse(Node* node) {
    if (node == NULL) {
        return;  
    }
    displayReverse(node->next);    
    cout << node->data << " ";     
}
int main() {
    cout << "=== RECURSIVE LINKED LIST ===\n\n";
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);
    cout << "List: 10→20→30→40→50→NULL\n\n";
    displayForward(head);
    cout << endl;
    displayReverse(head);
    cout << endl;
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}

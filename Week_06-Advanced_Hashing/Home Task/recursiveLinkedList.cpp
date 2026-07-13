#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *head = NULL;

void insertElement(int value){
    Node * temp = new Node();
    temp->data = value;
    temp->next = NULL;

    if(head==NULL){
        head = temp;
    }else{
        Node *curr = head;
        while(curr->next!=NULL){
            curr = curr->next;
        }
        curr->next = temp;
    }
}

void forwardDisplay(Node * temp){
    if (temp == NULL){
        return;
    }
    cout << temp->data << " ";
    forwardDisplay(temp->next);
}

void reverseDisplay(Node * temp){
    if (temp == NULL){
        return;
    }
    reverseDisplay(temp->next);
    cout << temp->data << " ";
}

int main() {
    insertElement(10);
    insertElement(20);
    insertElement(30);
    insertElement(40);
    insertElement(50);
    
    cout << "Forward: ";
    forwardDisplay(head);
    cout << endl;
    
    cout << "Backward: ";
    reverseDisplay(head);
    cout << endl;
    
    return 0;
}
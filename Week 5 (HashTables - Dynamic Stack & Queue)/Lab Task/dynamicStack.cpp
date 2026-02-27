#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *top = NULL;

void push(int val){
    Node *temp = new Node();
    temp->data = val;
    temp->next = top;
    top = temp;
}

void pop(){
    if (top == NULL){
        cout << "Stack underflow (stack is empty)"<<endl;
        return;
    }
    Node *temp = top;
    cout << temp->data;
    cout << " has been removed from top (popped !!)" <<endl;
    top = top->next;
    delete (temp);
}

int main() {
    int choice, value;

    while (choice != 3){
        cout << "\n1. Push";
        cout << "\n2. Pop";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
    
        if (choice==1){
            cout << "Enter value"<<endl;
            cin >> value;
            push(value);   
        }
        if (choice==2){
            pop();
        }
        if (choice==3){
            break;
        }

    }

    return 0;
}
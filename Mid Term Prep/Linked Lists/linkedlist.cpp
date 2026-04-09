#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *list = NULL;

void insertElement(int val){

    Node *temp = new Node();
    temp->next = NULL;
    temp->data = val;

    if (list==NULL){
        list = temp;
    }
    else{
        Node *curr = list;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = temp;
    }
}

// void searchElement(int val){
//     if (list == NULL){
//         cout << "List is empty"<<endl;
//     }

//     Node *curr = list;
// }

void deleteElement(int val){
    if (list == NULL)
        cout << "Linked list is empty"<< endl;

    Node *curr = list;
    if(val==list->data){
        list = list->next;
        free(curr);
        return;
    }

    while(curr!=NULL){
        if(val==curr->data){
            
        }
    }
}


void displayAll(){
    Node *curr = list;
    while (curr->next != NULL)
    {
        cout << curr->data<< " - ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
}


int main() {
    int choice, val;

    while (true) {
        cout << "\n1- Insert\n2- Display\n3- Exit\n";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter value: ";
            cin >> val;
            insertElement(val);
        }
        else if (choice == 2) {
            displayAll();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
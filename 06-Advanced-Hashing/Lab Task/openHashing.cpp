#include <iostream>
using namespace std;
struct Node {
    int data;
    Node *next;
};
const int SIZE = 10;
Node HT[SIZE];
void insert(int value){
    int index = value % SIZE;
    if (HT[index].data == -1){
        HT[index].data = value;
    }else{
        Node *temp = new Node();
        temp->data = value;
        temp->next = NULL;
        Node * curr = HT[index].next;
        if (curr==NULL){
            HT[index].next = temp;
        }
        else{
            while(curr->next !=NULL){
            }
        }
    }
}
bool search(int value){
    int index = value % SIZE;
    if (HT[index].data == -1)
        return false;
    if (HT[index].data == value)
        return true;
    Node *temp = HT[index].next;
    while(temp!=NULL){
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}
void display(){
    for (int i = 0; i < SIZE;i++){
        if(HT[i].data==-1){
            cout << "Empty";
        }
        else{
            cout << HT[i].data << " ";
            Node *temp = HT[i].next;
            while(temp!=NULL){
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << "NULL";
        }
        cout << endl;
    }
}
int main(){
    for (int i = 0; i < 10; i++){
        HT[i].data = -1;
        HT[i].next = NULL;
    }
    int choice;
    do{
        cout << "\n===== MENU =====\n";
        cout << "1. Insert element\n";
        cout << "2. Search element\n";
        cout << "3. Display Hashtable\n";
        cout << "4. Exit\n";
        cout << "Enter choice:"<< endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                int val;
                cout << "Enter number: \n";
                cin >> val;
                insert(val);
                break;
            }
            case 2: {
                int val;
                cout << "Enter number to search: \n";
                cin >> val;
                if (search(val) == true){
                    cout << "Found"<<endl;
                }else{
                    cout << "Not found"<<endl;
                }
                break;
            }
            case 3: {
                display();
            }
            case 4: {
                break;
            }
            default:
                cout << "Invalid choice\n";
        }
    }while(choice!=4);
}

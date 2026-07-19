#include <iostream>
using namespace std;


struct Node{
    int data;
    Node *next;
};

Node *list = NULL;

Node *stack =NULL;

void push(int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = stack;
    stack = temp;
}

void pop() {
    if (stack == NULL) {
        cout << "Stack underflow";
        return;
    }
    Node* temp = stack;
    cout << stack->data;
    stack = stack->next;
    free(temp);

    return;
}

int count = 0;

void insert(int val){
    Node *temp = new Node;
    temp->data=val;
    temp->next=NULL;

    int index = val % 10;

    if(list=NULL){
        list = temp;
        count++;
        return;
    }
    else{
 
    Node *curr = list;
    
    while(!curr){
        curr = curr->next;
        count++;

        if (index > count){
            curr->next = temp;
        }
        else if (index < count && count % 2 == 1)
        {
            temp->next = list;
            list = temp;
        }
        else if (index < count && count % 2 == 0)
        {
            Node *last = list;
            while(last->next!=NULL){
                last = last->next;       
            }
        }
    }
}
}

void reverseDisplay(Node * root){

    Node *curr = list;

    while(!curr){
        push(curr->data);
        curr = curr->next;
    }

    while(stack->next!=NULL){
        pop();
        stack = stack->next;
    }
};

int main(){
    insert(111);
    insert(212);
    insert(767);
    reverseDisplay(list);
}
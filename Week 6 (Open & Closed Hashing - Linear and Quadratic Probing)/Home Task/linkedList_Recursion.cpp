#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node* head;

void Reverse(struct Node* p){
    if (p->next == NULL)
    {
        head = p;
        return;
    }
    Reverse(p->next);
    Node *q = p->next;
    q->next = p;
    p->next = NULL;
}

void ReversePrint(Node* p){
    if (p==NULL)
    {
        return;
    }
    ReversePrint(p->next);
    printf("%d", p->data);
}
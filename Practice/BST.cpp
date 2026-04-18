#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;
};

Node *root = NULL;

Node * insertRecursive(Node * curr , int val){

    if (curr == NULL){
        Node * temp = new Node();
        temp->data = val;
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    }
    if (val>curr->data){
        curr->right = insertRecursive(curr->right, val);
    }
    else
    {
        curr->left = insertRecursive(curr->left, val);
    }

    return curr;
}

Node * insertIterative(Node *  curr, int val){
    Node *temp = new Node();
    temp->data = val;
    temp->right = NULL;
    temp->left = NULL;

    if (curr == NULL){
        return temp;
    }

    Node *tmp = curr;
    while(tmp != NULL){
        if (tmp->data > val && tmp->left != NULL)
            tmp = tmp->left;
        else if (tmp->data<val && tmp->right !=NULL)
            tmp = tmp->right;
        else
            break;
    }

    if (tmp->data > val){
        tmp->left = temp;
    }else {
        tmp->right = temp;
    }

    return curr;
}

void PreOrder(Node *curr){
    if(curr == NULL)
        return;

    cout << curr->data << " ";
    PreOrder(curr->left);
    PreOrder(curr->right);
}

int main() {
    root = insertIterative(root,1);
    root = insertIterative(root,11);
    root =insertIterative(root,21);
    root =insertRecursive(root, 2);
    root =insertRecursive(root, 12);
    root = insertRecursive(root, 22);
    PreOrder(root);
}
#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *right;
    Node *left;
    int height;
};

Node *root = NULL;

int getHeight(Node * n){
    if(n==NULL)
        return -1;

    return n->height;
}

int max(int a , int b){
    if (a>b){
        return a;
    }
    return b;
}

Node * rotateRight(Node * r){
    Node *newRoot = r->left;
    Node *temp = newRoot->right;

    newRoot->right = r;
    r->left = temp;

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node * rotateLeft(Node * r){
    Node *newRoot = r->right;
    Node *temp = newRoot->left;

    newRoot->left = r;
    r->right = temp;

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node * insertNode(Node * r, int val){

    if(r==NULL){
            Node *temp = new Node;
            temp->data = val;
            temp->left = NULL;
            temp->right = NULL;
            temp->height = 0;
            return temp;
    }

    if(val<r->data)
        r->left = insertNode(r->left, val);
    
    else
        r->right = insertNode(r->right, val);

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;

    int balance = getHeight(r->left) - getHeight(r->right);

    if (balance > 1 && val < r->left->data)
        return rotateRight(r);
    
    if (balance < -1 && val> r->right->data)
        return rotateLeft(r);

    if (balance > 1 && val > r->left->data){
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }

    if (balance < -1 && val > r->right->data){
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;
}

Node * findMin(Node *r){
    while(r->left !=NULL){
        r = r->left;
    }
    return r;
}

Node * deleteNode(Node *r, int val){

    if (r==NULL)
        return r;


    if(val<r->data)
        r->left = deleteNode(r->left, val);

    else if(val > r->data)
        r->right = deleteNode(r->right, val);
    
    else{
        if (r->left ==NULL || r->right == NULL){
            Node *temp = findMin(r->right);
            r->data = temp->data;
            r->right = deleteNode(r->right, temp->data);
        }
    }

    r->height = max(getHeight(r->left), getHeight(r->right)) + 1;

    int balance = getHeight(r->left) - getHeight(r->right);

    if(balance > 1 && getHeight(r->left->left) >= getHeight(r->left->right))
        return rotateRight(r);

    if(balance > 1 && getHeight(r->left->left) < getHeight(r->left->right)){
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }    

    if (balance < -1 && getHeight(r->right->right) >= getHeight(r->right->left))
        return rotateLeft(r);
    
    if(balance <-1 && getHeight(r->right->right) < getHeight(r->right->left)){
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    return r;
}


void inorder(Node* r) {
    if (r != NULL) {
        inorder(r->left);
        cout << r->data << " ";
        inorder(r->right);
    }
}

int main() {
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Display\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter value: ";
                cin >> value;
                root = insertNode(root, value);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;
                root = deleteNode(root, value);
                break;

            case 3:
                cout << "Inorder: ";
                inorder(root);
                cout << endl;
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}
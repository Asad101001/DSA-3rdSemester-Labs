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
    temp->right = temp->left = NULL;

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

void InOrder(Node *curr){
    if(curr == NULL)
        return;

    InOrder(curr->left);
    cout << curr->data << " ";
    InOrder(curr->right);
}

void PostOrder(Node *curr){
    if(curr == NULL)
        return;

    PostOrder(curr->left);
    PostOrder(curr->right);
    cout << curr->data << " ";
}

bool searchRecursive(Node * curr, int val){
    if (curr==NULL){
        return false;
    }    

    if(curr->data == val){
        return true;
    }
    
    if(val>curr->data)
        return searchRecursive(curr->right, val);

    else
        return searchRecursive(curr->left, val);
}

bool searchIterative(Node * curr , int val){
    bool flag =  false;

    while(curr!=NULL){
        if(curr->data==val){
            flag = true;
            break;
        }
        else if (val>curr->data)
            curr = curr->right;
        else
            curr = curr->left;
    }

    return flag;
}





        








int main() {

    root = insertIterative(root,1);
    root = insertIterative(root,11);
    root =insertIterative(root,21);
    root =insertRecursive(root, 2);
    root =insertRecursive(root, 12);
    root = insertRecursive(root, 22);



    if(searchIterative(root,2))
    cout << "2 exists"<<endl;
    else
        cout << "2 Doesn't exist" << endl;
    
    if(searchIterative(root,69))
    cout << "69 exists"<<endl;
    else
        cout << "69 doesn't exist" << endl;    

  
    if(searchRecursive(root,21))
    cout << "21 exists"<<endl;
    else
        cout << "21 Doesn't exist" << endl;
    
    if(searchRecursive(root,67))
    cout << "67 exists"<<endl;
    else
        cout << "67 doesn't exist" << endl;


    cout << "PreOrder traversal: ";
    PreOrder(root);
    cout << endl;
    cout << "InOrder traversal: ";
    InOrder(root);
    cout << endl;
    cout << "PostOrder traversal: ";
    PostOrder(root);
    cout << endl;
}
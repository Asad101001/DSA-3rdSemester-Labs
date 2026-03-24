#include <iostream>
using namespace std;

struct AVLNode {
    int data;
    AVLNode* leftChild;
    AVLNode* rightChild;
    int height;
};

AVLNode *root = NULL;

int getHeight(AVLNode* node) {
    if (node == NULL) return -1;
    return node->height;
}

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->leftChild;
    node->leftChild = newRoot->rightChild;
    newRoot->rightChild = node;
    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild)) + 1;
    return newRoot;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->rightChild;
    node->rightChild = newRoot->leftChild;
    newRoot->leftChild = node;
    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild)) + 1;
    return newRoot;
}

AVLNode* insertNode(AVLNode* node, int value) {
    if (node == NULL) {
        AVLNode* tmp = new AVLNode();
        tmp->data = value;
        tmp->leftChild = tmp->rightChild = NULL;
        tmp->height = 0;
        return tmp;
    }

    if (value < node->data) {
        node->leftChild = insertNode(node->leftChild, value);
        if (getHeight(node->leftChild) - getHeight(node->rightChild) == 2) {
            if (value < node->leftChild->data)
                node = rotateRight(node);
            else {
                node->leftChild = rotateLeft(node->leftChild);
                node = rotateRight(node);
            }
        }
    } else {
        node->rightChild = insertNode(node->rightChild, value);
        if (getHeight(node->rightChild) - getHeight(node->leftChild) == 2) {
            if (value > node->rightChild->data)
                node = rotateLeft(node);
            else {
                node->rightChild = rotateRight(node->rightChild);
                node = rotateLeft(node);
            }
        }
    }

    node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    return node;
}

AVLNode* deleteNode(AVLNode* node, int value) {
    if (node == NULL) return node;

    if (value < node->data) {
        node->leftChild = deleteNode(node->leftChild, value);
        if (getHeight(node->rightChild) - getHeight(node->leftChild) == 2) {
            if (getHeight(node->rightChild->rightChild) >= getHeight(node->rightChild->leftChild))
                node = rotateLeft(node);
            else {
                node->rightChild = rotateRight(node->rightChild);
                node = rotateLeft(node);
            }
        }
    } else if (value > node->data) {
        node->rightChild = deleteNode(node->rightChild, value);
        if (getHeight(node->leftChild) - getHeight(node->rightChild) == 2) {
            if (getHeight(node->leftChild->leftChild) >= getHeight(node->leftChild->rightChild))
                node = rotateRight(node);
            else {
                node->leftChild = rotateLeft(node->leftChild);
                node = rotateRight(node);
            }
        }
    } else {
        if (node->leftChild == NULL || node->rightChild == NULL) {
            AVLNode* tmp;
            if (node->leftChild != NULL)
                tmp = node->leftChild;
            else
                tmp = node->rightChild;

            if (tmp == NULL) {
                delete node;
                return NULL;
            }
            *node = *tmp;
            delete tmp;
        } else {
            AVLNode* tmp = node->rightChild;
            while (tmp->leftChild) tmp = tmp->leftChild;
            node->data = tmp->data;
            node->rightChild = deleteNode(node->rightChild, tmp->data);
        }
    }

    if (node) node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
    return node;
}

void display(AVLNode* node) {
    if (node) {
        display(node->leftChild);
        cout << node->data << " ";
        display(node->rightChild);
    }
}

int main() {
    int choice, value;
    do {
        cout << "\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: "; cin >> value;
                root = insertNode(root, value);
                break;
            case 2:
                cout << "Enter value: "; cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                display(root); cout << endl;
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
#include <stdio.h>
#include <stdlib.h>
struct Node {
    float data;
    struct Node * left;
    struct Node * right;
};
void insert(struct Node ** root, float val) {
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    struct Node * queue[100];
    int front = 0;
    int rear = 0;
    queue[rear++] = *root;
    while (front < rear) {
        struct Node * temp = queue[front++];
        if (temp->left == NULL) {
            temp->left = newNode;
            return;
        } else {
            queue[rear++] = temp->left;
        }
        if (temp->right == NULL) {
            temp->right = newNode;
            return;
        } else {
            queue[rear++] = temp->right;
        }
    }
}
void mirror(struct Node * root) {
    if (root == NULL) {
        return;
    }
    struct Node * temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}
void printInOrder(struct Node * root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%.2f ", root->data);
        printInOrder(root->right);
    }
}
int main() {
    struct Node * root = NULL;
    insert(&root, 89.0);
    insert(&root, 122.0);
    insert(&root, 12.0);
    insert(&root, 75.0);
    insert(&root, 99.0);
    insert(&root, 68.0);
    printf("In-order before mirror: ");
    printInOrder(root);
    printf("\n");
    mirror(root);
    printf("In-order after mirror:  ");
    printInOrder(root);
    printf("\n");
    return 0;
}

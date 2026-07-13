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
int search(struct Node * root, float x) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == x) {
        return 1;
    }
    if (search(root->left, x) == 1) {
        return 1;
    }
    return search(root->right, x);
}
void inOrder(struct Node * root, struct Node ** arr, int * count) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left, arr, count);
    arr[*count] = root;
    *count = *count + 1;
    inOrder(root->right, arr, count);
}
void findPredSucc(struct Node * root, float x) {
    struct Node * arr[100];
    int count = 0;
    inOrder(root, arr, &count);
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (arr[i]->data == x) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Element %.2f not found.\n", x);
    } else {
        if (idx > 0) {
            printf("Predecessor of %.2f is %.2f\n", x, arr[idx - 1]->data);
        } else {
            printf("Predecessor of %.2f does not exist.\n", x);
        }
        if (idx < count - 1) {
            printf("Successor of %.2f is %.2f\n", x, arr[idx + 1]->data);
        } else {
            printf("Successor of %.2f does not exist.\n", x);
        }
    }
}
int countNodes(struct Node * root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}
int main() {
    struct Node * root = NULL;
    insert(&root, 72.0);
    insert(&root, 24.0);
    insert(&root, 19.0);
    insert(&root, 26.0);
    insert(&root, 96.0);
    printf("Search 19.0: %s\n", search(root, 19.0) ? "Found" : "Not Found");
    printf("Search 10.0: %s\n", search(root, 10.0) ? "Found" : "Not Found");
    findPredSucc(root, 72.0);
    printf("Total nodes: %d\n", countNodes(root));
    return 0;
}

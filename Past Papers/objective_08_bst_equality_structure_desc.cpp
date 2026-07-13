#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node * left;
    struct Node * right;
};
void insert(struct Node ** root, int val) {
    if (*root == NULL) {
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
        return;
    }
    if (val < (*root)->data) {
        insert(&((*root)->left), val);
    } else {
        insert(&((*root)->right), val);
    }
}
int isEqual(struct Node * tree1, struct Node * tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    if (tree1 != NULL && tree2 != NULL) {
        if (tree1->data == tree2->data) {
            if (isEqual(tree1->left, tree2->left) == 1) {
                if (isEqual(tree1->right, tree2->right) == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
int hasSameStructure(struct Node * tree1, struct Node * tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    if (tree1 != NULL && tree2 != NULL) {
        if (hasSameStructure(tree1->left, tree2->left) == 1) {
            if (hasSameStructure(tree1->right, tree2->right) == 1) {
                return 1;
            }
        }
    }
    return 0;
}
void printDescending(struct Node * root) {
    if (root != NULL) {
        printDescending(root->right);
        printf("%d ", root->data);
        printDescending(root->left);
    }
}
int main() {
    struct Node * treeA = NULL;
    struct Node * treeB = NULL;
    struct Node * treeC = NULL;
    insert(&treeA, 50);
    insert(&treeA, 30);
    insert(&treeA, 70);
    insert(&treeB, 50);
    insert(&treeB, 30);
    insert(&treeB, 70);
    insert(&treeC, 60);
    insert(&treeC, 40);
    insert(&treeC, 80);
    printf("Tree A and Tree B are equal: %s\n", isEqual(treeA, treeB) == 1 ? "Yes" : "No");
    printf("Tree A and Tree C are equal: %s\n", isEqual(treeA, treeC) == 1 ? "Yes" : "No");
    printf("Tree A and Tree C have same structure: %s\n", hasSameStructure(treeA, treeC) == 1 ? "Yes" : "No");
    printf("Tree A Nodes in Descending Order: ");
    printDescending(treeA);
    printf("\n");
    return 0;
}

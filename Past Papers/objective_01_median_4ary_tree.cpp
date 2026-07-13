#include <stdio.h>
#include <stdlib.h>

// Objective 01: 4-ary tree based on median value
// Built recursively, calculating median and splitting into 4 parts.

struct Node {
    int data;
    struct Node* child1; // S1
    struct Node* child2; // S2
    struct Node* child3; // S3
    struct Node* child4; // S4
};

// Simple bubble sort to help find median
void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the height of a specific node
int findNodeHeight(struct Node* root) {
    if (root == NULL) {
        return -1; // Conventionally height of empty tree is -1
    }
    
    int h1 = findNodeHeight(root->child1);
    int h2 = findNodeHeight(root->child2);
    int h3 = findNodeHeight(root->child3);
    int h4 = findNodeHeight(root->child4);
    
    int max1 = 0;
    if (h1 > h2) {
        max1 = h1;
    } else {
        max1 = h2;
    }
    
    int max2 = 0;
    if (h3 > h4) {
        max2 = h3;
    } else {
        max2 = h4;
    }
    
    int max = 0;
    if (max1 > max2) {
        max = max1;
    } else {
        max = max2;
    }
    
    return max + 1;
}

// Traverses the tree and prints the level and height of all nodes
void printAllNodesStats(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    
    int height = findNodeHeight(root);
    printf("Node %d: Level = %d, Height = %d\n", root->data, level, height);
    
    printAllNodesStats(root->child1, level + 1);
    printAllNodesStats(root->child2, level + 1);
    printAllNodesStats(root->child3, level + 1);
    printAllNodesStats(root->child4, level + 1);
}

// Recursive function to build the tree and print stats whenever a node is inserted
void buildTreeRec(struct Node** nodePtr, int S[], int size, struct Node** absoluteRootPtr) {
    if (size == 0) {
        return;
    }
    
    // Sort the array to find the median
    sortArray(S, size);
    
    // Find the median M
    int mid = size / 2;
    int M = S[mid];
    
    // Create new node for M
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = M;
    root->child1 = NULL;
    root->child2 = NULL;
    root->child3 = NULL;
    root->child4 = NULL;
    
    // Attach to the main tree immediately so we can print the stats
    *nodePtr = root;
    
    if (*absoluteRootPtr == NULL) {
        *absoluteRootPtr = root;
    }
    
    printf("Inserted node: %d\n", M);
    printAllNodesStats(*absoluteRootPtr, 0); 
    printf("------------------------\n");
    
    // Arrays for the 4 parts
    int S1[100], S2[100], S3[100], S4[100];
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    
    for (int i = 0; i < size; i++) {
        if (i == mid) {
            continue; // Skip the median itself
        }
        
        int x = S[i];
        
        // S1 contains numbers less than or equal to M/2
        if (x <= M / 2) {
            S1[c1] = x;
            c1++;
        } 
        // S2 contains numbers greater than M/2 and less than M
        else if (x > M / 2 && x < M) {
            S2[c2] = x;
            c2++;
        } 
        // S3 contains numbers greater than M and less than 3M/2
        else if (x > M && x < (3 * M) / 2) {
            S3[c3] = x;
            c3++;
        } 
        // S4 contains the remaining elements
        else {
            S4[c4] = x;
            c4++;
        }
    }
    
    // Recursively create the 4 subtrees
    buildTreeRec(&(root->child1), S1, c1, absoluteRootPtr);
    buildTreeRec(&(root->child2), S2, c2, absoluteRootPtr);
    buildTreeRec(&(root->child3), S3, c3, absoluteRootPtr);
    buildTreeRec(&(root->child4), S4, c4, absoluteRootPtr);
}

int main() {
    int arr[] = {22, 44, 75, 90, 92, 99, 110, 112, 125, 130, 131};
    int size = 11;
    
    struct Node* treeRoot = NULL;
    
    printf("Building 4-ary Tree...\n\n");
    buildTreeRec(&treeRoot, arr, size, &treeRoot);
    
    return 0;
}

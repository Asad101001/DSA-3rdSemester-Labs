#include <stdio.h>
#include <stdlib.h>

// Objective 05: Binary Tree with heap-like level order insertion
// String based tree with mirror, predecessor/successor, level and height.

struct Node {
    char data[100];
    struct Node* left;
    struct Node* right;
};

// Create a new node with string data
struct Node* createNode(const char* val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    int i = 0;
    while (val[i] != '\0') {
        newNode->data[i] = val[i];
        i++;
    }
    newNode->data[i] = '\0';
    
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Queue Node for level order insertion
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

// Queue structure
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, struct Node* node) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    
    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    
    struct QueueNode* temp = q->front;
    struct Node* treeNode = temp->treeNode;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return treeNode;
}

int isQueueEmpty(struct Queue* q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}

// Insert left to right like a heap using level order traversal
void insertHeapStyle(struct Node** root, const char* val) {
    struct Node* newNode = createNode(val);
    
    if (*root == NULL) {
        *root = newNode;
        return;
    }
    
    struct Queue* q = createQueue();
    enqueue(q, *root);
    
    while (isQueueEmpty(q) == 0) {
        struct Node* temp = dequeue(q);
        
        if (temp->left == NULL) {
            temp->left = newNode;
            break;
        } else {
            enqueue(q, temp->left);
        }
        
        if (temp->right == NULL) {
            temp->right = newNode;
            break;
        } else {
            enqueue(q, temp->right);
        }
    }
    
    while (isQueueEmpty(q) == 0) {
        dequeue(q);
    }
    free(q);
}

// Recursively find the mirror image (swap left and right subtrees)
void mirrorImage(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirrorImage(root->left);
    mirrorImage(root->right);
}

// Custom string comparison to avoid extra libraries
int stringsEqual(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 0;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 1;
    }
    return 0;
}

// In-order traversal to populate an array for finding predecessor and successor
void inOrderTraversal(struct Node* root, struct Node** arr, int* index) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left, arr, index);
    arr[*index] = root;
    *index = *index + 1;
    inOrderTraversal(root->right, arr, index);
}

// Given x, find predecessor and successor using in-order sequence
void findPredecessorSuccessor(struct Node* root, const char* x) {
    struct Node* arr[1000];
    int count = 0;
    inOrderTraversal(root, arr, &count);

    int foundIdx = -1;
    for (int i = 0; i < count; i++) {
        if (stringsEqual(arr[i]->data, x) == 1) {
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1) {
        printf("Element %s not found in tree.\n", x);
    } else {
        if (foundIdx > 0) {
            printf("Predecessor of %s is %s\n", x, arr[foundIdx - 1]->data);
        } else {
            printf("Predecessor of %s does not exist.\n", x);
        }
        
        if (foundIdx < count - 1) {
            printf("Successor of %s is %s\n", x, arr[foundIdx + 1]->data);
        } else {
            printf("Successor of %s does not exist.\n", x);
        }
    }
}

// Recursively find the level of a node
int findLevel(struct Node* root, const char* x, int level) {
    if (root == NULL) {
        return -1;
    }
    if (stringsEqual(root->data, x) == 1) {
        return level;
    }
    
    int leftLevel = findLevel(root->left, x, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    
    return findLevel(root->right, x, level + 1);
}

// Recursively find the height of a subtree
int findHeight(struct Node* root) {
    if (root == NULL) {
        return -1; 
    }
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// Helper to find a specific node to calculate its height
struct Node* findNode(struct Node* root, const char* x) {
    if (root == NULL) {
        return NULL;
    }
    if (stringsEqual(root->data, x) == 1) {
        return root;
    }
    
    struct Node* leftRes = findNode(root->left, x);
    if (leftRes != NULL) {
        return leftRes;
    }
    
    return findNode(root->right, x);
}

void printHeightOfNode(struct Node* root, const char* x) {
    struct Node* targetNode = findNode(root, x);
    if (targetNode == NULL) {
        printf("Node %s not found.\n", x);
    } else {
        int h = findHeight(targetNode);
        printf("Height of node %s is %d\n", x, h);
    }
}

// Traversal for testing
void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%s ", root->data);
        printInOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    
    insertHeapStyle(&root, "A");
    insertHeapStyle(&root, "B");
    insertHeapStyle(&root, "C");
    insertHeapStyle(&root, "D");
    insertHeapStyle(&root, "E");
    insertHeapStyle(&root, "F");
    
    printf("In-order before mirror: ");
    printInOrder(root);
    printf("\n");
    
    findPredecessorSuccessor(root, "B");
    
    int level = findLevel(root, "E", 0);
    printf("Level of E: %d\n", level);
    
    printHeightOfNode(root, "A");
    
    mirrorImage(root);
    printf("In-order after mirror: ");
    printInOrder(root);
    printf("\n");
    
    return 0;
}

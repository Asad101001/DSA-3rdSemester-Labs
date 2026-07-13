#include <stdio.h>
#include <stdlib.h>

// Objective 10: Doubly Linked List Operations
// 1. Insert Node, Delete Node, Print Nodes
// 2. Find Min & move it to first Node
// 3. Find Max & move it to last Node
// 4. Find total no. of Nodes
// 5. Find the middle value of the linkedlist

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void insertNode(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void deleteNode(struct Node** head, int val) {
    if (*head == NULL) {
        return;
    }

    struct Node* current = *head;
    while (current != NULL) {
        if (current->data == val) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            return;
        }
        current = current->next;
    }
}

void printNodes(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int countNodes(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count = count + 1;
        current = current->next;
    }
    return count;
}

void moveMinToFirst(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* minNode = *head;

    while (current != NULL) {
        if (current->data < minNode->data) {
            minNode = current;
        }
        current = current->next;
    }

    if (minNode == *head) {
        return;
    }

    minNode->prev->next = minNode->next;
    if (minNode->next != NULL) {
        minNode->next->prev = minNode->prev;
    }

    minNode->next = *head;
    minNode->prev = NULL;
    (*head)->prev = minNode;
    *head = minNode;
}

void moveMaxToLast(struct Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* maxNode = *head;
    struct Node* lastNode = *head;

    while (current != NULL) {
        if (current->data > maxNode->data) {
            maxNode = current;
        }
        if (current->next == NULL) {
            lastNode = current;
        }
        current = current->next;
    }

    if (maxNode == lastNode) {
        return;
    }

    if (maxNode == *head) {
        *head = maxNode->next;
        (*head)->prev = NULL;
    } else {
        maxNode->prev->next = maxNode->next;
        maxNode->next->prev = maxNode->prev;
    }

    lastNode->next = maxNode;
    maxNode->prev = lastNode;
    maxNode->next = NULL;
}

void findMiddleValue(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node* slow = head;
    struct Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    printf("Middle value is: %d\n", slow->data);
}

int main() {
    struct Node* head = NULL;
    
    insertNode(&head, 50);
    insertNode(&head, 90);
    insertNode(&head, 20);
    insertNode(&head, 70);
    insertNode(&head, 10); // Min
    insertNode(&head, 100); // Max
    insertNode(&head, 30);
    
    printf("Initial List: ");
    printNodes(head);
    
    printf("Total Nodes: %d\n", countNodes(head));
    findMiddleValue(head);
    
    moveMinToFirst(&head);
    printf("After moving Min (10) to first: ");
    printNodes(head);
    
    moveMaxToLast(&head);
    printf("After moving Max (100) to last: ");
    printNodes(head);
    
    deleteNode(&head, 70);
    printf("After deleting 70: ");
    printNodes(head);
    
    return 0;
}

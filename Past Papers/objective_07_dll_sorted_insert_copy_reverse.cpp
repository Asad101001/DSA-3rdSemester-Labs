#include <stdio.h>
#include <stdlib.h>

// Objective 06: Doubly Linked List
// 1. SortedInsert: Sort the value at the time of insertion in a list.
// 2. CopyReverse: Copy the reverse of the first list in a completely new list.

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// 1. Sorted Insert for DLL
void sortedInsert(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if ((*head)->data >= val) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL && current->next->data < val) {
        current = current->next;
    }

    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    
    current->next = newNode;
    newNode->prev = current;
}

// 2. Copy and Reverse DLL
struct Node* copyReverse(struct Node* head) {
    struct Node* newHead = NULL;
    struct Node* current = head;

    while (current != NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = current->data;
        newNode->next = NULL;
        newNode->prev = NULL;

        // Insert at beginning of new list to reverse it
        if (newHead != NULL) {
            newNode->next = newHead;
            newHead->prev = newNode;
        }
        newHead = newNode;

        current = current->next;
    }
    
    return newHead;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    
    sortedInsert(&head, 99);
    sortedInsert(&head, 22);
    sortedInsert(&head, 55);
    sortedInsert(&head, 11);
    sortedInsert(&head, 77);
    
    printf("Original DLL (Sorted Insert): ");
    printList(head);
    
    struct Node* copyReversedList = copyReverse(head);
    
    printf("Copied and Reversed DLL: ");
    printList(copyReversedList);
    
    return 0;
}

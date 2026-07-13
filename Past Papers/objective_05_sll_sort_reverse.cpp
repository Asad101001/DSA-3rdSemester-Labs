#include <stdio.h>
#include <stdlib.h>

// Objective 05: Singly Linked List
// 1. Sort the value at the time of insertion in a list.
// 2. Copy the list in a completely new list and reverse it.

struct Node {
    int data;
    struct Node* next;
};

// 1. Sorted Insert
void sortedInsert(struct Node** head, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    // If list is empty or new value is smaller than head
    if (*head == NULL || (*head)->data >= val) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Find the insertion point
    struct Node* current = *head;
    while (current->next != NULL && current->next->data < val) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// 2. Copy and reverse the list
struct Node* copyAndReverse(struct Node* head) {
    struct Node* newHead = NULL;
    struct Node* current = head;
    
    while (current != NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = current->data;
        
        // Insert at the head of the new list to naturally reverse it
        newNode->next = newHead;
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
    
    // Testing Sorted Insert
    sortedInsert(&head, 50);
    sortedInsert(&head, 20);
    sortedInsert(&head, 40);
    sortedInsert(&head, 10);
    sortedInsert(&head, 30);
    
    printf("Original List (Sorted via Insertion): ");
    printList(head);
    
    // Testing Copy and Reverse
    struct Node* reversedCopy = copyAndReverse(head);
    
    printf("Copied and Reversed List: ");
    printList(reversedCopy);
    
    return 0;
}

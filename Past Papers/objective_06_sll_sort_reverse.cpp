#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node * next;
};
void sortedInsert(struct Node ** head, int val) {
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    if (*head == NULL || (*head)->data >= val) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node * current = *head;
    while (current->next != NULL && current->next->data < val) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
struct Node * copyAndReverse(struct Node * head) {
    struct Node * newHead = NULL;
    struct Node * current = head;
    while (current != NULL) {
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = current->data;
        newNode->next = newHead;
        newHead = newNode;
        current = current->next;
    }
    return newHead;
}
void printList(struct Node * head) {
    struct Node * current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main() {
    struct Node * head = NULL;
    sortedInsert(&head, 50);
    sortedInsert(&head, 20);
    sortedInsert(&head, 40);
    sortedInsert(&head, 10);
    sortedInsert(&head, 30);
    printf("Original List (Sorted via Insertion): ");
    printList(head);
    struct Node * reversedCopy = copyAndReverse(head);
    printf("Copied and Reversed List: ");
    printList(reversedCopy);
    return 0;
}

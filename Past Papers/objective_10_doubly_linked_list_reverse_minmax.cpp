#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node * next;
    struct Node * prev;
};
void insert(struct Node ** head, int value) {
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node * temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}
void printList(struct Node * head) {
    struct Node * temp = head;
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void reverseList(struct Node ** head) {
    if (*head == NULL) {
        return;
    }
    struct Node * temp = NULL;
    struct Node * current = *head;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        *head = temp->prev;
    }
}
int findMin(struct Node * head) {
    if (head == NULL) {
        return -1; 
    }
    int min = head->data;
    struct Node * temp = head->next;
    while (temp != NULL) {
        if (temp->data < min) {
            min = temp->data;
        }
        temp = temp->next;
    }
    return min;
}
int findMax(struct Node * head) {
    if (head == NULL) {
        return -1;
    }
    int max = head->data;
    struct Node * temp = head->next;
    while (temp != NULL) {
        if (temp->data > max) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}
int main() {
    struct Node * head = NULL;
    insert(&head, 10);
    insert(&head, 25);
    insert(&head, 5);
    insert(&head, 40);
    insert(&head, 15);
    printList(head);
    printf("Min element: %d\n", findMin(head));
    printf("Max element: %d\n", findMax(head));
    printf("Reversing list...\n");
    reverseList(&head);
    printList(head);
    return 0;
}

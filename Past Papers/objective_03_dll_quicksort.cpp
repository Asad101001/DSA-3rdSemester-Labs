#include <stdio.h>
#include <stdlib.h>
struct Node {
    int index;
    int data;
    struct Node * next;
    struct Node * prev;
};
void insert(struct Node ** start, struct Node ** last, int val) {
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (*start == NULL) {
        newNode->index = 1; 
        *start = newNode;
        *last = newNode;
    } else {
        newNode->index = (*last)->index + 1;
        (*last)->next = newNode;
        newNode->prev = *last;
        *last = newNode;
    }
}
void print(struct Node * start) {
    struct Node * temp = start;
    while (temp != NULL) {
        printf("[Idx:%d | Val:%d] ", temp->index, temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void swapNodes(struct Node * a, struct Node * b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
struct Node * partition(struct Node * l, struct Node * h) {
    int pivot = h->data;
    struct Node * i = l->prev;
    for (struct Node * j = l; j != h; j = j->next) {
        if (j->data <= pivot) {
            if (i == NULL) {
                i = l;
            } else {
                i = i->next;
            }
            swapNodes(i, j);
        }
    }
    if (i == NULL) {
        i = l;
    } else {
        i = i->next;
    }
    swapNodes(i, h);
    return i;
}
void quickSort(struct Node * l, struct Node * h) {
    if (h != NULL && l != h && l != h->next) {
        struct Node * p = partition(l, h);
        quickSort(l, p->prev);
        quickSort(p->next, h);
    }
}
int main() {
    struct Node * start = NULL;
    struct Node * last = NULL;
    insert(&start, &last, 50);
    insert(&start, &last, 20);
    insert(&start, &last, 40);
    insert(&start, &last, 10);
    insert(&start, &last, 30);
    printf("List before sorting:\n");
    print(start);
    quickSort(start, last);
    printf("\nList after Quick Sort:\n");
    print(start);
    return 0;
}

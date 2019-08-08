#include<stdlib.h>
#include<stdio.h>

struct node *list_append(struct node *list1, struct node *list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    
    struct node *tail = list1;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    
    tail->next = list2;
}


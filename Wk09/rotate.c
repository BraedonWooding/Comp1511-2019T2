#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct node {
    struct node *next;
    int          data;
};

// find nth item from last in a list (return the value of that item)
// i.e. find_nth(head, 1) should return the last item of the list
// and find_nth(head, 2) should return the second last item of the list
//     find_nth(head, 5) should return the 5th last item of the list
// return -1 if out of bounds.
int find_nth_from_last(struct node *head, int nth) {
    struct node *last = NULL;
    int i = 0;
    while (i < nth) {
        if (head == last) return -1;
        struct node *cur = head;
        while (cur->next != last) {
            cur = cur->next;
        }
        last = cur;
        i++;
    }
    if (last == NULL) return -1;

    return last->data;
}

struct node *copy(struct node *head) {
    struct node *cur = head;
    struct node *new_head = NULL;
    struct node *prev_handled = NULL;
    
    while (cur != NULL) {
        struct node *new = malloc(sizeof(struct node));
        new->data = cur->data;
        new->next = NULL;
        
        if (prev_handled != NULL) {
            prev_handled->next = new;
        } else {
            new_head = new;
        }
        
        prev_handled = new;
        cur = cur->next;
    }
    
    return new_head;
}

// rotate the list around the start point, 0 <= startpoint < count(head)
// for example rotate_list(1->2->3->4, 2) = 3->4->1->2
//             rotate_list(x, 0) = x (i.e. 0 causes no change)
//             rotate_list(1->2->3->4, 1) = 2->3->4->1
//             rotate_list(1->2->3->4, 3) = 4->1->2->3
// NOTE: create a new list don't edit the original
// NOTE: this is clockwise
// NOTE: opposite way of lab
struct node *rotate_list(struct node *head, int startpoint) {
    return NULL;
}

struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;

    int i = len - 1;
    while (i >= 0) {
        struct node *tmp = malloc(sizeof(struct node));
        tmp->data = atoi(strings[i]);
        tmp->next = head;
        head = tmp;
        i--;
    }

    return head;
}

// you don't have to understand this
void list_to_string(struct node *head, char *buf) {
    // if you want to though...
    int offset = 0;
    for (struct node *cur = head; cur != NULL; cur = cur->next) {
        // sprintf, just does printf to a string
        // and we need to move our buffer along manually
        // unlike stdin which moves the 'cursor' or buffer
        // along automatically.
        offset += sprintf(buf + offset, "%d->", cur->data);
    }
    sprintf(buf + offset, "x");
    // High level Q:
    //  Can this overflow the buffer?
    //  How could we prevent this?
}

void test_find_nth_from_last(void) {
    printf("== Testing Find Nth From Last ==\n");
    char *list1[] = {"2", "2", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    assert(find_nth_from_last(head, 1) == 16);
    assert(find_nth_from_last(head, 2) == 8);
    assert(find_nth_from_last(head, 3) == 2);
    assert(find_nth_from_last(head, 4) == 2);
    assert(find_nth_from_last(head, 6) == -1);
    assert(find_nth_from_last(head, 0) == -1);
    assert(find_nth_from_last(NULL, 4) == -1);
    printf("Find Nth From Last Successful\n");
}

void test_rotate_list(void) {
    printf("== Testing Rotate List ==\n");
    char *list1[] = {"1", "2", "3", "4"};
    struct node *head = strings_to_list(4, list1);
    struct node *rotate = rotate_list(head, 0);
    char buf1[1024];
    char buf2[1024];
    list_to_string(head, buf1);
    list_to_string(rotate, buf2);
    assert(strcmp(buf1, buf2) == 0);
    rotate = rotate_list(head, 1);
    list_to_string(rotate, buf1);
    assert(strcmp(buf1, "2->3->4->1->x") == 0);
    rotate = rotate_list(head, 2);
    list_to_string(rotate, buf1);
    assert(strcmp(buf1, "3->4->1->2->x") == 0);
    rotate = rotate_list(head, 3);
    list_to_string(rotate, buf1);
    assert(strcmp(buf1, "4->1->2->3->x") == 0);
    printf("Rotate list successful\n");
}

int main(void) {
    test_find_nth_from_last();
    test_rotate_list();
}

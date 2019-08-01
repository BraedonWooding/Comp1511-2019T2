# Wk09!!!!

We are nearing the end of this trimester so its time to also have a brief look at your notes/labs/lectures to get your brain ready for exam prep.

## Malloc/Free?

What does malloc and free do?

What is wrong about the following

### 1)

```c
void print_tail(struct node *head) {
    struct node *n = malloc(sizeof(struct node));
    n = head;
    while (n->next != NULL) {
        n = n->next;
    }
    printf("%d\n", n->data);
}
```

### 2)

```c
struct node *new = malloc(sizeof(struct node *));
```

Why don't we have to malloc before set set n to head in 1)?

## Use after free

Library analogy.

- Why is this dangerous?

## Memory Leak?

What does `dcc --leak-check` do?

Other ways to find memory leaks.
- `gcc -g -o file file.c` followed by `valgrind --leak-check=full ./file` can be a bit nicer to use also you may have this installed already! (if you are on a mac)

## Joining Lists?

`struct node *list_append(struct node *list1, struct node *list2);`

Write the above function such that you join list2 to the end of list1 and return the new list.

Questions?

```c
// list1 = 1 -> 2 -> 3 -> X
// list2 = 10 -> 100 -> X
print_list(list1);
print_list(list2);
struct node *new_list = list_append(list1, list2);
print_list(new_list);
print_list(list1);
print_list(list2);
```

What is the output of above?

## Passing addresses by reference and pointer stuff

```c
void edit_ptr(struct node *node) {
    node = node->next;
}

void main(void) {
    // list1 = 1 -> 2 -> X
    printf("%d\n", list->data);
    edit_ptr(list);
    printf("%d\n", list->data);
}
```

Why does this print `1\n1\n`??  Why doesn't it print `1\n2\n`?

What about the following;

```c
void edit_ptr(struct node **node) {
    *node = (*node)->next;
}

void main(void) {
    // list1 = 1 -> 2 -> X
    printf("%d\n", list->data);
    edit_ptr(&list); // NOTE: we have to use &
    printf("%d\n", list->data);
}
```

Lucky for you this is not required for the exam and using double pointers is something reserved for us later on.  You may still find cases where they make problems easier in 1511 however :).

## Copying a linked list

```c
struct node {
    int data;
    struct node *next;
};

struct node *copy(struct node *head) {
    // How?
}
```

## Completely new way of thinking of LL problems

`struct node *set_intersection(struct node *set1, struct node *set2);`

You are given two linked lists in strictly increasing order, create the intersection which also has to be in increasing order.

Now try it for this one;

`struct node *set_union(struct node *set1, struct node *set2);`

Create the union of the above two linked lists in purely increasing order.  Each element can only occur once.

## Exam Questions

```c

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
    return NULL;
}

// rotate the list around the start point, 0 <= startpoint < count(head)
// for example rotate_list(1->2->3->4, 2) = 3->4->1->2
//             rotate_list(x, 0) = x (i.e. 0 causes no change)
//             rotate_list(1->2->3->4, 1) = 2->3->4->1
//             rotate_list(1->2->3->4, 3) = 4->1->2->3
// NOTE: create a new list don't edit the original
// NOTE: this is clockwise
// NOTE: this is the opposite way of the lab so think about how you could reverse this
struct node *rotate_list(struct node *head, int startpoint) {
    // Easiest way to prevent making an edit is just to copy it
    // We could have a slightly more clever way but this is fine.
    head = copy(head);
    // what are the cases?

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
```

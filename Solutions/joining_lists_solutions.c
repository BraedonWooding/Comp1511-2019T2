#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *new_node(int data) {
    struct node *n = malloc(sizeof(struct node));
    n->next = NULL;
    n->data = data;
    return n;
}

// howMany refers to how many elements of one list do you put before going to the next list
// for example if howMany = 1 then you take one element from each list interweaving it
// if howMany = -1 then you put all of listA then all of listB
// Examples (using array syntax to make it easier to demonstrate it but it is linked lists not arrays):
// - joinList([1, 2, 1], [3, 4, 3], -1)  ==  [1, 2, 1, 3, 4, 3]
// - joinList([1, 2, 1], [3, 4, 3], 1)   ==  [1, 3, 2, 4, 1, 3]
// - joinList([1, 2, 1], [3, 4, 3], 2)   ==  [1, 2, 3, 4, 1, 2]
// - joinList([1, 2, 1], [3, 4, 3], 3)   ==  [1, 2, 1, 3, 4, 3]
// You can presume howMany != 0 and howMany == -1 or howMany in [1, max(len(A), len(B))]
// i.e. either it is -1 or it is < the maximum length of the two lists (and not 0)
// you can also presume both lists aren't empty
struct node *join_lists(struct node *listA, struct node *listB, int howMany) {
    struct node *newHead = NULL;
    struct node *newTail = NULL;
    struct node *curA = listA;
    struct node *curB = listB;

    while (curA != NULL && curB != NULL) {
        int i = 0;
        while ((i < howMany || howMany == -1) && curA != NULL) {
            if (newTail == NULL) {
                newHead = newTail = new_node(curA->data);
            } else {
                newTail->next = new_node(curA->data);
                newTail = newTail->next;
            }
            curA = curA->next;
            i++;
        }
        // instead of having to copy and paste above we can just swap the
        // pointers of curA and curB each time
        struct node *tmp = curA;
        curA = curB;
        curB = tmp;
    }

    // add the rest of the remaining list (since only one or both of the lists
    // can be empty at this point we can just use a swapping trick)
    if (curA == NULL) {
        curA = curB;
    }

    while (curA != NULL) {
        if (newTail == NULL) {
            newHead = newTail = new_node(curA->data);
        } else {
            newTail->next = new_node(curA->data);
            newTail = newTail->next;
        }
        curA = curA->next;
    }
    return newHead;
}

// create linked list from array of strings
// This is to make tests easier;
// DO NOT USE THIS YOU DON'T HAVE TO
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i = i-1;
    }
    return head;
}

void assert_list(struct node *head, int result[], int len) {
    int i = 0;
    while (i < len) {
        assert(head != NULL);
        assert(head->data == result[i]);
        head = head->next;
        i++;
    }
    assert(head == NULL);
}

int main(void) {
    char *list1[] = {"1", "2", "1"};
    struct node *a = strings_to_list(3, list1);
    char *list2[] = {"3", "4", "3"};
    struct node *b = strings_to_list(3, list2);
    struct node *head = join_lists(a, b, -1);
    int test1[] = {1, 2, 1, 3, 4, 3};
    assert_list(head, test1, 6);
    head = join_lists(a, b, 1);
    int test2[] = {1, 3, 2, 4, 1, 3};
    assert_list(head, test2, 6);
    head = join_lists(a, b, 2);
    int test3[] = {1, 2, 3, 4, 1, 3};
    assert_list(head, test3, 6);
    head = join_lists(a, b, 3);
    int test4[] = {1, 2, 1, 3, 4, 3};
    assert_list(head, test4, 6);
    return 0;
}

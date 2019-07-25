# Exam Questions

These have been taken from previous past papers (with modifications as to ensure they won't get repeated) as well as just some I made up myself.  They all come with tests.

## Linked List Questions

NOTE NOTE: To test this you need to uncomment the test you want to run in the main function.

It'll say `Test Successful` if it passed else it should give you an error message telling you which test failed and you may get some dcc error if you do something weird with memory.

```c
// A series of linked list questions
// Base code by Elizabeth Willer
// and modified by Braedon Wooding to include unit tests and a few more questions

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

// All are around ~CR level questions unless specified
void print_list(struct node *head);
int sum_list(struct node *head);
// ~DN
struct node *find_item(struct node *head, int item);
int find_last(struct node *head);
int find_nth(struct node *head, int nth);
// ~DN
int find_nth_from_last(struct node *head, int nth);
struct node *add_last(struct node *head, int item);
struct node *remove_first(struct node *head);
struct node *remove_last(struct node *head) ;
// ~DN
struct node *remove_item(struct node *head, int item);
void free_list(struct node *head);
void test_strings(void);
void test_sum(void);
void test_find(void);
void test_find_last(void);
void test_find_nth(void);
void test_find_nth_from_last(void);
void test_add_last(void);
void test_remove_first(void);
void test_remove_last(void);
void test_remove_item(void);

int main(int argc, char *argv[]) {
    // UNCOMMENT THESE AS YOU COMPLETE THEM to test them
    //test_strings();
    //test_sum();
    //test_find();
    //test_find_last();
    //test_find_nth();
    //test_find_nth_from_last();
    //test_add_last();
    //test_remove_first();
    //test_remove_last();
    //test_remove_item();
    return 0;
}

// print linked list in python style (i.e. [1, 2, 3, 4])
void print_list(struct node *head) {
    // TODO: Write this function first!
    // This will help you write your tests!
}

// free the memory used by the linked list
void free_list(struct node *head) {
    // TODO: complete this function
    // Try doing this recursively and iteratively!  Just as a bonus exercise
}

//calculate sum of a list
// return 0 for empty list.
int sum_list(struct node *head) {
    // TODO: complete this function
    return 42;
}

//find 'item' in a list (return pointer to that item)
//return NULL if can't find item.
struct node *find_item(struct node *head, int item) {
    // TODO: complete this function
    return NULL;
}

//find last item in a list (return the value of that item)
//return -1 if empty list
int find_last(struct node *head) {
    // TODO: complete this function
    return 42;
}

// find nth item in a list (return the value of that item)
// i.e. find_nth(head, 1) should return the head of the list
// and find_nth(head, 2) should return the second item of the list (head->next)
// return -1 if out of bounds.
int find_nth(struct node *head, int nth) {
    // TODO: complete this function
    return 42;
}

// find nth item from last in a list (return the value of that item)
// i.e. find_nth(head, 1) should return the last item of the list
// and find_nth(head, 2) should return the second last item of the list
//     find_nth(head, 5) should return the 5th last item of the list
// return -1 if out of bounds.
int find_nth_from_last(struct node *head, int nth) {
    // TODO: complete this function
    return 42;
}

//add item at the end of the list (return a pointer to the head of the list)
//if head is NULL then return the created node
struct node *add_last(struct node *head, int item) {
    // TODO: complete this function
    return NULL;

}

// remove first item from a list (return a pointer to the head of the list)
// do nothing if head is empty
// if last element return NULL;
struct node *remove_first(struct node *head) {
    // TODO: complete this function
    return NULL;
}

//remove last item from a list (return a pointer to the head of the list)
//do nothing if head is empty
//if last element return null
struct node *remove_last(struct node *head) {
    // TODO: complete this function
    return NULL;
}

// remove all items with value given (item) (say 25) from a list
// (return a pointer to the head of the list)
// do nothing if can't find item.
// i.e. 2 -> 2 -> 5, remove_item(head, 2) gives us 5
struct node *remove_item(struct node *head, int item) {
    // TODO: complete this function
    return NULL;

}

// create linked list from array of strings
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

void test_strings(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Strings ==\n");
    char *list1[] = {"2", "4", "8", "16"};
    struct node *head1 = strings_to_list(4, list1);
    print_list(head1);
    free_list(head1);
    char *list2[] = {"1", "2", "3", "4"};
    struct node *head2 = strings_to_list(4, list2);
    print_list(head2);
    free_list(head2);
    printf("Print Successful\n");
}

void test_sum(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Sum ==\n");
    char *list1[] = {"2", "4", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    assert(sum_list(head) == 30);
    free_list(head);
    char *list2[] = {"1", "2", "3", "4"};
    head = strings_to_list(4, list2);
    assert(sum_list(head) == 10);
    free_list(head);
    assert(sum_list(NULL) == 0);
    printf("Sum Successful\n");
}

void test_find(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Find ==\n");
    char *list1[] = {"2", "2", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    assert(find_item(head, 2)->data == 2);
    assert(find_item(head, 12) == NULL);
    assert(find_item(head, 2) == head);
    assert(find_item(NULL, 1) == NULL);
    free_list(head);
    printf("Find Successful\n");
}

void test_find_last(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Find Last ==\n");
    char *list1[] = {"2", "2", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    assert(find_last(head) == 16);
    assert(find_last(NULL) == -1);
    free_list(head);
    printf("Find Last Successful\n");
}

void test_find_nth(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Find Nth ==\n");
    char *list1[] = {"2", "2", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    assert(find_nth(head, 2) == 2);
    assert(find_nth(head, 12) == -1);
    assert(find_nth(head, 1) == 2);
    assert(find_nth(NULL, 1) == -1);
    free_list(head);
    printf("Find Nth Successful\n");
}

void test_find_nth_from_last(void) {
    // TODO: Write some test cases for your functions
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
    free_list(head);
    printf("Find Nth From Last Successful\n");
}

void test_add_last(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Add Last ==\n");
    char *list1[] = {"2", "2", "8", "16"};
    struct node *head = strings_to_list(4, list1);
    head = add_last(head, 2);
    assert(head->next->next->next->next != NULL);
    assert(head->next->next->next->next->data == 2);
    free_list(head);
    head = add_last(NULL, 1);
    assert(head != NULL);
    assert(head->data == 1);
    free_list(head);
    printf("Add Last Successful\n");
}

void test_remove_first(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Remove First ==\n");
    char *list1[] = {"2", "5", "3"};
    struct node *head = strings_to_list(3, list1);
    head = remove_first(head);
    assert(head != NULL && head->data == 5);
    head = remove_first(head);
    assert(head != NULL && head->data == 3);
    head = remove_first(head);
    assert(head == NULL);
    head = remove_first(head);
    assert(head == NULL);
    printf("Remove first Successful\n");
}

void test_remove_last(void) {
    // TODO: Write some test cases for your functions
    printf("== Testing Remove Last ==\n");
    char *list1[] = {"2", "5", "3"};
    struct node *head = strings_to_list(3, list1);
    head = remove_last(head);
    assert(head != NULL && head->next != NULL &&
           head->next->next == NULL && head->next->data == 5 && head->data == 2);
    head = remove_last(head);
    assert(head != NULL && head->next == NULL && head->data == 2);
    head = remove_last(head);
    assert(head == NULL);
    head = remove_last(head);
    assert(head == NULL);
    printf("Remove Last Successful\n");
}

void test_remove_item(void) {
     // TODO: Write some test cases for your functions
    printf("== Testing Remove Item ==\n");
    char *list1[] = {"2", "5", "3", "7"};
    struct node *head = strings_to_list(4, list1);
    head = remove_item(head, 0);
    assert(head != NULL                   && head->data == 2);
    assert(head->next != NULL             && head->next->data == 5);
    assert(head->next->next != NULL       && head->next->next->data == 3);
    assert(head->next->next->next != NULL && head->next->next->next->data == 7);
    assert(head->next->next->next->next == NULL);

    head = remove_item(head, 2);
    assert(head != NULL             && head->data == 5);
    assert(head->next != NULL       && head->next->data == 3);
    assert(head->next->next != NULL && head->next->next->data == 7);
    assert(head->next->next->next == NULL);

    head = remove_item(head, 3);
    assert(head != NULL             && head->data == 5);
    assert(head->next != NULL       && head->next->data == 7);
    assert(head->next->next == NULL);

    head = remove_item(head, 7);
    assert(head != NULL && head->data == 5);
    assert(head->next == NULL);

    head = remove_item(head, 5);
    assert(head == NULL);
    head = remove_item(head, 0);
    assert(head == NULL);

    char *list2[] = {"2", "2", "5"};
    head = strings_to_list(3, list2);
    head = remove_item(head, 2);
    assert(head->data == 5);
    assert(head->next == NULL);
    free_list(head);
    printf("Remove Item Successful\n");
}
```

### Joining Lists (a harder linked list Q)

Sometimes we want to join lists together and sometimes we want to interweave them, your job is to build something that does exactly that. Note: you can't edit the original lists

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

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
    return NULL; // @TODO
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
```

## Array Questions

### Counting Peaks

```c
#include <assert.h>
#include <stdlib.h>

/*
    Count the number of peaks in the array
    Where a peak is a number where on the left is a lower number
      and on the right is also a lower number
    For example for array [1, 2, 1] there is 1 peak
    for array [1, 2, 5, 9, 4, 7, 3] there are 2 peaks (9, and 7)
*/
int countPeaks(int array[], int size) {
    return 42;
}

int main(void) {
    int a[] = {1, 2, 1};
    assert(countPeaks(a, 3) == 1);
    int b[] = {1, 2, 5, 9, 4, 7, 3};
    assert(countPeaks(b, 7) == 2);
    assert(countPeaks(NULL, 0) == 0);
    int c[] = {1, 2, 2, 3, 4};
    assert(countPeaks(c, 5) == 0);
    return 0;
}
```

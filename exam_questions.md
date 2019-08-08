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

## Stacks and Queues

These are pretty easy problems so I won't add many tests.  Try to test them for yourself!

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

struct stack {
    struct node *top;
};

void test_push(void);
void test_pop(void);
void test_pop_while(void);

int main(void) {
    test_push();
    test_pop();
    test_pop_while();
}

struct node *new_node(int data) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp->next = NULL;
    tmp->data = data;
    return tmp;
}

// add a new item to the top of the stack
void push(struct stack *stack, int data) {
    // REPLACE with your code
    fprintf(stderr, "push not completed\n");
}

// remove the top element from the stack
int pop(struct stack *stack) {
    // REPLACE with your code
    fprintf(stderr, "pop not completed\n");
}

// pop while the data == condition
void pop_while(struct stack *stack, int condition) {
    // REPLACE with your code
    fprintf(stderr, "PopWhile not completed\n");
}

// helper function, don't use this!
struct stack new_stack(int *data, int len) {
    struct stack stack = {0};
    if (len == 0) return stack;
    stack.top = new_node(data[0]);
    for (int i = 1; i < len; i++) {
        struct node *tmp = new_node(data[i]);
        tmp->next = stack.top;
        stack.top = tmp;
    }
    return stack;
}

// helper function don't use this!
void check_stack(struct stack stack, int *data, int len) {
    int i = 0;
    for (struct node *cur = stack.top; cur != NULL; cur = cur->next) {
        assert(cur->data == data[len - 1 - i]);
        i++;
    }
}

void test_push(void) {
    struct stack a = {0};
    push(&a, 2);
    check_stack(a, (int[]){2}, 1);
    int data[101] = {2};
    for (int i = 0; i < 100; i++) {
        push(&a, i * 10);
        data[i + 1] = i * 10;
        check_stack(a, data, i + 2);
    }
}

void test_pop(void) {
    int data[101] = {2};
    for (int i = 0; i < 100; i++) {
        data[i + 1] = i * 10;
    }
    struct stack a = new_stack(data, 101);
    for (int i = 99; i >= 0; i--) {
        assert(pop(&a) == i * 10);
    }
    assert(pop(&a) == 2);
}

void test_pop_while(void) {
    struct stack a = new_stack((int[]){1, 2, 2, 2, 2}, 5);
    pop_while(&a, 2);
    assert(a.top->data == 1 && a.top->next == NULL);
}
```

## Building your own calculator! (Interesting DN - HD level question)

>> Originally thought it was around a HD question, after implementing it I realised it was probably only a DN (or lower HD level question).  Still a very good one.

You are going to be building your own postfix calculator!  It is a tad easier than it seems but let's go over what postfix is...

Typically you would have an expression like `9 + 5 * (2 + 4) = (9 + (5 * (2 + 4))) = (9 + (5 * 6)) = (9 + 30) = 39` however in postfix we basically flip it around so that we put the operator (`+`, `-`, `/`, and `*` are the only ones you have to support) is after the numbers i.e. the above expression in postfix is; `9 5 2 4 + * +` however another way we can express it is `2 4 + 5 * 9 +` (though that actually is `(2 + 4) * 5 + 9` note how it swaps it around).

A slightly more complicated example; `2 * 1 + (5 * 3) + 10 = 27` in postfix is `2 1 * 5 3 * + 10 +`.

If you are still struggling to understand think of it this way; every time you read `*` you pop two values off the front and the push the result of the operator.  For example in the `2 1 * 5 3 * + 10 +` example above it pushes the `2` and `1` reads the `*` pops the top two numbers (`2` and `1`) multiplies them for a result of `2` pushes it ontop, pushes the `5` and `3` then reads the `*` which means it pushes `15` onto the stack then reads the `+` so it pops the `15` and the `2` (from before and in this order) and then pushes `17` onto the stack it then pushes `10` onto the stack, reads `+` and pops both `10` and `17` adds them and pushes `27` onto the stack.  At the end the top value will be the result i.e. `27`.

So you don't have to convert between the two all you have to do is read in the postfix notation and print out the result!  You don't have to handle anything but integers (no doubles) `+`, `-`, `*`, `/` (use integer division) and that is it!  Though do ignore all whitespace.  You can also presume all input is going to be valid.

For the sake of tests I'll pass it in as a string but normally in the exam it would have to be read in from stdin.

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ADD_OP   ('+')
#define DIV_OP   ('/')
#define SUB_OP   ('-')
#define MUL_OP   ('*')

/*
    Hints:
    - Try to break it down, ignore the whitespace and see if the character is a digit or a operator.
    - Use a stack!
    - Note that in postfix you either are going to be pushing or popping
    - There will never be any negative integers (think about why)
    - Don't worry about an empty string or handling errors, you will always be given a valid input
    - No podmas or bodmas or pemdas or whatever just do it left -> right.
*/

int postfix_calculator(char *input);

int main(void) {
    assert(postfix_calculator("2 1 * 5 3 * + 10 +") == 27);
    assert(postfix_calculator("2") == 2);
    assert(postfix_calculator("5 2 / 3 +") == 5);
    assert(postfix_calculator("9 5 2 4 + * +") == 39);
    assert(postfix_calculator("2 4 + 5 * 9 +") == 39);
}

int postfix_calculator(char *input) {
    // @TODO
    return 42;
}
```

The exam version of this question would to read in from standard input and you would have to support things like PI, E and other constants.

Try to do floating point as an interesting change to make it a tad harder.

## Chess moves involving taking a piece (HD ish - maybe a tad bit easier than a normal HD question)

Given a chess board return how many moves the given player can make that involve taking a piece examples in the main function...  Note: you can ignore checkmate for the sake of taking pieces (though including it is a nice extension).

NOTE: uncomment the asserts in main function if you are doing the unique.

```c
#include <stdlib.h>
#include <assert.h>

#define NO_PIECE        (0)
#define WHITE_PAWN      (1)
#define BLACK_PAWN      (-1)
#define WHITE_ROOK      (2)
#define BLACK_ROOK      (-2)
#define WHITE_BISHOP    (3)
#define BLACK_BISHOP    (-3)
#define WHITE_KING      (4)
#define BLACK_KING      (-4)
#define WHITE_KNIGHT    (5)
#define BLACK_KNIGHT    (-5)
#define WHITE_QUEEN     (6)
#define BLACK_QUEEN     (-6)

#define WHITE_PLAYER    (1)
#define BLACK_PLAYER    (-1)

int countMoves(int size, int chessBoard[size][size], int player) {
    return 42; // @TODO
}

// don't include taking the same piece using different pieces (explained in main)
// MUCH harder so do countMoves first
int countUniqueMoves(int size, int chessBoard[size][size], int player) {
    return 42; // @TODO
}

int main(void) {
    /*
        For example in the 2x2 board (note: 0, 0 is bottom left; 1, 1 is top right)

        WHITE_QUEEN NO_PIECE
        BLACK_ROOK  BLACK_PAWN

        The white player has 2 pieces they can take (rook or pawn using queen) so you would return 2 for both moves and unique moves
        The black player can take the queen with either the black rook or with the pawn (presume the black starts on the 'bottom' side) so you would also return 2 moves but only 1 unique move.
    */

    int a[2][2] = { {BLACK_ROOK, WHITE_QUEEN}, {BLACK_PAWN, NO_PIECE} };
    assert(countMoves(2, a, WHITE_PLAYER) == 2);
    assert(countMoves(2, a, BLACK_PLAYER) == 2);
    // assert(countUniqueMoves(2, a, WHITE_PLAYER) == 2);
    // assert(countUniqueMoves(2, a, BLACK_PLAYER) == 1);

    /*
        WHITE_PAWN(1)   WHITE_PAWN(2)   BLACK_ROOK    WHITE_KING
        BLACK_PAWN(1)   BLACK_PAWN(2)   BLACK_KNIGHT  NO_PIECE
        NO_PIECE        WHITE_BISHOP    NO_PIECE      NO_PIECE
        WHITE_ROOK      WHITE_KNIGHT    WHITE_QUEEN   BLACK_KING

        White can take a total of 5 pieces with 13 total moves;
        - black pawn(1) with white pawn(2), white_rook, white_knight, white_bishop
        - black pawn(2) with white pawn(1)
        - black_rook with white_king
        - black_knight with white_bishop, white_queen, white_king, white_pawn(2), white_knight
        - black_king with white_queen and white_bishop
        Black can take a total of 5 pieces with 7 total moves;
        - white pawn(1) with black pawn(2) and black knight
        - white pawn(2) with black rook, black pawn(1)
        - white king with black_rook
        - white queen with black king
        - white knight with black knight
    */
    int b[4][4] = { {WHITE_ROOK, NO_PIECE, BLACK_PAWN, WHITE_PAWN},
                    {WHITE_KNIGHT, WHITE_BISHOP, BLACK_PAWN, WHITE_PAWN},
                    {WHITE_QUEEN, NO_PIECE, BLACK_KNIGHT, BLACK_ROOK},
                    {BLACK_KING, NO_PIECE, NO_PIECE, WHITE_KING} };
    assert(countMoves(4, b, WHITE_PLAYER) == 12);
    assert(countMoves(4, b, BLACK_PLAYER) == 7);
    // assert(countUniqueMoves(4, b, WHITE_PLAYER) == 5);
    // assert(countUniqueMoves(4, b, BLACK_PLAYER) == 5);
    return 0;
}
```

If you want more tests just ask I'll chuck together some more :).

## Big Int (HD level question - very hard)

NOTE: this is probably a week 9/10 question in terms of what you need to use so I wouldn't recommend attempting it yet.

A problem with integers is that they have a limited number of representable values, for example an integer with just a single byte can only have 256 unique values (either -127 to 126 or 0 to 255).  Sometimes we need to use insanely large (or big!) integers and so your question is... try to come up with a way to hold really large integers and perform arithmetic on it.

Hints:
- Think about how numbers are represented in our world (base 10) and how you could build a similar thing using arrays
- Think about what it means to do 10 + (-12) for example or in general a + b for b < 0.
- Think about cases like 000010 + 12
- Think about addition/subtraction/... digit by digit
- Think about how you can handle negative numbers
  - Look up [SMR](https://en.wikipedia.org/wiki/Signed_number_representations#Signed_magnitude_representation_(SMR)) for perhaps another hint

```c
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct _big_int_t {
    // @TODO
};

typedef struct _big_int_t *BigInt;

BigInt newBigInt(char *number);
BigInt addBigInt(BigInt a, BigInt b);
BigInt subBigInt(BigInt a, BigInt b);
BigInt mulBigInt(BigInt a, BigInt b);
void printBigInt(char *out, BigInt a);

// As a sequence of digits i.e. "12342424"
// can have a negative sign at the front i.e. "-123"
BigInt newBigInt(char *number) {
    return NULL; // @TODO
}

// return a + b;
BigInt addBigInt(BigInt a, BigInt b) {
    return NULL; // @TODO
}

// return a - b;
BigInt subBigInt(BigInt a, BigInt b) {
    return NULL; // @TODO
}

// write the big int to the buffer (presume size is large enough)
void printBigInt(char *out, BigInt a) {
    // @TODO
}

// EXTENSION (quite a bit harder)
// return a * b;
BigInt mulBigInt(BigInt a, BigInt b) {
   return NULL; // @TODO
}

int main(void) {
    // Tests
    // You may want to comment out the asserts
    // for the functions you haven't implemented yet
    char buf[1000] = {0};
    BigInt a = newBigInt("12");
    BigInt b = newBigInt("18446744073709551616");

    printBigInt(buf, a);
    assert(strcmp(buf, "12") == 0);

    printBigInt(buf, b);
    assert(strcmp(buf, "18446744073709551616") == 0);

    BigInt test1 = newBigInt("108000000");
    BigInt test2 = newBigInt("6619392");
    BigInt test3 = addBigInt(test1, test2);
    printBigInt(buf, test3);
    assert(strcmp(buf, "114619392") == 0);

    BigInt c = addBigInt(a, b);
    printBigInt(buf, c);
    assert(strcmp(buf, "18446744073709551628") == 0);

    BigInt d = subBigInt(c, a);
    printBigInt(buf, d);
    assert(strcmp(buf, "18446744073709551616") == 0);

    BigInt e = mulBigInt(a, b);
    printBigInt(buf, e);
    assert(strcmp(buf, "221360928884514619392") == 0);
    
    BigInt f = newBigInt("-12");
    printBigInt(buf, f);
    assert(strcmp(buf, "-12") == 0);

    BigInt g = addBigInt(a, f);
    printBigInt(buf, g);
    assert(strcmp(buf, "0") == 0);

    BigInt h = addBigInt(f, f);
    printBigInt(buf, h);
    assert(strcmp(buf, "-24") == 0);

    BigInt i = subBigInt(f, h);
    printBigInt(buf, i);
    assert(strcmp(buf, "12") == 0);
    
    BigInt j = mulBigInt(f, b);
    printBigInt(buf, j);
    assert(strcmp(buf, "-221360928884514619392") == 0);

    BigInt k = newBigInt("80");
    BigInt l = newBigInt("-88");
    printBigInt(buf, k);
    assert(strcmp(buf, "80") == 0);
    printBigInt(buf, l);
    assert(strcmp(buf, "-88") == 0);
    BigInt m = addBigInt(k, l);
    printBigInt(buf, m);
    assert(strcmp(buf, "-8") == 0);
    
    // NOTE: if you are confused why think about if you would want to see
    //       00000024 or just 24.  Basically just trim off all the 0's at the front
    BigInt n = newBigInt("00008");
    printBigInt(buf, n);
    assert(strcmp(buf, "8") == 0);

    return 0;
}
```

## Stacks and Queues

### Balanced Braces

Given an input string like; `(a)` determine if the braces are match you only need to handle `(`, `{`, `[`;

Examples:
- `(a]` is false
- `((a))` is true
- `{([a])}` is true
- `]a` is false
- `{}a` is true

Hint:
- Do you care about the text that isn't `{`, `}`, `[`, `]`, `(`, `)`??

```c
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int balanced(char *buf) {
    int len = strlen(buf);

    // TODO:
    return 42;
}

int main(void) {
    assert(balanced("(a]") == 0);
    assert(balanced("(a)") == 1);
    assert(balanced("[(a)]") == 1);
    assert(balanced("{(a){2}}") == 1);
    assert(balanced("{}") == 1);
    assert(balanced("") == 1);
    assert(balanced("a") == 1);
    assert(balanced("{]") == 0);
    assert(balanced("[(]") == 0);
    assert(balanced("{{}") == 0);
    // What do you think this indicates this kind of program
    // can be used for??
    assert(balanced("int main(void) { return 0; ") == 0);
    return 0;
}
```

### Simplify Directory Path (interview question asked by Amazon)

Given a unix path that is like `/home/a/./../c` output the resultant path in simplest form.

Note: you won't ever have to perform `..` on a home directory.

Examples;
- `/home/a/./../c` => `/home/c`
- `/home/` => `/home`
- `/a/q/../b/./d/../c/./` => `/a/b/c`

Hint:
- What does `./` do to a directory?
- What does the `/` on the last directory mean?
- If you viewed each operation as a sequence i.e. go to a then b then c what does `../` do that that sequence?
- There will be no spaces in the paths
- Note: will always start with a `/`

```c
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char *simplify(char *buf) {
    int len = strlen(buf);

    // @TODO:
    return "TODO";
}

int main(void) {
    // @LEAK: how do you think we could prevent this leak
    assert(strcmp(simplify("/home/a/./../c"), "/home/c") == 0);
    assert(strcmp(simplify("/home/"), "/home") == 0);
    assert(strcmp(simplify("/a/q/../b/./d/../c/./"), "/a/b/c") == 0);
    assert(strcmp(simplify("/abc"), "/abc") == 0);
    assert(strcmp(simplify("/q/./b/../"), "/q") == 0);

    return 0;
}
```


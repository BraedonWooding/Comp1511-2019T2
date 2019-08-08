# Exam Prep

Do the questions [here](exam_questions.md) the more you do the less stressed you will feel for the final exam.

For the theory questions do the questions [here](theory_questions.md)

### Ways to solve Linked List problems

1) What is the problem asking for?
2) What kind of loop do I need (if any)?
  - Where do I start
  - Where do I end
  - What if statement or logic do I need
3) Diagram of edge cases
  - Beginning, End, Middle
4) Do I need a previous pointer?

### For Example; List Append

```c
struct node {
    struct node *next;
    int          data;
};

struct node *list_append(struct node *list1, struct node *list2) {
    // @TODO:
    return NULL;
}
```

1) Asking for the the second list to be added to the end of the first list
2) I'll need a loop to find the last element of list1
  - Starting at head, ending at last element before NULL (if any), no logic inside
3) See board
  - Empty list1, empty list2 are edge cases, in these cases return the non empty list (or NULL if both are empty)
4) No I don't

Okay from that we get the following skeleton;

```c
struct node {
    struct node *next;
    int          data;
};

struct node *list_append(struct node *list1, struct node *list2) {
    // Edge cases: first or second list is empty (or both!) 
    if (list1 == NULL) {
      return list2;
    } else if (list2 == NULL) {
      return list1;
    }
    
    // starting at head
    struct node *cur = list1;
    // ending at last element before NULL
    while (cur->next != NULL) {
        cur = cur->next;
    }
    
    // And this is what is left!
    cur->next = list2;
    return list1;
}
```

See how there isn't much left!  Most of linked list code is just what we call a skeleton!

### GDB, Valgrind

GDB allows you to step through your program one line at a time!  Valgrind has slightly better memory checking (since it gives you something called a stacktrace) than --leak check.

To use both of them compile your program using gcc like; `gcc -g -o output source.c` (the only difference is `gcc -g` the -g means debug).  Then to use gdb write `gdb output -tui`, you can run your program by typing `r` followed by any command line arguments i.e. `r 1 10`.  Before you run your program you can set points to stop at (or what we call breakpoints) you do this via `b` i.e. `b main` or `b printList` (you can also give a line number).  Once it has stopped at that function/line you can use `n` to go to the next line `s` to step into functions (to follow the path) and `c` to just run as usual till it hits the next breakpoint.

To use valgrind it is; `valgrind --leak-check=full ./output` and at the end of your program it'll tell you a stacktrace of all unfreed memory allocations.

### `man`

Don't remember something just ask the manual or `man`. i.e. `man strlen`.

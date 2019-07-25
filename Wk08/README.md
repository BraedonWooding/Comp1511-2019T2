# Wk08 Pointers, Linked Lists and the new Assignment

## Linked Lists

```c
struct overall {
    struct node *start;
    struct node *end;
};

struct node {
    int data;
    struct node *next;
};
```

Look at some example visualisations.

Do you like these ?? I'll do more in the next few weeks if people like them :).

- What does overall look like in memory??
- What does the node struct look like in memory?
- What does `malloc` do?
- Write `struct node *new_node(int data);`
- Write `void insert_at_front(struct overall *o, int data);`
- Write `void insert_before_end(struct overall *o, int data);`

Since a ton of people have been worried about linked lists, I've put up some example questions using linked lists.  If you feel like you need to get some more practice with them they are probably a good place to start.

## Labs

```c
#define MAX_SPECIES_NAME_LENGTH 128
struct pod {
    struct date when;
    int how_many;
    char species[MAX_SPECIES_NAME_LENGTH];
};
```

and

```c
struct pod {
    struct pod *next;
    struct date *when;
    int how_many;
    char *species;
};
```

## Assignment 2 Castle Defence

Link is [here](https://cgi.cse.unsw.edu.au/~cs1511/19T2/assignments/ass2/index.html)


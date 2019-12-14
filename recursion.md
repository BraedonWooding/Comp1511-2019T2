# Recursion

Recursion is a very important concept in programming that can make certain problems much much easier!

A lot of the problems it can make easier are interestingly enough to do with linked lists.

Recursion is at a principle very simple but often is quite difficult to wrap your head around.  Recursion is just about repeating the same task over and over again (with slightly different parameters).

For example the classic fibonnaci example; the fibonacci sequence is represented by a piecewise function that is something like (note: I'm taking the fibonacci for n >= 0 and where fib(0) == 1, fib(1) == 1);

```c
                  { 1,                        if n <= 1    }
fib(n) : N -> N = { fib(n - 1) + fib(n - 2)   otherwise }
```

Now this may seem a little odd but think of it this way if I have the following sequence;

`1, 1, 2, 3, 5, 8, 13, ...` (which is the fibonacci sequence) it is built up from the previous two elements equal the third.  i.e. `1 + 1 == 2, 1 + 2 == 3, 2 + 3 == 5, 3 + 5 == 8, 5 + 8 == 13, ...`  So recursion is kind of working from the top down.  You work backwards!

i.e. for fibonacci in C it would look something like;

```c
int recursive_fib(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}
```

Note how it looks almost identical to the piecewise function!!

The more typical iterative form is messier and actually works bottom up!

```c
int bottom_up_fib(int n) {
    int a = 1;
    int b = 1;
    int i = 1;
    while (i < n) {
       int tmp = a + b;
       a = b;
       b = tmp;
       i++;
    }
    return b;
}
```

## Examples

Here are some examples;

```c
struct node *copy_list(struct node *head) {
    if (head == NULL) return NULL;

    struct node *n = malloc(sizeof(struct node));
    n->data = head->data;
    n->next = copy_list(head->next);
    return n;
}
```

Is much simpler than;

```c
struct node *copy_list(struct node *head) {
    if (head == NULL) return NULL;

    struct node *cur = head->next;
    struct node *copy = malloc(sizeof(struct node));
    copy->data = head->data;
    copy->next = NULL;
    struct node *copy_cur = copy;

    while (cur != NULL) {
        copy_cur->next = malloc(sizeof(struct node));
        copy_cur = copy_cur->next;
        copy_cur->next = NULL;
        copy_cur->data = cur->data;

        copy_cur = copy_cur->next;
        cur = cur->next;
    }
    return copy;
}
```

Printing a list;

```c
void print_list(struct node *head) {
    if (head == NULL) {
        printf("x\n");
    } else {
        printf("%d->", head->data);
        print_list(head->next);
    }
}
```

vs;

```c
void print_list(struct node *head) {
    struct node *cur = head;
    while (cur != NULL) {
        printf("%d->", head->data);
        cur = cur->next;
    }
    printf("x\n");
}
```

# Theory Questions

NOTE you can't use the terminal for these;

## What do these print??

If you don't know then copy and paste it into a gedit and run it!

### 1)

```c
// file.c

#include <stdio.h>

int main(int argc, char *argv[]) {
    putchar(argv[0][0]);
    printf("%d %s", argc, argv[2]);
}
```

When run like; `./file 1 boo kek`

### 2)

What is `strlen("boo")`?

What is the size of the array `char array[] = "boo"`?  Why aren't they the same

What does `strcmp("a", "b")` return?  (You can say `< 0`, `> 0`, or `= 0`)

Does malloc return initialised memory?

What is the size of the following structs (when using the CSE computers)?

>> NOTE: these questions seem to have been removed from the course this time around but its still useful for future courses but I can't say if they will/won't be in the exam.

```c
struct A {
    int a;
    int b;
    char *c;
};

struct B {
    int age;
    char *name;
    int weight;
};

struct C {
    int age;
    int weight;
    char *name;
};
```

What is the size of `char`?  What is the size of `char*`? if they are different why/why not?

How would I dynamically allocate 100 integers? i.e. `int *array = ?`

### 3)

```c
// file.c

#include <stdio.h>
#include <string.h>

int bar(int d, int k) {
    if (k < 1) {
        return d;
    }
    return foo(d - 1);
}

int foo(int c) {
    return bar(c, c / 2);
}

int main(void) {
    printf("%d\n", foo(10));
}
```

When run like; `./file`

>> Hint: Get some paper and write down the values as they change

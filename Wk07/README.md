# Pointers and Structs

Board stuff.  Time to inspect some memory yeet.

## Examples;

Create a struct that holds information about a pet;
- name
- age
- 'type' (cat, dog, ...)
- weight

When do you use `->` and when do you use `.`

i.e. for

```c
void print_age(struct pet *my_pet) {
    // is it?
    printf("%d\n", my_pet->age);
    // or...
    printf("%d\n", my_pet.age);
}

// what about for
void print_weight(struct pet my_pet) {
    // is it?
    printf("%d\n", my_pet->weight);
    // or...
    printf("%d\n", my_pet.weight);
}
```

## What does this do

```c
#include <stdio.h>

int main(void) {
    char str[10];
    str[0] = 'H';
    str[1] = 'i';
    printf("%s\n", str);
    return 0;
}
```

## What is the type of p and what is the type of q?

```
int *p, q;
```

## What will happen here;

```
int n;
int *p, *q;
p = &n;
*p = 5;
*q = 17;
q = p;
*q = 8;
```

## What is wrong with this...

This is actually probably one of the hardest things with strings!

```c
int foo(char a[]);
int bar(char *b);

int main(void) {
    char *a = "Hello";
    // is this allowed?
    a[0] = 'B';
    // what about
    char b[] = "Hello";
    a[0] = 'B';

    // what about
    a = "Hello";
    foo(a);
    bar(a);

    // or?
    char c[] = "Hello";
    foo(c);
    bar(c);

    // and finally
    foo("Hello");
    bar("Hello");
}

// what about
int foo(char a[]) {
    a[0] = 'B';
}

// or
int bar(char *b) {
    b[0] = 'B';
}
```

## String Functions

Name a few...

## Exam Like Question (This is a bit harder but I like it)

Build the following function;

```c
char *strtok(char *str, char tok, char **end);
```

Behaves like strtok (look at man / examples).

It splits up tokens based any ANY character inside sep.

For example if we give it the string "1 + 2 * 3 / 4" and the sep "+*/ " then it would split on all the tokens; `+`, `*`, `/`, ` ` and the first time we call it the string will be modified to `"1\0+ 2 * 3 / 4"` and the pointer it returns will point to the `1`.  The second time we call it we will get; `1\0\0\02\0* 3 / 4` and so on... till we get to `1\0\0\02\0\0\03\0\0\04` As our finished string!  This makes it useful to iterate separate strings.

NOTE: you are expected to edit the string in this case

```c
#include <stdio.h>
#include <string.h>

char *strtok(char **str, char *sep);

// can we edit argv??
// and more importantly should we?
int main(int argc, char *argv[]) {
    char *str = argv[1];
    if (argc != 3) {
        return 1;
    }
    while (str != null) {
        char *result = strtok(&str, argv[2]);
        if (result != null) {
            printf("%s\n", result);
        }
    }
}
```

Examples

```bash
$ ./strtok "Hello World This Is Me" " "
Hello
World
This
Is
Me
$ ./strtok "Wow//ThisIs\Cool" "/\"
Wow
ThisIs
Cool
```


# Wk05

## Assignment!!

It is due in 10 days so pleaseee start it if you haven't!!!!

## VLAB Notice

For Macintosh users, we have observed that the release version of the TigerVNC client (v1.9.0) can sometimes fail to initially connect to VLAB when using port 5920. This port is used for direct connections to VLAB from the outside world and provides an encrypted, private connection. We have seen connection failure rates of up to 20%. Once up, the connections seem fine. Other clients don't seem to be affected.

We suspect the problem is partly due to the fact that the release TigerVNC client for Macs is 32-bit and Macs now natively run 64-bit applications. Indeed, 32-bit applications will no longer work in the next generation of MacOS (Catalina).

If you are a Macintosh user and you have experienced this problem, you may want to try using a 64-bit prelease and experimental TigerVNC client. Our tests show significant improvement. However, note that this is experimental software and may or may not work for you. You can find it in the TigerVNC nightly builds repository by clicking the "here" link under Downloads on the TigerVNC web site at https://tigervnc.org/

## Arrays

- How do we declare an array of integers of size 100?
- What does index/indicies mean?
- What is the last index of the array above?

## Questions

You may not be able to do some of the following either implement them or say 'you can't do it'

- Build a function with the following prototype `int array_length(int num[])`
- Build a function with the following prototype `int test_all_initialised(int nums[])`
  - Initialised meaning it has a set value and isn't just randomly assigned one based on its location in memory
- `void print_array(int array[])` to print out all elements of an array one by one
  - If you can't write it how would you change it so you can?
- `int scanf_array(int n, int array[n])` to scanf n elements into the array

## Functions

Write a program to do the following...

```bash
$ ./occur
Enter 6 numbers: 1 3 1 3 1 9
Enter a number: 1
1 occurred 3 times in the 6 numbers read
```

Can we rewrite it to use a function?  What are the benefits of functions?

Can we rewrite it to not use an array?  If so what would we need to change?

## Swap

```c
#include <stdio.h>

int main(void) {
    int x = 10;
    int y = 4;
    printf("x is: %d, y is: %d\n", x, y);
    // TODO: Swap x and y

    return 0;
}
```

## Weird things about arrays

References...

```c
#include <stdio.h>

void bar(int x);

// why is this valid?
// should i make it `int array[n]`??
void foo(int n, int array[]);

int main(void) {
    int num = 4;
    bar(num); // what does this print?
    printf("%d\n", num); // what is the value of y?

    // what is the size of a?
    int a[] = {1, 2, 3};

    // what are the values of b
    int b[5] = {1};

    // what does the following print
    printf("%d %d %d\n", a[0], a[1], a[2]);

    foo(3, a);
    // what does the following print
    printf("%d %d %d\n", a[0], a[1], a[2]);

    return 0;
}

void bar(int x) {
    x = 2;
    printf("x is %d\n", x);

    // will the next line compile?
    // if I remove the comment?
    // printf("%d\n", num);
}

void foo(int n, int array[]) {
    int i = 0;
    while (i < n) {
        // what does this do?
        array[i] *= array[i];
        i++;
    }
}
```

## Super interesting example of C arrays

```c
#include <stdio.h>

int main(void) {
    int x;
    int a[6];

    x = 10;
    a[3 * 2] = 2 * 3 * 7;
    printf("%d\n", x);
    return 0;
}
```

What does the above print?  What should it print?

## If we have time...  Let us make our own array :O

Demo/On the board.


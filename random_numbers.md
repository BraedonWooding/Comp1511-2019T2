# Random Numbers in C

Random number generation is done through `rand()` and is quite straightforward, however it does carry a few interesting problems.

A very basic example is;

```c
#include <stdio.h>    // for printf
#include <stdlib.h>   // for rand/srand
#include <time.h>     // for getting the current time

int main(void) {
    // time(NULL) returns the current time
    // and since the current time is unique
    // this should give us unique random numbers
    srand(time(NULL));
    int x = rand(); // x in [0, RAND_MAX)
    printf("%d\n", x);
    // if we wanted between 0 and 9 (inclusive)
    printf("%d\n", rand() % 10);
    // between 10 and 20 (inclusive)
    printf("%d\n", rand() % 11 + 10);

    return 0;
}
```

You will rarely be required to use random numbers and NEVER at any level higher than above however if you were interested in making it stronger;

## Advanced Random Number Generation (not tested)

There are a few problems with the number generation and they mostly come to do with uniformality we can build a better random number generator like such;

```c
// between low and high (inclusive)
int randint(int low, int high) {
    assert(low >= 0 && high >= 0);
    assert(low <= RAND_MAX && high <= RAND_MAX);
    assert(low <= high);

    // first thing first adjust high
    // such that we can pretend its exclusive upper bound
    high++;

    // then we want to do it from [0, high - low] then adjust
    high -= low;

    // just an easy way around it for the case we want full
    // range.
    if (high - 1 == RAND_MAX) {
        return rand() + low;
    }

    // We want to chop off all the values towards the end
    // of RAND_MAX that would break our uniformality
    int end = RAND_MAX / high * high;
    // basically by doing / high * high we are
    // doing a rounding operation to a multiple of high
    // for example (10 / 3) * 3 = (3) * 3 = 9

    // And then we want to ignore all values from rand()
    // that fall above this limit.
    // Worst case from research is that this should
    // break out of the loop around 50% of the time
    int r = rand();
    while (r >= end) {
        r = rand();
    }
    // Now we can do our proper bounding
    return r % high + low;
}
```

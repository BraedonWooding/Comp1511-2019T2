# Wk03

## Variable Names

Which one of these are valid and which ones are good style.

- `int THX1138;`
- `double 2for1;`
- `int mrBean;`
- `double my space;`
- `int event_counter;`
- `double percentageWon;`
- `#define MY_FAVOURITE_NUMBER 42`
- `int ^oo^;`
- `#define _MEMLIMIT 400`
- `double return;`

## Types

- What is casting and what are types?  Why are they useful

## cm2feet.c

Using only ints.  Reminder: There are 2.54 cm in inch and 12 inch in foot.

```bash
./cm2feet
Enter your height in centimetres: 183
Your height in feet is 6
```

Would doubles be a better choice?

## range.c

Let a user enter the start, the finish and the step.

```bash
$ dcc -o range range.c
$ ./range
Enter start: 3
Enter stop: 9
Enter step: 2
3
5
7
9
```

## FizzBuzz

For all numbers from 1 to 100 (inclusive);
- If they are divisble by 3 print fizz
- If they are divisible by 5 print buzz
- If they are divisible by 3 and 5 print fizzbuzz
- Else print just the number

## Little other stuff

What does the following print;

```c
#include <stdio.h>

int main(void) {
    printf("%lf", 10 / 4);
    printf("%lf", (double)10 / 4);
    printf("%lf", 10 / 4.0);
    printf("%d", (1 > 2));
    printf("%d", (4 < 9));
    return 0;
}
```


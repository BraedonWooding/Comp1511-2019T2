# Wk02!

## Questions?

- What is a bit?
- What is a byte?
- How can we represent integers using 4 bits?
- What is a file?
- What is a directory?
- What is commonly stored inside a file and specify encoding

## Kahoot

Kahoot link [here](https://create.kahoot.it/share/week-02-tutorial-kahoot/9453e2ab-af1e-4265-8fa6-b42823203137) 

## What is wrong style wise

```c
#include <stdio.h>

int main(void) {
int x;
    printf("Enter your favourite number: ");
    scanf("%d", &x);
    if (x == 42) {
    printf("That is my favourite number too!\n");
    } else {
    printf("Agree to disagree!\n");
    }

return 0;
}
```

## Grade

Write a program that will give us a letter grade for your mark.

So FL is 0-49, PS is 50-64, CR 65-74, DN 75-84, HD 85-100.

If it is outside this range print out "ERROR"

Examples...

```bash
$ ./grade
Please enter your grade: 45
FL

$ ./grade
Please enter your grade: 98
HD
```

## Shapes!

```bash
$ ./rectangle
Please enter the width: 3
Please enter the length: 5
Area = 3 * 5 = 15

$ ./rectangle
Please enter the width: 42
Please enter the length: 42
Area = 42 * 42 = 1764
```

Can you change it to figure out the volume of a 3D rectangle?  Or perhaps the surface area of a sphere?


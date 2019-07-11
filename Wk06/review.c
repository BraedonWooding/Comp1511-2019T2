#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define BOB sqrt

int p(int a, int b) {
    return a * b;
}

int k(int a, int b, int c, int d, int e, int f, int g, int yeet) {
                    return p(a, b) + p(c, d) + p(e, f) + p(g, yeet);
}

int main(int a, char *b[]) {
int j = 0;
while (a > 1) {
j += j - j + BOB(p(atoi(b[a - 1]), atoi(b[a - 1])));
a--;
}

printf("Sum is %d\n", j);

return 1;
}



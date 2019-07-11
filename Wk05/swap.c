#include <stdio.h>

int main(void) {
    int x = 10;
    int y = 4;
    printf("x is: %d, y is: %d\n", x, y);
    // TODO: Swap x and y
    swap(x, y);

    return 0;
}

void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}


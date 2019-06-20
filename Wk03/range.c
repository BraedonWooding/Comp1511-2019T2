// Calculates range

#include <stdio.h>

int main(void) {
    int start, stop, step;
    printf("Enter start, stop, step: ");
    scanf("%d %d %d", &start, &stop, &step);
    int i = start;

    while (i <= stop) {
        printf("%d\n", i);
        i += step; // i = i + step;
    }

    return 0;
}


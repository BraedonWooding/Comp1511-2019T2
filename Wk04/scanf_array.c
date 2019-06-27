#include <stdio.h>

int main(void) {
    int i = 0;
    int sum = 0;
    int num_read = 1;
    while (num_read == 1) {
        num_read = scanf("%d", &i);
        if (num_read == 1) {
            sum += i;
        }
    }

    printf("%d\n", sum);

    // print out numbers
    return 0;
}

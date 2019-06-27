#include <stdio.h>

int main(void) {
    int numbers[6] = {5, 10, 5, 4, 3, 2};
    // sum every odd element that is the first, third, fifth, ...

    int i = 0;
    int sum = 0;
    while (i < 6) {
        sum += numbers[i];    
        i += 2;
    }    

    printf("%d\n", sum);

    // print out numbers
    return 0;
}

#include<stdio.h>

int main(void) {
    int number, other;
    scanf("%d", &number, &other);
    
    if (number == 1 && other == 0) {
        printf("ONE");
    } else {
        printf("%d", number);
    }
    
    printf(" & ");

    if (other == 1) {
        printf("ONE");
    } else {
        printf("%d", other);
    }
    
    return 0;
}

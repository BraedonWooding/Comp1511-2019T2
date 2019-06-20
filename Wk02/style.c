// Braedon Wooding & H17A Lab
// 13/6/2019
// Style Example

#include <stdio.h>

#define MY_FAVOURITE_NUMBER 42

int main(void) {
    int favourite_number;
    printf("Enter your favourite number: ");
    scanf("%d", &favourite_number);
    if (favourite_number == MY_FAVOURITE_NUMBER) {
        printf("That is my favourite number too!\n");
    } else {
        printf("Agree to disagree!\n");
    }

    return 0;
}

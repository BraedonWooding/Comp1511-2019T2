// Braedon Tute Lab H17A
// 13/6/2019
// Prints out grade

#include <stdio.h>

int main(void) {
    int grade;
    printf("Please enter your grade: ");
    scanf("%d", &grade);
    
    if (grade < 0 || grade > 100) {
        printf("ERROR");
    } else if (grade < 50) {
        printf("FL");
    } else if (grade < 65) {
        printf("PS");
    } else if (grade < 75) {
        printf("CR");
    } else if (grade < 85) {
        printf("DN");
    } else {
        printf("HD");
    }
    
    printf("\n");

    return 0;
}


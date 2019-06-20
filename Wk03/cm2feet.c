// Braedon & Tute Lab
// 20/06/2019
// Converts cm to feet

#include <stdio.h>

#define CENTIMETRES_PER_INCH (2.54)
#define INCHES_PER_FOOT (12)

int main(void) {
    int height;
    printf("Enter height in centimetres: ");
    scanf("%d", &height);
    
    int feet = height / CENTIMETRES_PER_INCH / INCHES_PER_FOOT;
    printf("Your height in feet is: %d", feet);

    return 0;
}


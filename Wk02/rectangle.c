// Braedon Tute Lab H17A
// 13/6/2019
// Dimensions of a rectangle

#include <stdio.h>

int main(void) {
    int width;
    int length;
    
    printf("Please enter the width: ");
    scanf("%d", &width);
    printf("Please enter the length: ");
    scanf("%d", &length);
    
    int area = width * length;
    printf("Area = %d * %d = %d\n", width, length, area);

    return 0;
}

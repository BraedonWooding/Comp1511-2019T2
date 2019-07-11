#include <stdio.h>

#define MAX_SIZE (6)

int scanf_array(int n, int array[n]);

int main(void) {
    int array[MAX_SIZE];
    
    printf("Enter 6 numbers: ");
    scanf_array(MAX_SIZE, array);
    
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int num_seen = 0;
    int i = 0;
    while (i < MAX_SIZE) {
        if (num == array[i]) {
            num_seen++;
        }
        i++;
    }
    
    printf("%d occurred %d times in the %d numbers read\n", num, num_seen, MAX_SIZE);
    
    return 0;
}

int scanf_array(int n, int array[n]) {
    int i = 0;
    while (i < n) {
        if (scanf("%d", &array[i]) != 1) {
            return 0;
        }
        i++;
    }
    return 1;
}


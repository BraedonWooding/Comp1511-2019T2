#include <assert.h>
#include <stdlib.h>

/*
    Count the number of peaks in the array
    Where a peak is a number where on the left is a lower number
      and on the right is also a lower number
    For example for array [1, 2, 1] there is 1 peak
    for array [1, 2, 5, 9, 4, 7, 3] there are 2 peaks (9, and 7)
*/
int countPeaks(int array[], int size) {
    int count = 0;
    int i = 1;
    while (i < size - 1) {
        if (array[i - 1] < array[i] && array[i] > array[i + 1]) {
            count++;
        }
        i++;
    }
    return count;
}

int main(void) {
    int a[] = {1, 2, 1};
    assert(countPeaks(a, 3) == 1);
    int b[] = {1, 2, 5, 9, 4, 7, 3};
    assert(countPeaks(b, 7) == 2);
    assert(countPeaks(NULL, 0) == 0);
    int c[] = {1, 2, 2, 3, 4};
    assert(countPeaks(c, 5) == 0);
    return 0;
}

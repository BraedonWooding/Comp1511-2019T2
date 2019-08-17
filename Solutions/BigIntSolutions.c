#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Explains the data struct under hints but basically we store each digit
    as a unique value in the array i.e.

    1024 => {1, 0, 2, 4}

    Then just do digit by digit addition subtraction and multiplication.

    You don't have to worry about freeing but I have just to make it a bit more
    complete.
*/

struct _big_int_t {
    int *num;
    int is_positive;
    int size;
};

typedef struct _big_int_t *BigInt;

BigInt newBigInt(char *number);
BigInt addBigInt(BigInt a, BigInt b);
BigInt subBigInt(BigInt a, BigInt b);
BigInt mulBigInt(BigInt a, BigInt b);
void printBigInt(char *out, BigInt a);
void freeBigInt(BigInt a);

// As a sequence of digits i.e. "12342424"
// can have a negative sign at the front i.e. "-123"
BigInt newBigInt(char *number) {
    if (number[0] == '-') {
        BigInt tmp = newBigInt(number + 1);
        tmp->is_positive = 0;
        return tmp;
    }

    int size = strlen(number);
    BigInt num = malloc(sizeof(struct _big_int_t));
    num->num = malloc(sizeof(int) * size);
    num->is_positive = 1;
    num->size = size;
    int i = 0;
    // note we are reading them in backwards to make later work easier
    while (i < size) {
        num->num[size - 1 - i] = number[i] - '0';
        i++;
    }
    return num;
}

// frees the big int
void freeBigInt(BigInt a) {
    free(a->num);
    free(a);
}

int realSize(BigInt a) {
    int real_size = a->size;
    while (a->num[real_size - 1] == 0) {
        real_size--;
    }
    return real_size;
}

// returns a < b
int checkSmaller(BigInt a, BigInt b) {
    // technically b could have tons of '0's to increase its size
    // so we just have to get its real size
    int real_size_a = realSize(a);
    int real_size_b = realSize(b);
    if (real_size_b > real_size_a) {
        return 1;
    } else if (real_size_a > real_size_b) {
        return 0;
    } else {
        // we can use memcmp
        // or you can cmp digit by digit
        return memcmp(a->num, b->num, real_size_a) < 0;
    }
}

// return a + b;
// Bit of a large function at 82 lines but for exams its more lenient
BigInt addBigInt(BigInt a, BigInt b) {
    // Big problems occur if b < 0 && a > 0 and a < b
    // and so to fix it we just do - (b - a) if a < b
    if (a->is_positive && b->is_positive == 0 && checkSmaller(a, b)) {
        // NOTE: you can edit the fields as long as you change them back
        //       before you return!
        b->is_positive = 1;
        a->is_positive = 0;
        BigInt tmp = addBigInt(b, a);
        tmp->is_positive = 0;
        b->is_positive = 0;
        a->is_positive = 1;
        return tmp;
    }

    BigInt num = malloc(sizeof(struct _big_int_t));
    int carry = 0;
    int modifier = 1;
    if (a->is_positive && b->is_positive == 0) {
        modifier = -1;
    } else if (a->is_positive == 0 && b->is_positive) {
        modifier = -1;
        // make sure that if a is negative then we swap it
        // just saves a bit on having a lot of conditional branches below
        // i.e. -a + b => b - a
        BigInt tmp = a;
        a = b;
        b = tmp;
    }

    int i = 0;
    int max, min;
    if (a->size > b->size) {
        max = a->size;
        min = b->size;
    } else {
        max = b->size;
        min = a->size;
    }
    num->num = malloc(sizeof(int) * (max + 1));

    while (i < min) {
        int res = a->num[i] + modifier * b->num[i] + carry;
        carry = 0;
        if (res >= 10) {
            carry = 1;
            res -= 10;
        } else if (res < 0) {
            carry = -1;
            res += 10;
        }
        num->num[i] = res;
        i++;
    }
    while (i < max) {
        int res = carry;
        carry = 0;
        if (a->size == max) {
            res += a->num[i];
        } else if (b->size == max) {
            res += b->num[i];
        }
        if (res >= 10) {
            carry = 1;
            res -= 10;
        }
        num->num[i] = res;
        i++;
    }
    if (carry) {
        num->num[i] = 1;
        i++;
        carry = 0;
    }

    // trim 0's making sure to leave one if there is only 1
    while (num->num[i - 1] == 0 && i > 1) {
        i--;
    }

    num->size = i;
    num->is_positive = a->is_positive;
    return num;
}

// return a - b;
BigInt subBigInt(BigInt a, BigInt b) {
    // a - b => a + (-b)
    b->is_positive = b->is_positive == 0;
    BigInt tmp = addBigInt(a, b);
    b->is_positive = b->is_positive == 0;
    return tmp;
}

// write the big int to the buffer (presume size is large enough)
void printBigInt(char *out, BigInt a) {
    int i = 0;
    if (a->is_positive == 0) {
        out[0] = '-';
        out++;
    }

    int end = a->size;
    // while there are 0's trim them
    // but make sure there is always atleast one
    while (a->num[end - 1] == 0 && end > 1) {
        end--;
    }

    while (i < end) {
        out[i] = a->num[end - 1 - i] + '0';
        i++;
    }
    out[i] = '\0';
}

// EXTENSION (quite a bit harder)
// return a * b;
BigInt mulBigInt(BigInt a, BigInt b) {
    BigInt num = malloc(sizeof(struct _big_int_t));
    num->num = malloc(sizeof(int));
    num->size = 1;
    num->num[0] = 0;
    num->is_positive = 1;

    int carry = 0;
    int i = 0;
    while (i < b->size) {
        int j = 0;
        BigInt tmp = malloc(sizeof(struct _big_int_t));
        tmp->size = 1000;
        tmp->num = malloc(sizeof(int) * tmp->size);
        memset(tmp->num, 0, sizeof(int) * tmp->size);
        tmp->is_positive = 1;
        int pos = 0;
        while (j < i) {
            tmp->num[pos] = 0;
            pos++;
            j++;
        }

        j = 0;
        while (j < a->size) {
            int res = a->num[j] * b->num[i] + carry;
            if (res >= 10) {
                carry = res / 10;
                res = res % 10;
            } else {
                carry = 0;
            }
            tmp->num[pos] = res;
            pos++;
            j++;
        }
        if (carry > 0) {
            tmp->num[pos] = carry;
            pos++;
            carry = 0;
        }
        tmp->size = pos;
        BigInt result = addBigInt(num, tmp);
        freeBigInt(num);
        freeBigInt(tmp);
        num = result;
        i++;
    }

    if (a->is_positive == b->is_positive) {
        // has to be positive i.e. both negative or both positive
        num->is_positive = 1;
    } else {
        // Note: this could be written as num->is_positive = a->is_positive == b->is_positive
        num->is_positive = 0;
    }

    return num;
}

int main(void) {
    printf("Doing tests for big int\n");
    // Tests
    // You may want to comment out the asserts
    // for the functions you haven't implemented yet
    char buf[1000] = {0};
    BigInt a = newBigInt("12");
    BigInt b = newBigInt("18446744073709551616");

    printBigInt(buf, a);
    assert(strcmp(buf, "12") == 0);

    printBigInt(buf, b);
    assert(strcmp(buf, "18446744073709551616") == 0);

    BigInt test1 = newBigInt("108000000");
    BigInt test2 = newBigInt("6619392");
    BigInt test3 = addBigInt(test1, test2);
    printBigInt(buf, test3);
    assert(strcmp(buf, "114619392") == 0);

    BigInt c = addBigInt(a, b);
    printBigInt(buf, c);
    assert(strcmp(buf, "18446744073709551628") == 0);

    BigInt d = subBigInt(c, a);
    printBigInt(buf, d);
    assert(strcmp(buf, "18446744073709551616") == 0);

    BigInt e = mulBigInt(a, b);
    printBigInt(buf, e);
    assert(strcmp(buf, "221360928884514619392") == 0);
    
    BigInt f = newBigInt("-12");
    printBigInt(buf, f);
    assert(strcmp(buf, "-12") == 0);

    BigInt g = addBigInt(a, f);
    printBigInt(buf, g);
    assert(strcmp(buf, "0") == 0);

    BigInt h = addBigInt(f, f);
    printBigInt(buf, h);
    assert(strcmp(buf, "-24") == 0);

    BigInt i = subBigInt(f, h);
    printBigInt(buf, i);
    assert(strcmp(buf, "12") == 0);
    
    BigInt j = mulBigInt(f, b);
    printBigInt(buf, j);
    assert(strcmp(buf, "-221360928884514619392") == 0);

    BigInt k = newBigInt("80");
    BigInt l = newBigInt("-88");
    printBigInt(buf, k);
    assert(strcmp(buf, "80") == 0);
    printBigInt(buf, l);
    assert(strcmp(buf, "-88") == 0);
    BigInt m = addBigInt(k, l);
    printBigInt(buf, m);
    assert(strcmp(buf, "-8") == 0);
    
    // NOTE: if you are confused why think about if you would want to see
    //       00000024 or just 24.  Basically just trim off all the 0's at the front
    BigInt n = newBigInt("00008");
    printBigInt(buf, n);
    assert(strcmp(buf, "8") == 0);
    
    // big free list of just all the stuff we allocated
    freeBigInt(a);
    freeBigInt(b);
    freeBigInt(c);
    freeBigInt(d);
    freeBigInt(e);
    freeBigInt(f);
    freeBigInt(g);
    freeBigInt(h);
    freeBigInt(i);
    freeBigInt(j);
    freeBigInt(k);
    freeBigInt(l);
    freeBigInt(m);
    freeBigInt(n);
    freeBigInt(test1);
    freeBigInt(test2);
    freeBigInt(test3);

    printf("Tests passed for big int!\n");
    
    return 0;
}

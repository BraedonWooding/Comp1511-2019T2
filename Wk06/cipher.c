/*
 * =====================================================================================
 *
 *       Filename:  cipher.c
 *
 *    Description:  Presents a ceasar/substituion cipher visualisation
 *
 *        Version:  1.0
 *        Created:  07/11/2019 13:42:05
 *       Revision:  none
 *       Compiler:  gcc, dcc
 *
 *         Author:  Braedon Wooding, braedonww@gmail.com
 *   Organization:  UNSW
 *
 * =====================================================================================
 */

// NOTE: The code has been written in a style and using tools
//       That students would be able to use at Wk06 content in 1511
//       The only exception is clearing via system(CLEAR);

#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_LEN (26)

// you can ignore this
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

/* Checks if the string a == b
 * NOTE: Both strings have to be valid
 *       That is terminating in a '\0'
 */
int str_equal(char a[], char b[]);

/* Prints out a help message
 */
void usage(void);

/* Copies string from source to dest
 */
void copy_str(char source[], char dest[]);

/* Substitution visualisation
 * Starting with cipher == alphabet
 */
void substitution(char alphabet[ALPHABET_LEN + 1]);

/* Caesar visualisation
 * Starting with cipher == shift
 */
void caesar(int shift);

/* Clears the terminal
 */
void clear_screen(void);

int main(int argc, char *argv[]) {
    // if they supplied no arguments or a 
    if (argc == 1 || str_equal(argv[1], "-h") || argc > 3) {
        usage();
        return 0;
    }

    if (str_equal(argv[1], "caesar")) {
        int shift = 5;
        if (argc == 3) {
            shift = atoi(argv[2]);
        }
        caesar(shift);
    } else if (str_equal(argv[1], "substitution")) {
        // +1 for \0
        char starting[ALPHABET_LEN + 1] = "qwertyuiopasdfghjklzxcvbnm";
        if (argc == 3) {
            copy_str(argv[2], starting);
        }
        substitution(starting);
    } else {
        usage();
        return 0;
    }
    return 0;
}

void caesar(int shift) {
    int res = 1;
    while (res == 1) {
        clear_screen();
        printf("a b c d e f g h i j k l m n o p q r s t u v w x y z\n");
        if (shift >= 0) {
            printf("                >> Shifting by %d >>\n", shift);
        } else {
            printf("                << Shifting by %d <<\n", shift);
        }
        int cur_char = 'a';
        while (cur_char <= 'z') {
            int ch = cur_char + shift % 26;
            if (ch > 'z') {
                ch -= 26;
            } else if (ch < 'a') {
                ch += 26;
            }
            printf("%c ", ch);
            cur_char++;
        }
        putchar('\n');
        // allow to change shift
        printf("\n\nEnter new shift: ");
        res = scanf("%d", &shift);
    }
    printf("Exiting: \n");
}

void substitution(char alphabet[ALPHABET_LEN + 1]) {
    int res = 1;
    while (res == 1) {
        clear_screen();
        printf("Alphabet: a b c d e f g h i j k l m n o p q r s t u v w x y z\n");
        printf("Cipher  : ");
        int i = 0;
        while (i < ALPHABET_LEN) {
            printf("%c ", alphabet[i]);
            i++;
        }
        putchar('\n');

        // allow them to change cipher
        printf("\n\nEnter new cipher: ");
        res = scanf("%s", alphabet);
    }
    printf("Exiting: \n");
}

void copy_str(char source[], char dest[]) {
    // presumes that dest has the storage capacity for source
    int i = 0;
    while (source[i] != '\0') {
        dest[i] = source[i];
        i++;
    }
    // make sure to copy across the '\0' as well
    dest[i] = '\0';
}

void usage(void) {
    printf("Usage for caesar: ./cipher caesar <number>\n"
           "Usage for substitution: ./cipher substitution <alphabet>\n");
    printf("`./cipher -h` prints this message\n");
    printf("Example 1: ./cipher caesar 2\n");
    printf("Example 2: ./cipher caesar\n");
    printf("Example 3: ./cipher substitution\n");
    printf("Example 4: ./cipher substitution bcdefghijklmnopqrstuvwxyza\n");
}

int str_equal(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    // make sure both strings end on a '\0'
    return a[i] == b[i];
}

void clear_screen(void) {
    // just like calling [H[2J inside a terminal
    system(CLEAR);
}


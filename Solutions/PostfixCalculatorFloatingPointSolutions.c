#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define ADD_OP   ('+')
#define DIV_OP   ('/')
#define SUB_OP   ('-')
#define MUL_OP   ('*')

/*
    This uses floats rather than ints, doesn't really change anything
    but how to parse the floats.
*/

/*
    Hints:
    - Try to break it down, ignore the whitespace and see if the character is a digit or a operator.
    - Use a stack!
    - Note that in postfix you either are going to be pushing or popping
    - Don't worry about an empty string or handling errors, you will always be given a valid input
    - No podmas or bodmas or pemdas or whatever just do it left -> right.
*/

typedef struct _node_t {
    struct _node_t *next;
    double data;
} *Node;

Node pop_stack(Node head, double *data);
Node push_stack(Node head, double data);
double postfix_calculator(char *input);

int main(void) {
    assert(postfix_calculator("2 1 * 5 3 * + 10 +") == 27);
    assert(postfix_calculator("2") == 2);
    assert(postfix_calculator("5 2 / 3 +") == 5.5);
    assert(postfix_calculator("9 5 2 4 + * +") == 39);
    assert(postfix_calculator("2 4 + 5 * 9 +") == 39);

    // NOTE: question didn't ask for this
    //       this was just so we can test it
    //       and most likely in a test they would
    //       want you to do it this way!
    // UNCOMMENT BELOW if you want to try it out manually
    /*
    printf("<<< ");
    char buf[1024];
    while (fgets(buf, 1024, stdin) != NULL) {
        printf("%lf\n", postfix_calculator(buf));
        printf("<<< ");
    }
    */
}

Node push_stack(Node head, double data) {
    Node node = malloc(sizeof(struct _node_t));
    node->next = head;
    node->data = data;
    return node;
}

Node pop_stack(Node head, double *data) {
    *data = head->data;
    Node tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

double postfix_calculator(char *input) {
    int input_len = strlen(input);
    Node stack = NULL;
    char buf[1024];

    int i = 0;
    while (i < input_len) {
        if (isspace(input[i])) {
            i++;
        } else if (input[i] == MUL_OP) {
            double second, first;
            stack = pop_stack(stack, &second);
            stack = pop_stack(stack, &first);
            stack = push_stack(stack, first * second);
            i++;
        } else if (input[i] == ADD_OP) {
            double second, first;
            stack = pop_stack(stack, &second);
            stack = pop_stack(stack, &first);
            stack = push_stack(stack, first + second);
            i++;
        } else if (input[i] == SUB_OP) {
            double second, first;
            stack = pop_stack(stack, &second);
            stack = pop_stack(stack, &first);
            stack = push_stack(stack, first - second);
            i++;
        } else if (input[i] == DIV_OP) {
            double second, first;
            stack = pop_stack(stack, &second);
            stack = pop_stack(stack, &first);
            stack = push_stack(stack, first / second);
            i++;
        } else {
            // pushing to stack
            int cur = 0;
            while ((isdigit(input[i]) || input[i] == '.') && i < input_len) {
                buf[cur] = input[i];
                i++;
                cur++;
            }
            buf[cur] = '\0';
            stack = push_stack(stack, atof(buf));
        }
    }
    double res;
    stack = pop_stack(stack, &res);
    return res;
}


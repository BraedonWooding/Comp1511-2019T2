#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

struct stack {
    struct node *top;
};

void test_push(void);
void test_pop(void);
void test_pop_while(void);

int main(void) {
    test_push();
    test_pop();
    test_pop_while();
}

struct node *new_node(int data) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp->next = NULL;
    tmp->data = data;
    return tmp;
}

// add a new item to the top of the stack
void push(struct stack *stack, int data) {
    struct node *n = new_node(data);
    n->next = stack->top;
    stack->top = n;
}

// remove the top element from the stack
int pop(struct stack *stack) {
    int data = stack->top->data;
    struct node *tmp = stack->top;
    stack->top = stack->top->next;
    free(tmp);
    return data;
}

// pop while the data == condition
void pop_while(struct stack *stack, int condition) {
    while (stack->top != NULL && stack->top->data == condition) {
        pop(stack);
    }
}

// helper function, don't use this!
struct stack new_stack(int *data, int len) {
    struct stack stack = {0};
    if (len == 0) {
        return stack;
    }
    stack.top = new_node(data[0]);
    for (int i = 1; i < len; i++) {
        struct node *tmp = new_node(data[i]);
        tmp->next = stack.top;
        stack.top = tmp;
    }
    return stack;
}

// helper function don't use this!
void check_stack(struct stack stack, int *data, int len) {
    int i = 0;
    for (struct node *cur = stack.top; cur != NULL; cur = cur->next) {
        printf("%d %d\n", cur->data, data[len - i - 1]);
        assert(cur->data == data[len - 1 - i]);
        i++;
    }
}

void test_push(void) {
    struct stack a = {0};
    push(&a, 2);
    check_stack(a, (int[]){2}, 1);
    int data[101] = {2};
    for (int i = 0; i < 100; i++) {
        push(&a, i * 10);
        data[i + 1] = i * 10;
        check_stack(a, data, i + 2);
    }
}

void test_pop(void) {
    int data[101] = {2};
    for (int i = 0; i < 100; i++) {
        data[i + 1] = i * 10;
    }
    struct stack a = new_stack(data, 101);
    for (int i = 99; i >= 0; i--) {
        assert(pop(&a) == i * 10);
    }
    assert(pop(&a) == 2);
}

void test_pop_while(void) {
    struct stack a = new_stack((int[]){1, 2, 2, 2, 2}, 5);
    pop_while(&a, 2);
    assert(a.top->data == 1 && a.top->next == NULL);
}

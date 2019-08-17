#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct _node_t {
    struct _node_t *next;
    char            data;
};

typedef struct _node_t *Node;

Node push_stack(Node head, char data) {
    Node node = malloc(sizeof(struct _node_t));
    node->next = head;
    node->data = data;
    return node;
}

Node pop_stack(Node head, char *data) {
    *data = head->data;
    Node tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

int balanced(char *buf) {
    int len = strlen(buf);
    int i = 0;
    Node stack = NULL;
    while (i < len) {
        if (buf[i] == '{' || buf[i] == '[' || buf[i] == '(') {
            stack = push_stack(stack, buf[i]);
        } else if (buf[i] == '}' || buf[i] == ']' || buf[i] == ')') {
            char popped;
            stack = pop_stack(stack, &popped);
            // if they don't match
            if ((buf[i] == '}' && popped != '{') ||
                (buf[i] == ']' && popped != '[') ||
                (buf[i] == ')' && popped != '(')) {
                return 0;
            }
        }
        // else we just skip

        i++;
    }
    // if the stack is empty then we don't have balanced ones
    if (stack != NULL) {
        return 0;
    } else {
        return 1;
    }
}

int main(void) {
    assert(balanced("(a]") == 0);
    assert(balanced("(a)") == 1);
    assert(balanced("[(a)]") == 1);
    assert(balanced("{(a){2}}") == 1);
    assert(balanced("{}") == 1);
    assert(balanced("") == 1);
    assert(balanced("a") == 1);
    assert(balanced("{]") == 0);
    assert(balanced("[(]") == 0);
    assert(balanced("{{}") == 0);
    // What do you think this indicates this kind of program
    // can be used for??
    assert(balanced("int main(void) { return 0; ") == 0);
    return 0;
}

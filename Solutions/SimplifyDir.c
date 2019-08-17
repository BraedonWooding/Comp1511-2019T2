#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct _node_t {
    struct _node_t *next;
    char           *data;
};

typedef struct _node_t *Node;

Node push_stack(Node head, char *data) {
    Node node = malloc(sizeof(struct _node_t));
    node->next = head;
    node->data = data;
    return node;
}

Node pop_stack(Node head) {
    Node tmp = head;
    head = head->next;
    free(tmp->data);
    free(tmp);
    return head;
}

char *simplify(char *buf) {
    int len = strlen(buf);
    Node stack = NULL;
    // skip the first '/'
    int i = 1;
    char tmp_buf[1024] = {0};
    int sub_len = 0;

    while (i < len) {
        sub_len = 0;
        while (buf[i] != '/' && i < len) {
            tmp_buf[sub_len] = buf[i];
            sub_len++;
            i++;
        }
        tmp_buf[sub_len] = '\0';
        if (sub_len != 0 && strcmp(tmp_buf, ".") != 0) {
            // if there was actually something there and it wasn't just .
            if (strcmp(tmp_buf, "..") == 0) {
                // go back one
                stack = pop_stack(stack);
            } else {
                char *dup = malloc(sizeof(char) * (sub_len + 1));
                dup[sub_len] = '\0';
                int j = 0;
                while (j < sub_len) {
                    dup[j] = tmp_buf[j];
                    j++;
                }
                stack = push_stack(stack, dup);
            }
        }
        i++;
    }

    // reverse the stack into a queue by just taking the top element
    // and pushing the rest ontop
    Node reverse = NULL;
    while (stack != NULL) {
        Node tmp = stack;
        stack = stack->next;
        tmp->next = reverse;
        reverse = tmp;
    }

    // a lot more memory than we need but it's fine since we'll never need more
    // and its quicker this way.
    char *res = malloc(sizeof(char) * (strlen(buf) + 1));
    int current_offset = 0;

    while (reverse != NULL) {
        int i = 0;
        int sub_len = strlen(reverse->data);
        res[current_offset] = '/';
        current_offset++;
        while (i < sub_len) {
            res[current_offset] = reverse->data[i];
            current_offset++;
            i++;
        }
        Node tmp = reverse;
        reverse = reverse->next;
        free(tmp->data);
        free(tmp);
    }
    res[current_offset] = '\0';
    return res;
}

int main(void) {
    assert(strcmp(simplify("/home/a/./../c"), "/home/c") == 0);
    assert(strcmp(simplify("/home/"), "/home") == 0);
    assert(strcmp(simplify("/a/q/../b/./d/../c/./"), "/a/b/c") == 0);
    assert(strcmp(simplify("/abc"), "/abc") == 0);
    assert(strcmp(simplify("/q/./b/../"), "/q") == 0);

    return 0;
}

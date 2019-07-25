/*
 * =============================================================================
 *
 *       Filename:  ll_v1.c
 *
 *    Description:  A linked list visualisation :O
 *
 *        Version:  1.0
 *        Created:  25/07/19 13:37:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Braedon Wooding (bw), b.wooding@unsw.edu.au
 *   Organization:  UNSW
 *
 * =============================================================================
 */

#include "../llv.h"

char example1[] =
    "int num = atoi(argv[1]);\n"
    "struct node *cur = head;\n"
    "while (cur != NULL && cur->next != NULL && cur->next->data != num) {\n"
    "    cur = cur->next;\n"
    "}\n"
    "\n"
    "if (cur != NULL && cur->next != NULL) {\n"
    "    struct node *tmp = cur->next;\n"
    "    cur->next = cur->next->next;\n"
    "    free(tmp);\n"
    "}\n"
    ;
char example1Lines[sizeof(example1) + 100] = {};

void modifyLines(int cur_line) {
    char *cur = example1;
    char *out = example1Lines;
    int newLine = 1;
    int line = 0;

    while (*cur != '\0') {
        if (newLine) {
            line++;
            newLine = 0;
            *out++ = cur_line == line ? '>' : ' ';
            int tmp = line;
            if (tmp > 9) {
                tmp -= 10;
                *out++ = '1';
            } else {
                *out++ = '0';
            }
            *out++ = tmp + '0';
            *out++ = ' ';
        }

        *out = *cur++;
        if (*out == '\n') newLine = 1;
        out++;
    }
    *out = *cur;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;
    LL list = ll_new("Example List");
    for (int i = 0; i < 10; i++) {
        ll_append(list, NEW_NODE(ll, i));
    }

    LL_Node cur = list->head;
    attach_ptr(&cur, "cur");
    modifyLines(2);
    fmt_update("%l %s", list, example1Lines);
    modifyLines(3);
    fmt_update("%l %s", list, example1Lines);
    while (cur != NULL && cur->next != NULL && cur->next->data.int_data != atoi(argv[1])) {
        modifyLines(4);
        cur = cur->next;
        fmt_update("%l %s", list, example1Lines);
        modifyLines(3);
        fmt_update("%l %s", list, example1Lines);
    }
    modifyLines(5);
    fmt_update("%l %s", list, example1Lines);
    modifyLines(7);
    fmt_update("%l %n %s", list, cur, example1Lines);
    if (cur == NULL || cur->next == NULL) {
        modifyLines(11);
        fmt_update("%l %s", list, example1Lines);
        return 0;
    }
    modifyLines(8);
    LL_Node tmp = cur->next;
    attach_ptr(&tmp, "tmp");
    fmt_update("%l %n %n %s", list, cur, tmp, example1Lines);
    modifyLines(9);
    cur->next = cur->next->next;
    fmt_update("%l %n %n %s", list, cur, tmp, example1Lines);
    modifyLines(10);
    deattach_ptr(&tmp, "tmp");
    fmt_update("%l %n %s", list, cur, example1Lines);
}

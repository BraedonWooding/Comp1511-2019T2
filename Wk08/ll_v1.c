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
    "struct node *cur = head;\n"
    "while (cur != NULL) {\n"
    "    printf(\"%d\\n\", cur->data);\n"
    "    cur = cur->next;\n"
    "}\n"
    ;
char example1Lines[sizeof(example1) + 15] = {};

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
            *out++ = line + '0';
            *out++ = ' ';
        }

        *out = *cur++;
        if (*out == '\n') newLine = 1;
        out++;
    }
    *out = *cur;
}

int main(void) {
    LL list = ll_new("Example List");
    for (int i = 0; i < 10; i++) {
        ll_append(list, NEW_NODE(ll, i));
    }

    LL_Node cur = list->head;
    attach_ptr(&cur, "cur");
    modifyLines(1);
    fmt_update("%l %s", list, example1Lines);
    modifyLines(2);
    fmt_update("%l %s", list, example1Lines);
    char number[15] = "STDOUT: ";
    while (cur != NULL) {
        modifyLines(3);
        sprintf(number + 8, "%d", cur->data.int_data);
        fmt_update("%l %s %s", list, example1Lines, number);
        cur = cur->next;
        modifyLines(4);
        fmt_update("%l %s", list, example1Lines);
        modifyLines(2);
        fmt_update("%l %s", list, example1Lines);
    }
    modifyLines(5);
    fmt_update("%l %s", list, example1Lines);
}

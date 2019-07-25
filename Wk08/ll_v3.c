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
    "struct node *new = malloc(sizeof(struct node));\n"
    "scanf(\"%d\", &new->data);\n"
    "new->next = NULL;\n"
    "struct node *cur = head;\n"
    "while (cur != NULL && cur->next != NULL && cur->next->next != NULL) {\n"
    "    cur = cur->next;\n"
    "}\n"
    "\n"
    "if (cur != NULL && cur->next != NULL) {\n"
    "    new->next = cur->next;\n"
    "    cur->next = new;\n"
    "} else if (head == NULL) {\n"
    "    head = new;\n"
    "} else {\n"
    "    new->next = head;\n"
    "    head = new;\n"
    "}\n"
    "return head;\n"
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
                *out++ = tmp / 10 + '0';
                tmp -= 10;
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
    LL list = ll_new("Example List");
    LL_Node cur = list->head;
    modifyLines(1);
    int num = 1;
    while (1) {
        attach_ptr(&cur, "cur");
        modifyLines(2);
        fmt_update("%l %s %ii", list, example1Lines, &num);
        LL_Node n = NEW_NODE(ll, num);
        attach_ptr(&n, "new");
        modifyLines(3);
        fmt_update("%l %n %s", list, n, example1Lines);
        n->next = NULL;
        modifyLines(4);
        cur = list->head;
        fmt_update("%l %n %s", list, n, example1Lines); 
        modifyLines(5);
        fmt_update("%l %n %s", list, n, example1Lines);
        while (cur != NULL && cur->next != NULL && cur->next->next != NULL) {
            cur = cur->next;
            modifyLines(6);
            fmt_update("%l %n %s", list, n, example1Lines);
            modifyLines(5);
            fmt_update("%l %n %s", list, n, example1Lines);
        }
        modifyLines(9);
        fmt_update("%l %n %s", list, n, example1Lines);
        if (cur != NULL && cur->next != NULL) {
            n->next = cur->next;
            modifyLines(10);
            fmt_update("%l %n %s", list, n, example1Lines);
            cur->next = n;
            modifyLines(11);
            fmt_update("%l %n %s", list, n, example1Lines); 
        } else if (list->head == NULL) {
            modifyLines(12);
            fmt_update("%l %n %s", list, n, example1Lines);
            ll_append(list, n);
            modifyLines(13);
            fmt_update("%l %n %s", list, n, example1Lines);
        } else {
            modifyLines(14);
            fmt_update("%l %n %s", list, n, example1Lines);
            n->next = list->head;
            modifyLines(15);
            fmt_update("%l %n %s", list, n, example1Lines);
            list->head = n;
            modifyLines(16);
            fmt_update("%l %n %s", list, n, example1Lines);
        }
        deattach_ptr(&n, "new");
        deattach_ptr(&cur, "cur");
        modifyLines(18);
        fmt_update("%l %s", list, example1Lines);
    }
}

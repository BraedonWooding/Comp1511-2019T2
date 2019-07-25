// If library
// #include <LLV/collections/ll.h>
// #include <LLV/llv.h>
// Else
#include "../llv.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    LL list = ll_new("Example List");
    double res;
    while(true) {
        fmt_update("%l %if", list, &res);
        // 0 has an actual proper value so epsilon isn't needed
        // here since we aren't doing arithmetic on it
        if (res == 0) break;
        // NEW_NODE picks up on it being a double and doesn't care!!! yay
        ll_append(list, NEW_NODE(ll, res));
    }

    double lower, upper;
    // no need to have lists here we just want a lower and upper bound but why not
    fmt_update("%l %s %if %if", list, "Enter lower and then upper bound", &lower, &upper);

    LL_Node cur = list->head;
    attach_ptr(&cur, "cur");
    update(1, list);
    while (cur != NULL) {
       if (cur->data.flt_data < lower || cur->data.flt_data > upper) {
           LL_Node tmp = cur;
           cur = cur->next;
           ll_remove_node(list, tmp);
           fmt_update("%l %s %n", list, "Removed Node:", tmp);
           ll_free_node(tmp);
       } else {
           cur = cur->next;
       }
    }

    fmt_update("%s %l", "Finished Removing Nodes out of bounds", list);
    deattach_ptr(&cur, "cur");
    ll_free(list);
}

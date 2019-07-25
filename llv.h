/* AUTO GENERATED */
#ifndef LLV_H
#define LLV_H

/* A collection of helper functions */

#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#   define WINDOWS_COMPATIBILITY
#   define CLEAR_SCREEN "cls"
#else
#   define UNIX_COMPATIBILITY
#   define CLEAR_SCREEN "clear"
#endif

typedef struct _terminal_int {
    int width;
    int height;
} terminalSize;

void write_str_to_buf(wchar_t **buf, int offset, int len, int index,
                      wchar_t *str, int str_len);

void write_str_center_of_buf(wchar_t **buf, int offset, int len,
                             wchar_t *str, int str_len);

void write_str_repeat_char(wchar_t *buf, int offset, wchar_t c, int count);

void write_str_repeat_char_vert(wchar_t **buf, int offset, wchar_t c, int count, int index);

void write_str_repeat_char_grid(wchar_t **buf, int offset, wchar_t c, int vert_count,
                                int horiz_count, int index);

terminalSize get_terminal_size(void);

/*
    Sleeps for the given amount of time.
*/
void sleep_ms(int ms);

/*
    Mallocs 'size' memory and exits with OOM message if memory is NULL.
*/
void *malloc_with_oom(size_t size, char *obj_name);

bool contains_utf(char *str);

/*
    Chooses 'unicode' string if unicode support is enabled else will choose 'backup'.
*/
wchar_t select_char_unicode(wchar_t unicode, wchar_t backup);

wchar_t *select_str_unicode(wchar_t *unicode, wchar_t *backup);

bool str_icase_eql(char *a, char *b);
bool atob(char *str);
bool supports_unicode(void);

void assert_msg(bool expr, char *fmt, ...);

typedef struct _collection_t *Collection;

typedef void(*fn_print_node)(void *n, wchar_t **buf, int size, int len, int offset);
typedef int(*fn_sizeof_node)(void *n);
typedef void(*fn_print_list)(Collection collection);

// Currently we expect everyone to fit in the COLLECTION_NODE struct properly
// Really we should do the same as above!  and have fake node defined as just that
// then have a fake linked list node that is defined with the next pointer.

// This is the main linked list class; you get a subsect of the list.
struct _collection_t {
    char *name;
    fn_print_node node_printer;
    fn_sizeof_node get_sizeof;
    fn_print_list list_printer;
};

#if defined(__STDC__)
#   if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)  /* C11 */
#       define MODERN_C
#   endif
#endif

#ifndef MODERN_C
#   warning "Not Modern C, behaviour is not guaranteed"
#endif

// This is used everywhere

// all the possible data types
typedef enum _type_tag {
    FLOAT,
    STRING,
    INTEGER,
    ANY,        // if set for a list its equivalent to 'none'
} TypeTag;

typedef union _data {
    long long int_data;
    void *any_data;
    char *str_data;
    double flt_data;
} Data;

typedef struct _data_node_t {
    char *visual_ptr;
    Data data;
    TypeTag tag;
} DataNode;

Data data_int(long long data);
Data data_flt(double data);
Data data_str(char *data);
Data data_any(void *data);

/* This is the main header to import, by importing this you get everything
   you need to build an example/demonstration of LLV except for the collections.
*/

#ifdef MODERN_C
#   define GET_DATA(data)              \
        _Generic((data),                \
            long: data_int, \
            long long: data_int, \
            unsigned int: data_int, \
            unsigned long: data_int, \
            unsigned long long: data_int, \
            int: data_int, \
            float: data_flt, \
            double: data_flt, \
            long double: data_flt, \
            char: data_int, \
            short: data_int, \
            unsigned short: data_int, \
            char *: data_str, \
            bool: data_int, \
            default: data_any \
        )(data)

#   define GET_DATA_TYPE(data)         \
        _Generic((data),                \
            long: INTEGER, \
            long long: INTEGER, \
            unsigned int: INTEGER, \
            unsigned long: INTEGER, \
            unsigned long long: INTEGER, \
            int: INTEGER, \
            float: FLOAT, \
            double: FLOAT, \
            long double: FLOAT, \
            char: INTEGER, \
            short: INTEGER, \
            unsigned short: INTEGER, \
            char *: STRING, \
            bool: INTEGER, \
            default: ANY \
        )

#   define NEW_NODE(type, data) type##_new_node(GET_DATA(data), GET_DATA_TYPE(data))
#endif

#define SET_PTR(node, value) if ((node) != NULL) (node)->ptr = value;
#define UNSET_PTR(node) SET_PTR(node, NULL)

void update(int number, ...);
void update_wait(void);
void fmt_update(char *fmt, ...);
void clear_screen(void);

void attach_ptr(void *node, char *ptr);
bool deattach_ptr(void *node, char *ptr);

void print_out_single_box(void *node, fn_print_node printer, fn_sizeof_node sizeof_n, int height);
void print_out_single_box_using_defaults(void *node, Collection c);

#include <stdio.h>
#include <inttypes.h>

#undef new_env_var
#define new_env_var(name, env_name, type, default_value, process_fn) \
    type name(void);

new_env_var(get_print_height, LLV_PRINT_HEIGHT, int, 5, atoi);
new_env_var(get_ptr_height, LLV_PTR_HEIGHT, int, 2, atoi);
new_env_var(unicode_in_lang, LANG, bool, false, contains_utf)
new_env_var(get_sleep_time, LLV_SLEEP_TIME, int, 0, atoi);
new_env_var(clear_on_update, LLV_CLEAR_ON_UPDATE, bool, true, atob);
new_env_var(unicode_disabled, LLV_DISABLE_UNICODE, bool, false, atob);
new_env_var(include_ptrs_on_single, LLV_INCLUDE_PTRS_ON_SINGLE_BOX, bool, false, atob);
new_env_var(get_default_term_width, LLV_DEFAULT_TERM_WIDTH, int, 80, atoi);
new_env_var(get_default_term_height, LLV_DEFAULT_TERM_HEIGHT, int, 80, atoi);
new_env_var(testing_activated, LLV_TESTING, bool, false, atob);
new_env_var(force_unicode, LLV_FORCE_UNICODE, bool, false, atob);

#define MAX_SIZE_FLT                    (15)

int sizeof_uint(unsigned long long int n);

int sizeof_int(long long int n);

void write_str_center_incr(wchar_t **buf, int *offset, int len,
                           wchar_t *str, int str_len);

int sizeof_data(Data data, TypeTag tag);

typedef struct _dll_node_t *DLL_Node;

struct _dll_node_t {
    char *ptr;          // for display
    Data data;          // the data type
    TypeTag data_tag;   // the corresponding tag for the data ^^;
    DLL_Node next;      // the next item in the LL
    DLL_Node prev;      // the previous item
};

typedef struct _doubly_linked_list_t {
    struct _collection_t parent;   // all the inherited members
    DLL_Node head;      // the head of the list
    DLL_Node tail;      // the tail of the list
} *DLL;

/*
    Create a new list with a given name and a default type.
*/
DLL dll_new(char *name);

/*
    Clears and frees list.
*/
void dll_free(DLL list);

/*
    Frees the given node.
*/
void dll_free_node(DLL_Node n);

/*
    Creates a new node with the data given.
*/
DLL_Node dll_new_node(Data data, TypeTag type);

/*
    Prints out the node data.
*/
void dll_default_print_data(DLL_Node n);

/*
    Free all nodes in collection.
*/
void dll_clear(DLL list);

/*
    Inserts the given node after the DLL_Node 'at'.
*/
void dll_insert_after(DLL list, DLL_Node node, DLL_Node at);

/*
    Inserts the given node before the DLL_Node 'at'.
*/
void dll_insert_before(DLL list, DLL_Node node, DLL_Node at);

/*
    Removes the given node from the list, returning the node removed.
*/
DLL_Node dll_remove_node(DLL list, DLL_Node node);

/*
    Returns true if the list is empty.
*/
int dll_is_empty(DLL list);

/*
    List can be null in some cases.  Will find the previous node to the given one.
*/
DLL_Node dll_find_prev(DLL_Node at);

/*
    List can be null in some cases.  Will find the next node to the given one.
*/
DLL_Node dll_find_next(DLL_Node n);

/*
    Returns length of list.
*/
int dll_length(DLL list);

/*
    Pushes node to top of list.
*/
void dll_push(DLL list, DLL_Node n);

/*
    Pops top node from list.
*/
DLL_Node dll_pop(DLL list);

/*
    Adds node to end of list.
*/
void dll_append(DLL list, DLL_Node n);

typedef struct _list_t *List;
typedef struct _list_data_t *ListNode;

typedef int(*fn_growth_factor)(int old_len, int min_new_len, double factor);

struct _list_data_t {
    char *ptr;
    Data data; // the data type
    TypeTag data_tag; // the corresponding tag;
};

struct _list_t {
    struct _collection_t parent;
    ListNode data;
    int cur_len;
    int max_len;
    fn_growth_factor grow_function;
    double factor;
};

/*
    Create a new list with the given name.
    By default uses `poly_grow_function` with factor 2.
*/
List list_new(char *name);

/*
    Frees the list.
*/
void list_free(List list);

/*
    Grows the list linearly.
    i.e. increases by factor each time.
    if factor == 0 then just is always min_new_len i.e. no growth.
    for factor == 2 => 2 -> 4 -> 6 -> 8 -> 10...
*/
int linear_grow_function(int old_len, int min_new_len, double factor);

/*
    Grows the list polynomially.
    i.e. doubles each time if factor == 2.
    2 -> 4 -> 8...
*/
int poly_grow_function(int old_len, int min_new_len, double factor);

/*
    y = x^factor such that min_new_len <= y(old_len).
    Will effectively find the smallest multiple such that it'll fit the min_new_len.

    2 -> 4 -> 16... for a factor of 2
    2 -> 8 -> 512... for a factor of 3
*/
int exponential_grow_function(int old_len, int min_new_len, double factor);

/*
    Get the node at the index given.
*/
ListNode list_at(List list, int index);

/*
    Creates a new list node.
    Used for the other functions
*/
struct _list_data_t list_new_node(Data data, TypeTag type);

/*
    Makes sure the list can handle len amount of data.
*/
void list_reserve(List list, int len);

/*
    Clears list.  Will release memory if release_memory is true.
*/
void list_clear(List list, int release_memory);

/*
    Pushes node to back of list, growing if needed.
*/
void list_push_back(List list, struct _list_data_t node);

/*
    Inserts node after index given.
*/
void list_insert_after(List list, int index, struct _list_data_t node);

/*
    Inserts node before index given.
*/
void list_insert_before(List list, int index, struct _list_data_t node);

/*
    Removes node at index.
*/
void list_remove(List list, int index);

/*
    Returns true if list is empty.
*/
int list_is_empty(List list);

/*
    Returns length of list.
*/
int list_length(List list);

/*
    Returns capacity of list.
*/
int list_capacity(List list);

typedef struct _array_t *Array;
typedef struct _array_data_t *ArrayNode;

struct _array_data_t {
   char *ptr;
   Data data; // the data type
   TypeTag data_tag; // the corresponding tag;
};

struct _array_t {
   struct _collection_t parent;
   ArrayNode data;
   int len;
};

/* Create a new array with a given name and size */
Array array_new(char *name, int size);

/* Free the array */
void array_free(Array array);

/* Get the array node at the given index */
ArrayNode array_at(Array array, int index);

/*
   Create a new array node for use in the other functions 
   Could use NEW_NODE(array, data) instead! 
*/
struct _array_data_t array_new_node(Data data, TypeTag type);

/*
   Resize the array to the new size keeping the old elements.
*/
void array_resize(Array array, int new_size);

/*
   Set a specific index to a node value.
*/
void array_set(Array array, int index, struct _array_data_t node);

/*
   Get the array length.
*/
int array_length(Array array);

/*
  This is so we don't have to import all the LL functions if we are just using stacks/queues.
*/

struct _LL_node_t {
    char *ptr;          // for display
    Data data;          // the data of this node
    TypeTag data_tag;   // the corresponding tag for the data ^^
    struct _LL_node_t *next;       // the next one in the list
};

typedef struct _singly_linked_list_t {
    struct _collection_t parent;   // inherited members
    struct _LL_node_t *head;       // the front of the list
    struct _LL_node_t *tail;       // the back of the list
} *LL;

typedef struct _singly_linked_list_t *Stack;
typedef struct _LL_node_t *StackNode;

/* Create a new stack with a given name */
Stack stack_new(char *name);

/* Free the stack */
void stack_free(Stack stack);

/* Frees the given node */
void stack_free_node(StackNode n);

/* Returns how many items are currently on the stack */
int stack_length(Stack stack);

/* Returns true if there are no items on the stack */
int stack_is_empty(Stack stack);

/* Free all nodes in stack. */
void stack_clear(Stack stack);

/* 
   Create a new node in the stack 
   Could use NEW_NODE(stack, data);
*/
StackNode stack_new_node(Data data, TypeTag type);

/* Pushes a new node onto the top of the stack */
void stack_push(Stack stack, StackNode node);

/* Pops a node form the top of the stack */
StackNode stack_pop(Stack stack);

#include <string.h>

/*
    valid values for WIDTH
    - (0) no spaces i.e. `|a||b||c||d|`
    - (x > 0) spaces i.e. for x == 1 `|a| |b| |c| |d|`
    - (x == -1) no spaces and no double bars i.e. `|a|b|c|d|`
*/
#define WIDTH (1)
#define ELLIPSES (L" [ ... ]")
#define ELLIPSES_LEN (wcslen(ELLIPSES))

struct _fake_array_data_t {
   char *ptr;
   Data data; // the data type
   TypeTag data_tag; // the corresponding tag;
};

typedef struct _fake_array_data_t *FakeArrayNode;

void print_array_like(Collection c, char *collection_type, FakeArrayNode data, int len);

typedef struct _LL_node_t *LL_Node;

/*
    Create a new list with a given name and a default type.
*/
LL ll_new(char *name);

/*
    Clears and frees list.
*/
void ll_free(LL list);

/*
    Frees the given node.
*/
void ll_free_node(LL_Node n);

/*
    Creates a new node with the data given.
*/
LL_Node ll_new_node(Data data, TypeTag type);

/*
    Prints out the node data.
*/
void ll_default_print_data(LL_Node n);

/*
    Free all nodes in collection.
*/
void ll_clear(LL list);

/*
    Inserts the given node after the LL_Node 'at'.
*/
void ll_insert_after(LL list, LL_Node node, LL_Node at);

/*
    Inserts the given node before the LL_Node 'at'.
*/
void ll_insert_before(LL list, LL_Node node, LL_Node at);

/*
    Removes the given node from the list, returning the node removed.
*/
LL_Node ll_remove_node(LL list, LL_Node node);

/*
    Returns true if the list is empty.
*/
bool ll_is_empty(LL list);

/*
    List can be null in some cases.  Will find the previous node to the given one.
*/
LL_Node ll_find_prev(LL list, LL_Node at);

/*
    List can be null in some cases.  Will find the next node to the given one.
*/
LL_Node ll_find_next(LL_Node n);

/*
    Returns the length of the list.
*/
int ll_length(LL list);

/*
    Pushes node to top of list.
*/
void ll_push(LL list, LL_Node n);

/*
    Pops top node from list.
*/
LL_Node ll_pop(LL list);

/*
    Adds node to end of list.
*/
void ll_append(LL list, LL_Node n);

#define NULL_NODE L"X"
#define NULL_NODE_LEN wcslen(NULL_NODE)
#define SPACES_ON_SIDE (2)
#define EXTRA_WIDTH (4)

#define BOX_HORIZONTAL select_char_unicode(L'═', L'=')
#define BOX_BOTTOM_RIGHT select_char_unicode(L'╝', L'=')
#define BOX_BOTTOM_LEFT select_char_unicode(L'╚', L'=')
#define BOX_VERT select_char_unicode(L'║', L'|')
#define BOX_TOP_LEFT select_char_unicode(L'╔', L'=')
#define BOX_TOP_RIGHT select_char_unicode(L'╗', L'=')

// make sure your struct can downcast to this
// don't malloc this!
typedef struct _fake_node_t {
    char *ptr;
    Data data; // the data type
    TypeTag data_tag; // the corresponding tag;
    struct _fake_node_t *next;
} *FakeNode;

int list_sizeof(void *n);

void list_print_node(void *n, wchar_t **buf, int size, int len, int offset);

void list_print_general(Collection list, int len, int count, FakeNode forwards,
                FakeNode backwards, int stop, int *node_sizes, wchar_t *after_node,
                wchar_t *start_of_list, wchar_t *end_of_list, wchar_t *ellipses, FakeNode head,
                char *collection_name);

typedef struct _singly_linked_list_t *Queue;
typedef struct _LL_node_t *QueueNode;

/* Create a new queue with a given name */
Queue queue_new(char *name);

/* Frees the queue and all the memory its allocated */
void queue_free(Queue queue);

/* Frees the given node */
void queue_free_node(QueueNode n);

/* Returns how many items are currently in queue */
int queue_length(Queue queue);

/* Returns true if there are no items in queue */
int queue_is_empty(Queue queue);

/* Free all nodes in queue. */
void queue_clear(Queue queue);

/*
   Create a new node
   Could use NEW_NODE(queue, data)
*/
QueueNode queue_new_node(Data data, TypeTag type);

/*
    Adds a object to the end of the queue
*/
void queue_enqueue(Queue queue, QueueNode node);

/*
    Takes an object from the front of the queue.
*/
QueueNode queue_dequeue(Queue queue);

#include <stdint.h>

void list_print(Collection c);

int int_pow(int base, int exp) {
    int res = base;
    for (int i = 1; i < exp; i++) res *= base;
    return res;
}

List list_new(char *name) {
    List list = (List)malloc_with_oom(sizeof(struct _list_t), "List");
    list->cur_len = list->max_len = 0;
    list->data = NULL;
    list->grow_function = poly_grow_function;
    list->factor = 2.0;
    list->parent.get_sizeof = list_sizeof;
    list->parent.node_printer = list_print_node;
    list->parent.list_printer = list_print;
    list->parent.name = name;
    return list;
}

void list_free(List list) {
    if (list->data != NULL) free(list->data);
    free(list);
}

int linear_grow_function(int old_len, int min_new_len, double factor) {
    assert_msg(factor >= 0.0, "list:linear_grow_function factor (%d) must be "
                              "positive or 0", factor);
    if (factor == 0 || old_len == 0) return min_new_len;
    return (min_new_len + factor) * factor / factor;
}

int poly_grow_function(int old_len, int min_new_len, double factor) {
    assert_msg(factor >= 0.0, "list:poly_grow_function factor (%d) must be "
                              "positive or 0", factor);
    if (factor == 0 || old_len == 0) return min_new_len;
    int new_len = old_len;
    while (new_len <= min_new_len) new_len *= factor;
    return new_len;
}

int exponential_grow_function(int old_len, int min_new_len, double factor) {
    assert_msg(factor >= 0.0, "list:exponential_grow_function factor (%d) must "
                              "be positive or 0", factor);
    if (factor == 0 || old_len == 0) return min_new_len;
    int new_len = old_len;
    while (new_len <= min_new_len) new_len = int_pow(new_len, factor);
    return new_len;
}

ListNode list_at(List list, int index) {
    if (list->cur_len >= index) return NULL;
    return &list->data[index];
}

struct _list_data_t list_new_node(Data data, TypeTag type) {
    return (struct _list_data_t) {
        .data = data,
        .data_tag = type,
        .ptr = NULL,
    };
}

void list_clear(List list, int release_memory) {
    list->cur_len = 0;
    if (release_memory) {
        list->max_len = 0;
        free(list->data);
    }
}

void list_push_back(List list, struct _list_data_t node) {
    if (list->cur_len == list->max_len) list_reserve(list, list->cur_len + 1);
    list->data[list->cur_len++] = node;
}

/*
    @Refactor: These two are similar enough that we need a middleman func.
    Also don't like the early return probably an else would be better.
*/
void list_insert_after(List list, int index, struct _list_data_t node) {
    assert_msg(list->cur_len > index, "list:list_insert_after %d is out of "
                                      "bounds, the max index"
                                      "is %d\n", index, list->cur_len - 1);
    if (index == list->cur_len - 1) {
        list_push_back(list, node);
        return;
    }

    if (list->cur_len == list->max_len) list_reserve(list, list->cur_len + 1);
    memmove(list->data + index + 2, list->data + index + 1,
        sizeof(struct _list_data_t) * (list->cur_len - 1 - index));
    list->data[index + 1] = node;
    list->cur_len++;
}

void list_insert_before(List list, int index, struct _list_data_t node) {
    assert_msg(list->cur_len > index, "list:list_insert_after %d is out of "
                                      "bounds, the max index"
                                      "is %d\n", index, list->cur_len);
    if (index == list->cur_len) {
        list_push_back(list, node);
        return;
    }

    if (list->cur_len == list->max_len) list_reserve(list, list->cur_len + 1);
    memmove(list->data + index + 1, list->data + index,
        sizeof(struct _list_data_t) * (list->cur_len - 1 - index));
    list->data[index] = node;
    list->cur_len++;
}

void list_remove(List list, int index) {
    assert_msg(list->cur_len > index, "list:list_insert_after %d is out of "
                                      "bounds, the max index"
                                      "is %d\n", index, list->cur_len - 1);
    // easy remove
    if (index == list->cur_len - 1) {
        list->cur_len--;
        return;
    } else {
        // shuffle back one post index
        memmove(list->data + index, list->data + index + 1,
            sizeof(struct _list_data_t) * (list->cur_len - 1 - index));
    }
}

int list_is_empty(List list) {
    return list->cur_len == 0;
}

int list_length(List list) {
    return list->cur_len;
}

int list_capacity(List list) {
    return list->max_len;
}

void list_reserve(List list, int len) {
    if (list->max_len >= len) return;
    int new_len = list->grow_function(list->max_len, len, list->factor);
    list->max_len = new_len;
    list->data = (ListNode)realloc(list->data, sizeof(struct _list_data_t) * list->max_len);
}

void list_print(Collection c) {
    List list = (List)c;
    print_array_like(c, "List", (FakeArrayNode)list->data, list->cur_len);
}

#include <assert.h>
#include <wchar.h>

int array_get_sizes(Collection c, FakeArrayNode array, int len, int max, int **node_sizes, int *out_calculated_len) {
    int count = 0;
    *out_calculated_len = 0;
    if (len == 0) *node_sizes = NULL;
    else *node_sizes = (int*)malloc_with_oom(sizeof(int) * len, "Node Sizes");

    // same idea as DLL, go both ways
    int i;
    int mod = -1;

    // this will handle the case where we have extra width at the end
    if (len > 0) count = -WIDTH;

    for (i = 0; i < (len + 1) / 2; i++) {
        int forward_size = c->get_sizeof(&array[i]);
        (*node_sizes)[i] = forward_size;

        if (forward_size + count + WIDTH > max) {
            count += ELLIPSES_LEN;
            if (count > max) {
                mod = 1;
            }
            break;
        }
        count += forward_size + WIDTH;
        (*out_calculated_len)++;

        if (i == len / 2) break;

        int backward_size = c->get_sizeof(&array[len - 1 - i]);
        (*node_sizes)[len - 1 - i] = backward_size;
        if (backward_size + count + WIDTH > max) {
            count += ELLIPSES_LEN;
            if (count > max) mod = 0;
            break;
        }
        count += backward_size + WIDTH;
        (*out_calculated_len)++;
    }

    // this presumes that we don't have one node bigger than the screen.
    // obviously this could be incorrect.
    if (mod != -1) {
        // we have to handle the size being over the limit
        while (count > max) {
            if (mod % 2 == 0) {
                // we want to undo front
                count -= (*node_sizes)[i] + WIDTH;
            } else {
                // undo back
                i--;
                count -= (*node_sizes)[len - 1 - i] + WIDTH;
            }
            (*out_calculated_len)--;
            mod++;
        }
    }

    if ((*out_calculated_len == 1 && len > 1) ||
        (*out_calculated_len == 0 && len > 0)) {
        printf("Error: No valid sizing constraint matches terminal size; i.e. increase your terminal size since on current size can't even fit the bare minimum\n");
        exit(1);
    }

    return count;
}

void print_array_like(Collection c, char *collection_type, FakeArrayNode data, int len) {
    terminalSize size = get_terminal_size();
    int *node_sizes;
    int calculated_len;
    int count = array_get_sizes(c, data, len, size.width, &node_sizes, &calculated_len);
    assert_msg(calculated_len <= len, "array_helper:print_array_like, calculated_len (%d) must be <= len (%d)\n", calculated_len, len);

    int total_height = get_print_height() + get_ptr_height();
    wchar_t **buf = (wchar_t**)malloc_with_oom(sizeof(wchar_t*) * total_height, "Buffer");
    for (int i = 0; i < total_height; i++) {
        buf[i] = (wchar_t*)malloc_with_oom((count + 1) * sizeof(wchar_t), "Buffer");
        for (int j = 0; j < count; j++) buf[i][j] = ' ';
        buf[i][count] = '\0';
    }

    int front_len = calculated_len == len ? calculated_len : (calculated_len + 1) / 2;
    int offset = 0;
    for (int i = 0; i < front_len; i++) {
        if (i != 0) {
            write_str_repeat_char_grid(buf, offset, ' ', get_print_height(), WIDTH, 0);
            offset += WIDTH;
        }
        list_print_node(&data[i], buf, node_sizes[i], get_print_height(), offset);
        offset += node_sizes[i];
    }

    if (front_len != calculated_len) {
        // do middle/ellipses
        write_str_center_incr(buf, &offset, get_print_height(), ELLIPSES, ELLIPSES_LEN);

        // do back side
        for (int i = len - calculated_len / 2; i < len; i++) {
            write_str_repeat_char_grid(buf, offset, ' ', get_print_height(), WIDTH, 0);
            offset += WIDTH;
            list_print_node(&data[i], buf, node_sizes[i], get_print_height(), offset);
            offset += node_sizes[i];
        }
    }

    printf("%s: %s\n", collection_type, c->name);
    for (int i = 0; i < get_print_height(); i++) {
        printf("%ls\n", buf[i]);
        free(buf[i]);
    }
    for (int i = get_print_height(); i < total_height; i++) {
        bool found_non_space = false;
        for (int j = 0; j < count; j++) {
            if (buf[i][j] != ' ') {
                found_non_space = true;
                break;
            }
        }
        if (found_non_space) printf("%ls\n", buf[i]);
        free(buf[i]);
    }

    assert_msg(offset == count, "array_helper:print_array_like, "
                                "we promised to print out %d characters and "
                                "printed out just %d\n", count, offset);
    printf("\n");

    free(buf);
    free(node_sizes);
}

void array_print(Collection c);

Array array_new(char *name, int size) {
    Array array = (Array)malloc_with_oom(sizeof(struct _array_t), "Array");
    array->data = (ArrayNode)malloc_with_oom(sizeof(struct _array_data_t) * size, "Array Nodes");
    array->len = size;
    array->parent.get_sizeof = list_sizeof;
    array->parent.node_printer = list_print_node;
    array->parent.list_printer = array_print;
    array->parent.name = name;
    return array;
}

void array_free(Array array) {
    free(array->data);
    free(array);
}

ArrayNode array_at(Array array, int index) {
    if (array->len <= index) return NULL;
    return &array->data[index];
}

struct _array_data_t array_new_node(Data data, TypeTag type) {
    return (struct _array_data_t) {
        .data = data,
        .ptr = NULL,
        .data_tag = type,
    };
}

void array_resize(Array array, int new_size) {
    array->data = (ArrayNode)realloc(array->data, sizeof(struct _array_data_t) * new_size);
    array->len = new_size;
}

void array_set(Array array, int index, struct _array_data_t node) {
    assert_msg(array->len > index, "array:array_set %d is out of bounds max "
                                   "index is %d", index, array->len - 1);
    array->data[index] = node;
}

int array_length(Array array) {
    return array->len;
}

void array_print(Collection c) {
    Array array = (Array)c;
    print_array_like(c, "Array", (FakeArrayNode)array->data, array->len);
}

Stack stack_new(char *name) {
    return ll_new(name);
}

void stack_free(Stack stack) {
    ll_free(stack);
}

void stack_free_node(StackNode n) {
    ll_free_node(n);
}

void stack_clear(Stack stack) {
    ll_clear(stack);
}

int stack_length(Stack stack) {
    return ll_length(stack);
}

int stack_is_empty(Stack stack) {
    return ll_is_empty(stack);
}

StackNode stack_new_node(Data data, TypeTag type) {
    return ll_new_node(data, type);
}

void stack_push(Stack stack, StackNode node) {
    ll_push(stack, node);
}

StackNode stack_pop(Stack stack) {
    return ll_pop(stack);
}

#define PTR_SYMBOL select_char_unicode(L'⌃', L'^')

void print_bounding_box(wchar_t **buf, int offset, int len, int width);
void print_out_nodes(Collection list, FakeNode begin, FakeNode end, wchar_t **buf, int *node_sizes,
                         int *offset, wchar_t *after_node, int starting_size);

int list_sizeof(void *n) {
    FakeNode node = (FakeNode)n;
    return sizeof_data(node->data, node->data_tag) + EXTRA_WIDTH;
}

/*
    @REFACTORING NOTICE:
    - I'll attempt this soon, it isn't just magic numbers to fix I have a few crazy ideas
      to how to fit even more pointers by placing above/below as well this could show nicer pointers
      then having just below.
*/
void print_ptr(wchar_t **buf, int len, int count, char *ptr_name, int ptr_len, int offset) {
    // @REFACTORING
    // this is just a very early version
    // I'm going to update this once I figure out visual ptrs a bit more
    // a lot of this is hand waivey and magic variables
    int i = 0;
    while (i < get_ptr_height() && buf[len + i][offset] == PTR_SYMBOL) i++;

    if (i == get_ptr_height()) {
        // we can fit two if we are clever
        // we want to make sure though that we haven't done this before
        // and find a level that we can fit the second one on
        i = 0;
        while (i < get_ptr_height() && buf[len + i][offset + count] != ' ') i++;
        if (i == get_ptr_height()) {
            // oh no, we can't print this out :(
            // @TODO: figure out if we want to try something else
            return;
        }

        for (int j = offset + 3; j < offset + count; j++) buf[i + len][j] = ' ';
        // first truncate old ptr
        // next we want to fit ourselves in we will push ourselves one/two longer
        // then the actual minimum square, but that's okay, min is 5 and ptr is always
        // ` -> ` so we can fit it
        int max = ptr_len + 1 > 7 ? 7 : ptr_len + 1;
        for (int j = offset + 4; j < offset + max; j++) buf[i + len][j] = ptr_name[j - offset - 4];
        buf[i + len][offset + 3] = PTR_SYMBOL;
    } else {
        int max = ptr_len + 1 > 5 ? 5 : ptr_len + 1;
        for (int j = offset + 1; j < offset + max; j++) buf[i + len][j] = ptr_name[j - offset - 1];
        buf[i + len][offset] = PTR_SYMBOL;
    }
}

void list_print_node(void *n, wchar_t **buf, int size, int len, int offset) {
    FakeNode node = (FakeNode)n;
    print_bounding_box(buf, offset, len, size);
    wchar_t *text_to_print;
    switch (node->data_tag) {
        case FLOAT: {
            text_to_print = (wchar_t*)malloc_with_oom(sizeof(wchar_t) * (size - EXTRA_WIDTH / 2 + 1), "Text to print");
            swprintf(text_to_print, size - EXTRA_WIDTH / 2 + 1, L"%.5g", node->data.flt_data);
        } break;
        case STRING: {
            int len = strlen(node->data.str_data);
            text_to_print = (wchar_t*)malloc_with_oom(len * sizeof(wchar_t), "Text to print");
            for (int i = 0; i < len; i++) text_to_print[i] = node->data.str_data[i];
        } break;
        case INTEGER: {
            // note: we are including the '\0' room just to make nothing weird happen
            // with snprintf, but we will completely ignore it below in memcpy.
            text_to_print = (wchar_t*)malloc_with_oom(sizeof(wchar_t) * (size - EXTRA_WIDTH / 2 + 1), "Text to print");
            swprintf(text_to_print, size - EXTRA_WIDTH / 2, L"%lld", node->data.int_data);
        } break;
        case ANY: {
            text_to_print = (wchar_t*)malloc_with_oom(sizeof(wchar_t) * (size - EXTRA_WIDTH / 2 + 1), "Text to print");
            swprintf(text_to_print, size - EXTRA_WIDTH / 2, L"%p", node->data.any_data);
        } break;
    }
    if (node->ptr != NULL) print_ptr(buf, len, size, node->ptr, strlen(node->ptr), offset);

    // our sizes are always buffered by '4'
    // a sprintf or similar is just going to give us nasty '\0'
    memcpy(buf[len / 2] + EXTRA_WIDTH/2 + offset, text_to_print, sizeof(wchar_t) * (size - EXTRA_WIDTH));
    free(text_to_print);
}

void print_bounding_box(wchar_t **buf, int offset, int len, int width) {
    write_str_repeat_char_vert(buf, offset, BOX_VERT, len, 0);
    write_str_repeat_char_vert(buf, offset, BOX_VERT, len, width - 1);
    write_str_repeat_char(buf[0], offset + 1, BOX_HORIZONTAL, width - 2);
    buf[0][offset] = BOX_TOP_LEFT;
    buf[0][offset + width - 1] = BOX_TOP_RIGHT;
    write_str_repeat_char(buf[len - 1], offset, BOX_HORIZONTAL, width);
    buf[len - 1][offset] = BOX_BOTTOM_LEFT;
    buf[len - 1][offset + width - 1] = BOX_BOTTOM_RIGHT;
}

void print_out_nodes(Collection list, FakeNode begin, FakeNode end, wchar_t **buf, int *node_sizes,
                         int *offset, wchar_t *after_node, int starting_size) {
    int i = starting_size;
    FakeNode n;
    for (n = begin; n != end; n = n->next, i++) {
        list_print_node(n, buf, node_sizes[i], get_print_height(), *offset);
        *offset += node_sizes[i];
        if (n->next != end) {
            write_str_center_incr(buf, offset, get_print_height(), after_node, wcslen(after_node));
        }
    }
}

void list_print_general(Collection list, int len, int count, FakeNode forwards,
                FakeNode backwards, int stop, int *node_sizes, wchar_t *after_node,
                wchar_t *start_of_list, wchar_t *end_of_list, wchar_t *ellipses, FakeNode head,
                char *collection_name) {
    terminalSize size = get_terminal_size();
    assert_msg(size.width >= count, "list_helper:list_print_general, size.width (%d) must be >= count (%d)\n", size.width, count);

    // now we have sizes we can allocate buffer and prepare to print list
    // probably going to be a few characters bigger than we need but no harm no foul
    wchar_t **buf = (wchar_t**)malloc_with_oom(sizeof(wchar_t*) * (get_print_height() + get_ptr_height()), "Buffer");
    for (int i = 0; i < get_print_height() + get_ptr_height(); i++) {
        buf[i] = (wchar_t*)malloc_with_oom((count + 1) * sizeof(wchar_t), "Buffer");
        for (int j = 0; j < count; j++) buf[i][j] = ' ';
        buf[i][count] = '\0';
    }

    int offset = 0;
    FakeNode forward_stop = forwards;
    // if everything in the list fits on page
    bool everything_fits = forward_stop == NULL;

    if (head == NULL) {
        write_str_center_incr(buf, &offset, get_print_height(), NULL_NODE, wcslen(NULL_NODE));
    } else {
        write_str_center_incr(buf, &offset, get_print_height(), start_of_list, wcslen(start_of_list));
        print_out_nodes(list, head, forward_stop, buf, node_sizes, &offset, after_node, 0);

        if (!everything_fits) {
            write_str_center_incr(buf, &offset, get_print_height(), after_node, wcslen(after_node));
            write_str_center_incr(buf, &offset, get_print_height(), ellipses, wcslen(ellipses));
            int backwards_start = len;
            backwards = backwards->next;
            for (FakeNode n = backwards; n != NULL; n = n->next) backwards_start--;
            print_out_nodes(list, backwards, NULL, buf, node_sizes, &offset, after_node, backwards_start);
        }

        // print end character
        write_str_center_incr(buf, &offset, get_print_height(), end_of_list, wcslen(end_of_list));
    }

    printf("%s: %s\n", collection_name, list->name);
    for (int i = 0; i < get_print_height(); i++) {
        printf("%ls\n", buf[i]);
        free(buf[i]);
    }
    for (int i = get_print_height(); i < get_ptr_height() + get_print_height(); i++) {
        bool found_non_space = false;
        for (int j = 0; j < count; j++) {
            if (buf[i][j] != ' ') {
                found_non_space = true;
                break;
            }
        }
        if (found_non_space) printf("%ls\n", buf[i]);
        free(buf[i]);
    }

    assert_msg(offset == count, "list_helper:list_print_general, "
                                "we promised to print out %d characters and "
                                "printed out just %d\n", count, offset);
    printf("\n");

    free(buf);
    free(node_sizes);
}

#define LL_AFTER_NODE (select_str_unicode(L" ➢ ", L" -> "))
#define LL_AFTER_NODE_LEN (wcslen(LL_AFTER_NODE))

// This used to be `NULL_NODE " <- "` but I've made it empty (but still a definition)
// Since I felt that wasn't really what a linked list should look like as there is no
// previous pointer on the first member.  However the code will still work if reverted
// just incase it turns out we want this to look like it used to or some other way.
#define LL_START_OF_LIST (L"")
#define LL_START_OF_LIST_LEN (wcslen(LL_START_OF_LIST))
#define LL_END_OF_LIST (select_str_unicode(L" ➢ " NULL_NODE, L" -> " NULL_NODE))
#define LL_END_OF_LIST_LEN (wcslen(LL_END_OF_LIST))
#define LL_ELLIPSES (select_str_unicode(L"... ➢ ", L"... -> "))
#define LL_ELLIPSES_LEN (wcslen(LL_ELLIPSES))

void ll_print_list(Collection list);

LL ll_new(char *name) {
    LL ll = (LL)malloc_with_oom(sizeof(struct _singly_linked_list_t), "LL");
    ll->parent.name = name;
    ll->head = ll->tail = NULL;
    ll->parent.list_printer = ll_print_list;
    ll->parent.get_sizeof = list_sizeof;
    ll->parent.node_printer = list_print_node;
    return ll;
}

void ll_free(LL list) {
    ll_clear(list);
    free(list);
}

void ll_free_node(LL_Node n) {
    // should help catch any dereferencing memory that can't be accessed.
    n->next = NULL;
    free(n);
}

LL_Node ll_new_node(Data data, TypeTag type) {
    LL_Node new_node = (LL_Node)malloc_with_oom(sizeof(struct _LL_node_t), "LL LL_Node");
    new_node->next = NULL;
    new_node->data = data;
    new_node->data_tag = type;
    new_node->ptr = NULL;
    return new_node;
}

void ll_push(LL list, LL_Node n) {
    ll_insert_before(list, n, list->head);
}

LL_Node ll_pop(LL list) {
    return ll_remove_node(list, list->head);
}

void ll_append(LL list, LL_Node n) {
    ll_insert_after(list, n, list->tail);
}

void ll_clear(LL list) {
    for (LL_Node cur = list->head; cur != NULL;) {
        LL_Node temp = cur;
        cur = cur->next;
        free(temp);
    }
    list->head = list->tail = NULL;
}

void ll_insert_after(LL list, LL_Node node, LL_Node at) {
    node->next = NULL;
    if (at == NULL) {
        list->tail = list->head = node;
    } else {
        LL_Node post_at = at->next;
        // at -> post_at => at -> node -> post_at;
        node->next = post_at;
        at->next = node;
        if (post_at == NULL) list->tail = node;
    }
}

void ll_insert_before(LL list, LL_Node node, LL_Node at) {
    node->next = NULL;
    if (at == NULL) {
        list->tail = list->head = node;
    } else {
        LL_Node at_prev = NULL;
        if (at == list->head) {
            list->head = node;
        } else {
            LL_Node at_prev = ll_find_prev(list, at);
            // at_prev -> at => at_prev -> node -> at
            at_prev->next = node;
        }
        node->next = at;
    }
}

LL_Node ll_remove_node(LL list, LL_Node node) {
    if (node == NULL) return NULL;

    LL_Node at_prev;
    if (node == list->head) {
        list->head = node->next;
        at_prev = NULL;
    } else {
        at_prev = ll_find_prev(list, node);
        if (at_prev == NULL) return NULL;
        at_prev->next = node->next;
    }
    if (node == list->tail) {
        list->tail = at_prev;
    }
    node->next = NULL;
    return node;
}

bool ll_is_empty(LL list) {
    return list->head == NULL;
}

LL_Node ll_find_prev(LL list, LL_Node at) {
    if (at != NULL) {
        bool found;
        LL_Node cur;
        for (cur = list->head; cur != NULL; cur = cur->next) {
            if (cur->next == at) return cur;
        }
    }
    return NULL;
}

LL_Node ll_find_next(LL_Node n) {
    if (n == NULL) return NULL;
    return n->next;
}

int *ll_attempt_fit(LL list, int len, terminalSize size, int *out_count,
                    LL_Node *out_forwards, LL_Node *out_backwards, int *out_stop) {
    int *node_sizes = (int*)malloc_with_oom(sizeof(int) * len, "node_sizes");

    if (ll_is_empty(list)) {
        *out_stop = 0;
        *out_count = NULL_NODE_LEN;
        return node_sizes;
    }

    *out_count = LL_START_OF_LIST_LEN + NULL_NODE_LEN;
    *out_stop = 0;
    for (; *out_forwards != NULL; *out_forwards = (*out_forwards)->next, (*out_stop)++) {
        node_sizes[*out_stop] = list->parent.get_sizeof(*out_forwards);
        *out_count += node_sizes[*out_stop] + LL_AFTER_NODE_LEN;
    }

    // if we fit on screen then exit, we won't use out_backwards!
    if (*out_count <= size.width) {
        return node_sizes;
    }

    *out_count = NULL_NODE_LEN + LL_ELLIPSES_LEN + LL_START_OF_LIST_LEN;
    *out_stop = 0;
    *out_forwards = list->head;

    // how far backwards we can go
    int backwards_index = 0;
    bool broke_due_to_size = false;
    // Account for odd lists by including the extra element on the left side
    for (; *out_stop < (len + 1) / 2; (*out_stop)++) {
        int forward_size = node_sizes[*out_stop] + LL_AFTER_NODE_LEN;
        if (forward_size + *out_count > size.width) {
            broke_due_to_size = true;
            break;
        }
        *out_forwards = (*out_forwards)->next;
        *out_count += forward_size;

        if (*out_stop == len / 2) break;

        int backward_size = node_sizes[len - 1 - *out_stop] + LL_AFTER_NODE_LEN;
        if (backward_size + *out_count > size.width) {
            broke_due_to_size = true;
            break;
        }
        *out_count += backward_size;
        backwards_index++;
    }

    if (*out_stop == 0 && broke_due_to_size) {
        printf("Error: No valid sizing constraint matches terminal size; i.e. increase your terminal size since on current size can't even fit the bare minimum\n");
        exit(1);
    }

    // we need to actually traverse the list
    // find middle
    LL_Node middle = list->head;
    for (int i = 0; i < len / 2; i++) middle = middle->next;
    *out_backwards = middle;

    // now go forwards from backwards (len / 2) - backwards_index times
    for (int i = len / 2; i < len - 1 - backwards_index; i++) {
        *out_backwards = (*out_backwards)->next;
    }

    return node_sizes;
}

int ll_length(LL list) {
    int count = 0;
    for (LL_Node n = list->head; n != NULL; n = n->next) count++;
    return count;
}

void ll_print_list(Collection list) {
    LL ll = (LL)list;
    int len = ll_length(ll);
    int count;
    int stop;
    LL_Node forwards = ll->head;
    LL_Node backwards = ll->tail;
    terminalSize size = get_terminal_size();
    int *node_sizes = ll_attempt_fit(ll, len, size, &count, &forwards,
                                     &backwards, &stop);
    list_print_general(list, len, count, (FakeNode)forwards,
                       (FakeNode)backwards, stop, node_sizes, LL_AFTER_NODE,
                       LL_START_OF_LIST, LL_END_OF_LIST, LL_ELLIPSES,
                       (FakeNode)ll->head, "Linked List");
}

Queue queue_new(char *name) {
    return ll_new(name);
}

void queue_free(Queue queue) {
    ll_free(queue);
}

void queue_free_node(QueueNode n) {
    ll_free_node(n);
}

void queue_clear(Queue queue) {
    ll_clear(queue);
}

int queue_length(Queue queue) {
    return ll_length(queue);
}

int queue_is_empty(Queue queue) {
    return ll_is_empty(queue);
}

QueueNode queue_new_node(Data data, TypeTag type) {
    return ll_new_node(data, type);
}

void queue_enqueue(Queue queue, QueueNode node) {
    ll_append(queue, node);
}

QueueNode queue_dequeue(Queue queue) {
    return ll_pop(queue);
}

Data data_int(long long data) {
    return (Data){.int_data = data};
}

Data data_flt(double data) {
    return (Data){.flt_data = data};
}

Data data_str(char *data) {
    return (Data){.str_data = data};
}

Data data_any(void *data) {
    return (Data){.any_data = data};
}

#include <stdarg.h>

typedef struct _ll_visual_t {
    void *node;
    char *ptr_name;
    struct _ll_visual_t *next;
} *VisualNode;

VisualNode visual_ptrs = NULL;

void update_collection(Collection c);

void print_border(void) {
    terminalSize size = get_terminal_size();
    for (int i = 0; i < size.width; i++) printf("%lc", BOX_HORIZONTAL);
    printf("\n");
}

void attach_ptr(void *node, char *ptr) {
    VisualNode visual_node = (VisualNode)malloc_with_oom(sizeof(struct _ll_visual_t), "FakeNode");
    visual_node->node = node;
    visual_node->ptr_name = ptr;
    visual_node->next = visual_ptrs;
    visual_ptrs = visual_node;
}

bool deattach_ptr(void *node, char *ptr) {
    VisualNode prev = NULL;
    for (VisualNode n = visual_ptrs; n != NULL; prev = n, n = n->next) {
        if (n->node == node && !strcmp(n->ptr_name, ptr)) {
            if (prev == NULL)   visual_ptrs = n->next;
            else                prev->next = n->next;
            free(n);
            return true;
        }
    }
    return false;
}

void input_wait(char *fmt, va_list args) {
    // sleep time doesn't effect this
    for (char *a = fmt; *a != '\0'; a++) {
        if (*a == '%') {
            assert((*(++a) == 'i') && "%i must be the last of the fmt");
            switch (*(++a)) {
                case 'i': {
                    printf("Enter an integer: ");
                    int *i = va_arg(args, int*);
                    scanf("%d", i);
                } break;
                case 'l': {
                    printf("Enter a long integer: ");
                    long *i = va_arg(args, long*);
                    scanf("%ld", i);
                } break;
                case 'c': {
                    printf("Enter a character: ");
                    char *c = va_arg(args, char*);
                    scanf("%c", c);
                } break;
                case 's': {
                    printf("Enter a string: ");
                    char *str = va_arg(args, char*);
                    scanf("%s", str);
                } break;
                case 'f': {
                    printf("Enter a floating pointer number: ");
                    double *flt = va_arg(args, double*);
                    scanf("%lf", flt);
                } break;
                default: {
                    printf("Unknown %c", *a);
                }
            }
        }
    }
}

void update_wait(void) {
    // wait either a set amount of time or till key press
    if (get_sleep_time() > 0) sleep_ms(get_sleep_time());
    else {
        printf("\nType enter to continue...\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void update_ptrs(bool remove) {
    for (VisualNode n = visual_ptrs; n != NULL; n = n->next) {
        if (n->node != NULL) {
            // yeh... ouchy, basically all collection nodes
            // can implicitly downcast to just a char* so we can grab
            // a ptr to a node (which is a ptr to a ptr to a struct) and cast
            char **downcast = *(char***)n->node;
            if (downcast != NULL) *downcast = remove ? NULL : n->ptr_name;
        } else {
            // if that's NULL there is no chance it is going to go un-null
            deattach_ptr(n->node, n->ptr_name);
        }
    }
}

void fmt_update(char *fmt, ...) {
    if (clear_on_update()) clear_screen();
    print_border();
    va_list list;
    va_start(list, fmt);
    update_ptrs(false);

    for (char *a = fmt; *a != '\0'; a++) {
        if (*a == '%') {
            switch (*(++a)) {
                case 'n': {
                    // single node
                    FakeNode n = va_arg(list, FakeNode);
                    print_out_single_box(n, list_print_node, list_sizeof,
                                         get_print_height());
                } break;
                case 'l': {
                    Collection c = va_arg(list, Collection);
                    update_collection(c);
                } break;
                case 's': {
                    char *str = va_arg(list, char *);
                    printf("%s\n", str);
                } break;
                case 'i': {
                    a--; // go back to `%`
                    update_ptrs(true);
                    print_border();
                    input_wait(a, list);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    va_end(list);
                } return;
            }
        }
    }
    update_ptrs(true);
    va_end(list);
    print_border();
    update_wait();
}

void clear_screen(void) {
    system(CLEAR_SCREEN);
}

void update(int number, ...) {
    if (clear_on_update()) clear_screen();
    print_border();
    va_list list;
    va_start(list, number);
    update_ptrs(false);
    for (int i = 0; i < number; i++) {
        Collection c = va_arg(list, Collection);
        update_collection(c);
    }
    va_end(list);
    update_ptrs(true);
    print_border();
    update_wait();
}

void print_out_single_box(void *node, fn_print_node printer, fn_sizeof_node sizeof_n, int height) {
    wchar_t **buf = (wchar_t**)malloc_with_oom(sizeof(wchar_t *) * (height + get_ptr_height()), "Single");
    int count = sizeof_n(node);
    for (int i = 0; i < height + get_ptr_height(); i++) {
        buf[i] = (wchar_t*)malloc_with_oom(sizeof(wchar_t) * (count + 1), "Single");
        for (int j = 0; j < count; j++) buf[i][j] = ' ';
        buf[i][count] = '\0';
    }
    printer(node, buf, count, height, 0);

    for (int i = 0; i < height; i++) {
        printf("%ls\n", buf[i]);
        free(buf[i]);
    }
    for (int i = height; i < get_ptr_height() + height; i++) {
        if (include_ptrs_on_single()) {
            bool found_non_space = false;
            for (int j = 0; j < count; j++) {
                if (buf[i][j] != ' ') {
                    found_non_space = true;
                    break;
                }
            }
            if (found_non_space) printf("%ls\n", buf[i]);
        }
        free(buf[i]);
    }
    free(buf);
}

void print_out_single_box_using_defaults(void *node, Collection c) {
    print_out_single_box(node, c->node_printer, c->get_sizeof, get_print_height());
}

void update_collection(Collection c) {
    c->list_printer(c);
}

#include <ctype.h>
#include <locale.h>

#ifdef WINDOWS_COMPATIBILITY
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>

    // https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
    #if _POSIX_C_SOURCE >= 199309L
        #include <time.h>
    #else
        #define POSIX_LEGACY
    #endif
#endif

void write_str_center_of_buf(wchar_t **buf, int offset, int len,
                             wchar_t *str, int str_len) {
    write_str_to_buf(buf, offset, len, len / 2, str, str_len);
}

void write_str_to_buf(wchar_t **buf, int offset, int len, int index,
                      wchar_t *str, int str_len) {
    memcpy(buf[index] + offset, str, str_len * sizeof(wchar_t));
}

terminalSize get_terminal_size(void) {
    int cols, rows;
    #ifdef WINDOWS_COMPATIBILITY
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        cols = w.ws_col;
        rows = w.ws_row;
    #endif

    // this effects debuggers/tests
    if (cols == 0 || testing_activated()) {
        cols = get_default_term_width();
        rows = get_default_term_height();
    }

    return (terminalSize){.width = cols, .height = rows};
}

void sleep_ms(int ms) {
    #ifdef WINDOWS_COMPATIBILITY
        Sleep(ms);
    #elif defined(POSIX_LEGACY)
        // use timeout as opposed to usleep
        struct timeval tv = { .tv_sec = ms / 1000, .tv_usec = (ms % 1000) * 1000 };
        select(0, NULL, NULL, NULL, &tv);
    #else
        struct timespec ts = { .tv_sec = ms / 1000, .tv_nsec = (ms % 1000) * 1000000 };
        nanosleep(&ts, NULL);
    #endif
}

/*
    @Refactor: maybe could include `__FILE__:__LINE__` instead of the obj_name??
               would have to make this a macro in that case (to get the file/line right)
*/
void *malloc_with_oom(size_t size, char *obj_name) {
    void *obj = malloc(size);
    if (obj == NULL) {
        printf("Error: OOM; can't allocate %zu bytes for %s\n", size, obj_name);
        exit(1);
    }
    return obj;
}

void write_str_repeat_char(wchar_t *buf, int offset, wchar_t c, int count) {
    for (int i = 0; i < count; i++) buf[i + offset] = c;
}

void write_str_repeat_char_vert(wchar_t **buf, int offset, wchar_t c, int count, int index) {
    for (int i = 0; i < count; i++) buf[i][index + offset] = c;
}

void write_str_repeat_char_grid(wchar_t **buf, int offset, wchar_t c, int vert_count,
                                int horiz_count, int index) {
    for (int i = 0; i < horiz_count; i++) {
        write_str_repeat_char_vert(buf, offset, ' ', vert_count, i + index);
    }
}

bool supports_unicode() {
    if (unicode_disabled()) return false;
    #ifdef UNIX_COMPATIBILITY
    // @OS BUG: for some reason we need to set the locale on unix systems
    // (not all just high sierra and ubuntu so far) otherwise nothing is printed.
    setlocale(LC_ALL, "");
    #endif

    if (force_unicode()) return true;
    return unicode_in_lang();
}

bool contains_utf(char *str) {
    // just looks for 'utf'
    // not necessarily always true but I haven't seen a case of a false positive
    // just false negatives so for the default value of false it won't ever cause issues
    for (int i = 0; str[i] != '\0' && str[i + 1] != '\0' && str[i + 2] != '\0'; i++) {
        if (tolower(str[i]) == 'u' && tolower(str[i + 1]) == 't' &&
            tolower(str[i + 2]) == 'f') {
            return true;
        }
    }
    return false;
}

wchar_t select_char_unicode(wchar_t unicode, wchar_t backup) {
    return supports_unicode() ? unicode : backup;
}

wchar_t *select_str_unicode(wchar_t *unicode, wchar_t *backup) {
    return supports_unicode() ? unicode : backup;
}

bool str_icase_eql(char *a, char *b) {
    int i;
    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    // if they are different lengths
    if (a[i] != '\0' || b[i] != '\0') return false;
    return true;
}

bool atob(char *str) {
    if (str_icase_eql(str, "true") || str_icase_eql(str, "false")) {
        return true;
    }
    int res = atoi(str);
    if (res == 1 || res == 0) return res;
    return false;
}

void assert_msg(bool expr, char *fmt, ...) {
#ifndef NDEBUG
    if (!expr) {
        printf("Assert Failed!\n");
        va_list(args);
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
#endif
}

#undef new_env_var
#define new_env_var(name, env_name, type, default_value, process_fn) \
    type name(void) { \
        bool defined = false; \
        type previous = default_value; \
        if (!defined) { \
            defined = true; \
            char *str = getenv(#env_name); \
            if (str != NULL) previous = process_fn(str); \
        } \
        return previous; \
    }

new_env_var(get_print_height, LLV_PRINT_HEIGHT, int, 5, atoi);
new_env_var(get_ptr_height, LLV_PTR_HEIGHT, int, 2, atoi);
new_env_var(unicode_in_lang, LANG, bool, false, contains_utf)
new_env_var(get_sleep_time, LLV_SLEEP_TIME, int, 0, atoi);
new_env_var(clear_on_update, LLV_CLEAR_ON_UPDATE, bool, true, atob);
new_env_var(unicode_disabled, LLV_DISABLE_UNICODE, bool, false, atob);
new_env_var(include_ptrs_on_single, LLV_INCLUDE_PTRS_ON_SINGLE_BOX, bool, false, atob);
new_env_var(get_default_term_width, LLV_DEFAULT_TERM_WIDTH, int, 80, atoi);
new_env_var(get_default_term_height, LLV_DEFAULT_TERM_HEIGHT, int, 80, atoi);
new_env_var(testing_activated, LLV_TESTING, bool, false, atob);
new_env_var(force_unicode, LLV_FORCE_UNICODE, bool, false, atob);

#define DLL_AFTER_NODE (select_str_unicode(L" ⟺   ", L" <-> "))
#define DLL_AFTER_NODE_LEN (wcslen(DLL_AFTER_NODE))
#define DLL_START_OF_LIST (select_str_unicode(NULL_NODE L" ⟺  ", NULL_NODE L" <-> "))
#define DLL_START_OF_LIST_LEN (wcslen(DLL_START_OF_LIST))
#define DLL_END_OF_LIST (select_str_unicode(L" ⟺   " NULL_NODE, L" <-> " NULL_NODE))
#define DLL_END_OF_LIST_LEN (wcslen(DLL_END_OF_LIST))
#define DLL_ELLIPSES (select_str_unicode(L"... ⟺   ", L"... <-> "))
#define DLL_ELLIPSES_LEN (wcslen(DLL_ELLIPSES))

void dll_print_list(Collection collection);

DLL dll_new(char *name) {
    DLL dll = (DLL)malloc_with_oom(sizeof(struct _doubly_linked_list_t), "DLL");
    dll->parent.name = name;
    dll->head = dll->tail = NULL;
    dll->parent.list_printer = dll_print_list;
    dll->parent.get_sizeof = list_sizeof;
    dll->parent.node_printer = list_print_node;
    return dll;
}

void dll_free(DLL list) {
    dll_clear(list);
    free(list);
}

void dll_free_node(DLL_Node n) {
    // should help catch any dereferencing memory that can't be accessed.
    n->next = NULL;
    n->prev = NULL;
    free(n);
}

DLL_Node dll_new_node(Data data, TypeTag type) {
    DLL_Node new_node = (DLL_Node)malloc_with_oom(sizeof(struct _dll_node_t), "DLL_Node");
    new_node->next = new_node->prev = NULL;
    new_node->data = data;
    new_node->data_tag = type;
    new_node->ptr = NULL;
    return new_node;
}

void dll_push(DLL list, DLL_Node n) {
    dll_insert_before(list, n, list->head);
}

DLL_Node dll_pop(DLL list) {
    return dll_remove_node(list, list->head);
}

void dll_append(DLL list, DLL_Node n) {
    dll_insert_after(list, n, list->tail);
}

void dll_clear(DLL list) {
    for (DLL_Node cur = list->head; cur != NULL;) {
        DLL_Node temp = cur;
        cur = cur->next;
        free(temp);
    }
    list->head = list->tail = NULL;
}

void dll_insert_after(DLL list, DLL_Node node, DLL_Node at) {
    node->next = NULL;
    if (at == NULL) {
        list->tail = list->head = node;
    } else {
        DLL_Node post_at = at->next;
        // at -> post_at => at -> node -> post_at;
        node->next = post_at;
        at->next = node;
        node->prev = at;
        if (post_at == NULL) list->tail = node;
    }
}

void dll_insert_before(DLL list, DLL_Node node, DLL_Node at) {
    if (at == list->head) {
        list->head = node;
        node->prev = NULL;
        node->next = at;
        if (at != NULL) {
            at->prev = node;
        }
    } else if (at != NULL) {
        at->prev->next = node;
        node->next = at;
        at->prev = node;
    }
}

DLL_Node dll_remove_node(DLL list, DLL_Node node) {
    if (node == NULL) return NULL;
    bool found = false;
    for (DLL_Node c = list->head; c != NULL && !found; c = c->next) {
        found = (c == node);
    }
    if (!found) return NULL;

    if (list->head == node) {
        list->head = node->next;
    }
    if (list->tail == node) {
        list->tail = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    node->next = node->prev = NULL;
    return node;
}

int dll_is_empty(DLL list) {
    return list->head == NULL;
}

DLL_Node dll_find_prev(DLL_Node at) {
    if (at == NULL) return NULL;
    return at->prev;
}

DLL_Node dll_find_next(DLL_Node n) {
    if (n == NULL) return NULL;
    return n->next;
}

int dll_length(DLL list) {
    int count = 0;
    for (DLL_Node n = list->head; n != NULL; n = n->next) count++;
    return count;
}

int *dll_attempt_fit(DLL list, int len, terminalSize size, int *out_count,
                    DLL_Node *out_forwards, DLL_Node *out_backwards, int *out_stop) {
    int *node_sizes = (int*)malloc_with_oom(sizeof(int) * len, "node_sizes");

    if (dll_is_empty(list)) {
        *out_stop = 0;
        *out_count = NULL_NODE_LEN;
        return node_sizes;
    }

    *out_count = DLL_START_OF_LIST_LEN + NULL_NODE_LEN + DLL_ELLIPSES_LEN;
    *out_stop = 0;
    *out_forwards = list->head;
    *out_backwards = list->tail;

    // only go through half the list
    bool broke_due_to_size = false;
    for (; *out_stop < (len + 1) / 2; (*out_stop)++) {
        node_sizes[*out_stop] = list->parent.get_sizeof(*out_forwards);
        int forward_size = node_sizes[*out_stop] + DLL_AFTER_NODE_LEN;
        if (*out_count + forward_size > size.width) {
            broke_due_to_size = true;
            break;
        }

        *out_count += forward_size;
        *out_forwards = (*out_forwards)->next;

        if (*out_stop == len / 2) break;

        node_sizes[len - 1 - *out_stop] = list->parent.get_sizeof(*out_backwards);
        int backward_size = node_sizes[len - 1 - *out_stop] + DLL_AFTER_NODE_LEN;
        if (*out_count + backward_size > size.width) {
            broke_due_to_size = true;
            break;
        }

        *out_count += backward_size;
        *out_backwards = (*out_backwards)->prev;
    }

    if (*out_stop == 0 && broke_due_to_size) {
        printf("Error: No valid sizing constraint matches terminal size; i.e. "
               "increase your terminal size since on current size can't even "
               "fit the bare minimum\n");
        exit(1);
    }

    if (!broke_due_to_size) {
        // go through entire list
        *out_forwards = NULL;
        *out_backwards = NULL;
        *out_count -= DLL_ELLIPSES_LEN;
    }

    return node_sizes;
}

void dll_print_list(Collection list) {
    DLL dll = (DLL)list;
    int len = dll_length(dll);
    int count;
    int stop;
    DLL_Node forwards = dll->head;
    DLL_Node backwards = dll->tail;
    terminalSize size = get_terminal_size();
    int *node_sizes = dll_attempt_fit(dll, len, size, &count, &forwards,
                                      &backwards, &stop);
    list_print_general(list, len, count, (FakeNode)forwards,
                       (FakeNode)backwards, stop, node_sizes, DLL_AFTER_NODE,
                       DLL_START_OF_LIST, DLL_END_OF_LIST, DLL_ELLIPSES,
                       (FakeNode)dll->head, "Doubly Linked List");
}

int log10_int(int num) {
    int log = 0;
    while (num >= 10) {
        num /= 10;
        log++;
    }
    return log;
}

int sizeof_uint(unsigned long long int n) {
    return (n == 0) ? 1 : log10_int(n) + 1;
}

int sizeof_int(long long int n) {
    if (n < 0) {
        return sizeof_uint(n * -1) + 1;
    } else {
        return sizeof_uint(n);
    }
}

int sizeof_flt(double flt) {
    wchar_t buf[MAX_SIZE_FLT];
    int res = swprintf(buf, MAX_SIZE_FLT, L"%.5g", flt);
    if (res < 0) {
        fprintf(stderr, "BUG IN FLT PRINTER\n");
        abort();
    }
    return (int)res;
}

int sizeof_data(Data data, TypeTag tag) {
    int node_size = 0;
    switch (tag) {
        case FLOAT: {
            node_size = sizeof_flt(data.flt_data);
        } break;
        case STRING: {
            node_size = strlen(data.str_data);
        } break;
        case INTEGER: {
            node_size = sizeof_int(data.int_data);
        } break;
        case ANY: {
            node_size = sizeof_uint((size_t)data.any_data);
        } break;
    }
    return node_size;
}

void write_str_center_incr(wchar_t **buf, int *offset, int len,
                           wchar_t *str, int str_len) {
    write_str_center_of_buf(buf, *offset, len, str, str_len);
    *offset += str_len;
}

#endif

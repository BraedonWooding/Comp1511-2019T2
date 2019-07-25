Let us begin by looking at why we need linked lists; what is the motivation behind them...

## Arrays and their shortcomings

If you understand arrays/dynamic arrays well just jump to the [linked list](#linked_lists) section.

Let us just quickly recap memory layout if we have the following program;

```c
int main(void) {
    int number = 2;
    int intArray[5] = {1, 2, 3, 4, 0};
    char stringArray[4] = "hey";
    return 0;
}
```

In memory it looks something like (to save horizontal space I'm going to just include 8 bits - in reality integers are 32 bits);

```
| 0000 0010 (2) | 0000 0001 (1) | 0000 0010 (2) | 0000 0011 (3) | 0000 0100 (4) | 0000 0000 (0) | 0110 1000 ('h') | 0110 0101 ('e') | 0111 1001 ('y') | 0000 0000 ('\0') |
```

Now as you can see it is very compact and interestingly enough if you do; `intArray[-1]` you will get `2` (note: dcc will give you an error cause it is out of bounds; if you want to run this you need to tell the compiler 'shush its okay' and use gcc like; `gcc -o0 my_file.c -o output_file`).

The problem is however is that our arrays are always going to be size 5; what if we want to increase the size of the array?  Such as adding a pokemon to a pokedex?

Well using malloc we can!

## Dynamic Arrays

```c
#include <stdlib.h>

int main(void) {
    // from lectures!  Ask the OS for 10 integers
    // and take a pointer to the first one
    int *array = malloc(sizeof(int) * 10);
    int i = 0;
    while (i < 10) {
        array[i] = i * 2;
        i++;
    }
    // Ends up with [0, 2, 4, 6, 8, 10, ...] and so on
    // What if we want to make this array have another 10 elements??
    // Why don't we reallocate the array!
    // But we can't just free the old array so we have to kind of swap it
    // like when you were swapping two variables
    int *temp = malloc(sizeof(int) * 20);
    // now we can copy over the old array
    i = 0;
    while (i < 10) {
        temp[i] = array[i];
        i++;
    }
    // since we have copied it over we no longer need array
    // we no longer need this memory
    free(array);
    array = temp;
    // now we can add our new 10 elements
    i = 10;
    while (i < 20) {
        array[i] = i * i;
        i++;
    }

    return 0;
}
```

What does this look like in memory;

First the stack (which is basically everything that isn't malloc'd) is only going to have a few variables; first the two pointers (array, temp) and `i`, now I don't know what the pointer values will be at runtime since it'll depend on which memory the OS gives us so I'm just going to do `$1` and `$2` to represent two memory addresses

```
| $1 | 0000 0000 (this is `i` though it'll change throughout the program) | $2 |
```

Notice how the arrays aren't stored on the stack at all!  They are all stored somewhere else called the 'heap' which will look something like this for array;

```
| ??? (random memory) | ??? | 0 | 2 | 4 | 6 | 8 | 10 | 12 | ... | 18 | ??? | ??? |
```

This is one of the key reasons why you have to stay inside the array else you could access memory that doesn't belong to you!  Which could crash the program (and on much old computers even crash the computer!!).

And for temp it will look very similar but will go up to 19^2 like;

```
| ??? (random memory) | 0 | 2 | ... | 20 | 121 | 144 | ... | 324 | 361 | ??? |
```

Do note that the memory above will be in a different location completely to the first set of memory.

Now this clearly is a bit of a pain; every time we increase it we have to move over all the memory and its not very nice.  So what if instead we could build a list (another word for array) where each item is linked to the one after it?

## Linked Lists

Linked lists are like a choose your own adventure book; the ones where you go to a page it has a short bit of text then it lists the next page to go to i.e.;

- Page 01: "You face a giant pikachu whose very surprised at your galaxy brain" - goto page 42
- Page 42: "You jump up and down" - goto page 32
- Page 32: "You start to realise how cool linked lists are" - goto page 55
- Page 55: "The end" - the end of the book no goto page

The nice thing about linked lists is that its very easy to add a new 'page' or 'node' all you have to do is change the last page to point to a new one for example you could change Page 55 to go to page 99 instead of no where and tada you have a new 'node'.

A typical linked list looks like;

```c
struct linked_list {
    // place data here
    struct linked_list *next;
};
```

In the location of `// place data here` you can put any data you want!  You could put a string or a number or even a pokemon...

In the case of the choose your own adventure we would probably have;

```c
#define MAX_TEXT (100)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
    int pageNumber;
    // this could also be 'malloc'd but keeping it simple
    char text[MAX_TEXT];
    struct page *next;
};

// The pokemon.h and pokedex.h describes this pretty well
// it is just like a #define but for type
// everytime we write 'Page' it will replace it with 'struct page *'
typedef struct page *Page;

Page new_page(int number, char *text) {
    Page page = malloc(sizeof(struct page));
    page->pageNumber = number;
    strcpy(page->text, text);
    // SUPER DUPER IMPORTANT
    // always initialise all your
    // next pointers to NULL!!!!
    page->next = NULL;
    return page;
}

void print_pages(Page head) {
    Page cur = head;
    while (cur != NULL) {
        printf("- Page %d: \"%s\" ", cur->pageNumber, cur->text);
        if (cur->next != NULL) {
            // if we aren't the last one print the next pages number
            printf("goto page %d\n", cur->next->pageNumber);
        } else {
            printf("end of book\n");
        }
        cur = cur->next;
    }
    printf("End of book\n");
}

// Adds page to end of list then returns the first item in the list
Page add_to_list(Page head, Page to_add) {
    // if head is NULL then our list will just be to_add
    if (head == NULL) {
        return to_add;
    }

    // Else find the last element;
    Page cur = head;
    // NOTE: we don't want to stop when cur == NULL
    // we want to stop just before then so cur is a valid item
    // so we want to stop when cur->next == NULL
    while (cur->next != NULL) {
        cur = cur->next;
    }
    // okay now we are at the end we can just add it
    cur->next = to_add;
    return head; // the first item hasn't changed!
}

int is_space(int c) {
    // I got some feedback from you guys saying you prefer
    // it written this way rather than;
    // return c == ' ' || c == '\n' || c == '\t';
    if (c == ' ' || c == '\n' || c == '\t') {
        return true;
    } else {
        return false;
    }
}

int main(void) {
    Page head = NULL;
    printf("Enter page number and text: ");
    char text[MAX_TEXT];
    int number;

    while (scanf("%d", &number) > 0 && fgets(text, MAX_TEXT, stdin) != NULL) {
        // remove spaces / newlines at the start / end
        // this may seem a bit complicated so have a good hard think about it
        // for example if we have the string "  hello world \n"
        // then it will have the start string be "hello world\n" then set the \n to \0
        // and we have "hello world"
        char *start = text;
        while (is_space(*start)) {
            start++; // move start to the next memory position
        }
        // remove at the end by just setting '\0'
        int len = strlen(start);
        while (is_space(start[len - 1])) {
            start[len - 1] = '\0';
            len--;
        }
        
        // add page
        head = add_to_list(head, new_page(number, start));
        printf("Enter page number and text: ");
    }
    printf("\n");
    print_pages(head);
    return 0;
}
```

And running it;

```bash
Enter page number and text: 2 grab the plant
Enter page number and text: 5 regret grabbing the plant
Enter page number and text: 9 really regret grabbing the plant
Enter page number and text: 11 oh look a mouse with a weird lighting tail
Enter page number and text: 15 regret touching the weird lighting mouse
Enter page number and text: 19 the end
Enter page number and text: CTRL+D
- Page 2: "grab the plant" goto page 5
- Page 5: "regret grabbing the plant" goto page 9
- Page 9: "really regret grabbing the plant" goto page 11
- Page 11: "oh look a mouse with a weird lighting tail" goto page 15
- Page 15: "regret touching the weird lighting mouse" goto page 19
- Page 19: "the end" end of book
End of book
```

This should be a pretty major hint to help you get started with the labs and assignment!

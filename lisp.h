#ifndef LISP_H
#define LISP_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum { LISP_NUMBER, LISP_OPERATOR, LISP_LIST } lisp_type;

typedef struct lisp_node {
    lisp_type type;
    union {
        int number;
        char operator;
        struct {
            struct lisp_node **list;
            int list_size;
        } list_data;
    } data;
} lisp_node;

lisp_node* lisp_parse(const char *input);
int lisp_eval(lisp_node *node);
void lisp_free(lisp_node *node);

#endif // LISP_H

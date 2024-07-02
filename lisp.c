#include "lisp.h"

static const char* skip_whitespace(const char *input) {
    while (isspace(*input)) input++;
    return input;
}

static lisp_node* lisp_parse_node(const char **input) {
    *input = skip_whitespace(*input);
    if (**input == '(') {
        (*input)++;
        lisp_node *node = (lisp_node *)malloc(sizeof(lisp_node));
        node->type = LISP_LIST;
        node->data.list_data.list_size = 0;
        node->data.list_data.list = NULL;

        while (**input != ')') {
            node->data.list_data.list = (lisp_node **)realloc(node->data.list_data.list, sizeof(lisp_node*) * (node->data.list_data.list_size + 1));
            node->data.list_data.list[node->data.list_data.list_size++] = lisp_parse_node(input);
            *input = skip_whitespace(*input);
        }
        (*input)++;
        return node;
    } else if (isdigit(**input) || (**input == '-' && isdigit((*input)[1]))) {
        int number = strtol(*input, (char **)input, 10);
        lisp_node *node = (lisp_node *)malloc(sizeof(lisp_node));
        node->type = LISP_NUMBER;
        node->data.number = number;
        return node;
    } else if (**input == '+' || **input == '-' || **input == '*' || **input == '/') {
        lisp_node *node = (lisp_node *)malloc(sizeof(lisp_node));
        node->type = LISP_OPERATOR;
        node->data.operator = **input;
        (*input)++;
        return node;
    }

    return NULL;
}

lisp_node* lisp_parse(const char *input) {
    return lisp_parse_node(&input);
}

int lisp_eval(lisp_node *node) {
    if (node->type == LISP_NUMBER) {
        return node->data.number;
    } else if (node->type == LISP_LIST) {
        if (node->data.list_data.list_size == 0) return 0;
        lisp_node *operator_node = node->data.list_data.list[0];
        if (operator_node->type != LISP_OPERATOR) return 0;

        int result = lisp_eval(node->data.list_data.list[1]);
        for (int i = 2; i < node->data.list_data.list_size; i++) {
            switch (operator_node->data.operator) {
                case '+': result += lisp_eval(node->data.list_data.list[i]); break;
                case '-': result -= lisp_eval(node->data.list_data.list[i]); break;
                case '*': result *= lisp_eval(node->data.list_data.list[i]); break;
                case '/': result /= lisp_eval(node->data.list_data.list[i]); break;
            }
        }
        return result;
    }
    return 0;
}

void lisp_free(lisp_node *node) {
    if (node->type == LISP_LIST) {
        for (int i = 0; i < node->data.list_data.list_size; i++) {
            lisp_free(node->data.list_data.list[i]);
        }
        free(node->data.list_data.list);
    }
    free(node);
}

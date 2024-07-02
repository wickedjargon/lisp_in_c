#include "lisp.h"

int main() {
    const char *input = "(/ (* (+ 4 2) 6) 2)";
    lisp_node *root = lisp_parse(input);
    int result = lisp_eval(root);
    printf("Result: %d\n", result);
    lisp_free(root);
    return 0;
}

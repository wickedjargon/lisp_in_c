#include "lisp.h"

int main() {
    const char *input = "(+ (/ (* (+ 4 2) 6) 2) 1)";
    lisp_node *root = lisp_parse(input);
    int result = lisp_eval(root);
    printf("Input s-expression:        %s\n", input);
    printf("evaluated s-expression:    %d\n", result);
    lisp_free(root);
    return 0;
}

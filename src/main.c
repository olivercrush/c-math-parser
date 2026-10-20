#include "../include/token.h"
#include "../include/node.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"<expression>\"", argv[0]);
        return 1;
    }

    TokenList token_list = token_get_from_string(argv[1]);

    Node* root = node_build_tree(token_list);
    node_print(root);
    printf("\n");

    printf("%f", calculate_expression(root));

    token_free(token_list);
    node_free(root);

    return 0;
}

#include "../include/token.h"
#include "../include/node.h"

int main() {
    char expression[] = "4 * 600 / 3 + 84 - 69 * 43 + 709";

    TokenList token_list = token_get_from_string(expression);
    //token_print(token_list);

    Node* root = node_build_tree(token_list);
    node_print(root);

    token_free(token_list);
    node_free(root);

    return 0;
}

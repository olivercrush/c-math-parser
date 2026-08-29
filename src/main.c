#include <stdio.h>
#include <stdlib.h>

enum {
    EXPRESSION,
    TERM,
    OPERATION
};

enum {
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    NO_OP
};

const int OPERATION_LENGTH = 4;
const char OPERATION_TOKENS[] = {
    [ADD] = '+',
    [SUBSTRACT] = '-',
    [MULTIPLY] = '*',
    [DIVIDE] = '/'
};

typedef struct Node {
    int type;
    int data;
    int children_count;
    struct Node **children;
} Node;

int get_operation_token(char token);
Node* create_node(int type);
Node* build_parse_tree(char *expression, int length);
void print_node(Node* root);
void free_node(Node* root);

int main() {
    char expression[] = "1+2*3-5";

    Node* root = build_parse_tree(expression, 7);
    print_node(root);

    free_node(root);
    return 0;
}

int get_operation_token(char token) {
    for (int i = 0; i < OPERATION_LENGTH; i++)
        if (OPERATION_TOKENS[i] == token)
            return i;
    return NO_OP;
}

Node* create_node(int type) {
    Node* root = malloc(sizeof(Node));
    root->type = type;
    root->data = -1;
    root->children_count = 0;
    root->children = NULL;
    return root;
}

Node* build_parse_tree(char *expression, int length) {
    Node* root = create_node(EXPRESSION);
    root->children_count = length;
    root->children = malloc(length * sizeof(Node));

    for (int i = 0; i < length; i++) {
        int operation_token = get_operation_token(expression[i]);

        if (operation_token == NO_OP) {
            Node* term_node = create_node(TERM);
            term_node->data = expression[i] - '0';
            root->children[i] = term_node;
            continue;
        }

        Node* op_node = create_node(OPERATION);
        op_node->data = operation_token;
        root->children[i] = op_node;
    }

    return root;
}

void print_node(Node* node) {
    if (node->type == EXPRESSION)
        for (int i = 0; i < node->children_count; i++)
            print_node(node->children[i]);

    if (node->type == TERM)
        printf("%d ", node->data);

    if (node->type == OPERATION)
        printf("%c ", OPERATION_TOKENS[node->data]);
}

void free_node(Node* node) {
    for (int i = 0; i < node->children_count; i++)
        free_node(node->children[i]);
    free(node);
}

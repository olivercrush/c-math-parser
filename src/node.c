#include "../include/node.h"
#include "../include/operation.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum {
    EXPRESSION,
    TERM,
    OPERATION
};

Node* node_build_tree(TokenList tokenList) {
    Node* root = node_create(EXPRESSION, -1);
    Node* current_expression = root;

    for (int i = 0; i < tokenList.count; i++) {
        char* token = tokenList.tokens[i];

        int operation_id = operation_get_id(token[0]);
        if (operation_id == NO_OP) {

            // Detect new expression
            if (i + 1 < tokenList.count) {
                char* next_op_token = tokenList.tokens[i+1];
                int next_op_id = operation_get_id(next_op_token[0]);
                if (current_expression == root && (next_op_id == MULTIPLY || next_op_id == DIVIDE)) {
                    Node* expression = node_create(EXPRESSION, -1);
                    node_add_child(root, expression);
                    current_expression = expression;
                }
            }

            Node* term = node_create(TERM, (int) strtol(token, NULL, 10));
            node_add_child(current_expression, term);
        }
        else {
            if (operation_id != MULTIPLY && operation_id != DIVIDE)
                current_expression = root;

            Node* op = node_create(OPERATION, operation_id);
            node_add_child(current_expression, op);
        }
    }

    return root;
}

Node* node_create(int type, int data) {
    Node* node = malloc(sizeof(Node));
    node->type = type;
    node->data = data;
    node->children_count = 0;
    node->children_capacity = 0;
    node->children = NULL;
    return node;
}

void node_add_child(Node* parent, Node* child) {
    if (parent->children_capacity == 0) {
        parent->children_capacity = 3;
        parent->children = malloc(sizeof(Node*) * parent->children_capacity);
    }
    else if (parent->children_capacity == parent->children_count) {
        parent->children_capacity += 2;
        parent->children = realloc(parent->children, sizeof(Node*) * parent->children_capacity);
    }

    parent->children[parent->children_count++] = child;
}

void node_print(Node* node) {
    if (node->type == EXPRESSION) {
        printf("(");
        for (int i = 0; i < node->children_count; i++)
            node_print(node->children[i]);
        printf(")");
    }

    if (node->type == TERM)
        printf("%d", node->data);

    if (node->type == OPERATION)
        printf(" %c ", operation_get_char(node->data));
}

void node_free(Node* node) {
    for (int i = 0; i < node->children_count; i++)
        node_free(node->children[i]);
    free(node->children);
    free(node);
}

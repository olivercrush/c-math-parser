#include "token.h"

typedef struct Node {
    int type;
    int data;
    int children_count;
    int children_capacity;
    struct Node **children;
} Node;

Node* node_build_tree(TokenList tokenList);
Node* node_create(int type, int data);
void node_add_child(Node* parent, Node* child);
void node_print(Node* root);
void node_free(Node* root);

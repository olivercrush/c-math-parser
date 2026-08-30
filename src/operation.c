#include "../include/operation.h"

const char OPERATION_TOKENS[] = {
    [ADD] = '+',
    [SUBSTRACT] = '-',
    [MULTIPLY] = '*',
    [DIVIDE] = '/'
};

int operation_get_id(char token) {
    for (int i = 0; i < SUPPORTED_OPERATION_LENGTH; i++)
        if (OPERATION_TOKENS[i] == token)
            return i;
    return NO_OP;
}

char operation_get_char(int id) {
    return OPERATION_TOKENS[id];
}

#pragma once

#define SUPPORTED_OPERATION_LENGTH 4

enum {
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    NO_OP
};

int operation_get_id(char token);
char operation_get_char(int id);

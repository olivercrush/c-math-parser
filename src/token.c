#include "../include/token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/operation.h"

TokenList token_get_from_string(char *expression) {
    expression = token_remove_spaces(expression);

    int is_valid = token_validate(expression);
    if (is_valid == 1) {
        TokenList empty_list = { 0 };
        printf("Invalid expression, returning empty token list");
        return empty_list;
    }

    int length = strlen(expression);

    int next_operation_cursor = 0;
    int current_term_cursor = 0;

    int max_token_count = length;
    char *tokens[max_token_count];

    int token_count = 0;
    while (next_operation_cursor < length) {
        // 1. Find next operation
        do
            next_operation_cursor++;
        while (next_operation_cursor < length && operation_get_id(expression[next_operation_cursor]) == NO_OP);

        // 2. Tokenize term
        int term_length = next_operation_cursor - current_term_cursor;
        if (term_length > 0)
        {
            tokens[token_count] = malloc(term_length + 1);
            memcpy(tokens[token_count], &expression[current_term_cursor], term_length);
            tokens[token_count][term_length] = '\0';
            token_count++;
        }
        current_term_cursor = next_operation_cursor + 1;

        // 3. Tokenize next operation
        if (next_operation_cursor < length) {
            tokens[token_count] = malloc(2);
            memcpy(tokens[token_count], &expression[next_operation_cursor], 1);
            tokens[token_count][1] = '\0';
            token_count++;
        }
    }

    TokenList tokenized = { token_count };
    tokenized.tokens = malloc(token_count * sizeof(char*));

    for (int i = 0; i < token_count; i++)
        tokenized.tokens[i] = tokens[i];

    return tokenized;
}

char* token_remove_spaces(char* expression) {
    int length = strlen(expression);
    for (int i = 0; i < length; i++) {
        if (expression[i] == ' ') {
            for (int j = i; j < length; j++)
                expression[j] = expression[j+1];
            length--;
            i--;
        }
    }

    expression[length] = '\0';
    return expression;
}

int token_validate(char* expression) {
    int length = strlen(expression);

    if (operation_get_id(expression[0]) != NO_OP)
        return 1;

    if (operation_get_id(expression[length - 1]) != NO_OP)
        return 1;

    for (int i = 0; i < length; i++) {
        if (operation_get_id(expression[i]) != NO_OP && operation_get_id(expression[i+1]) != NO_OP) {
            printf("Two sequencial operations : %c %c\n", expression[i], expression[i+1]);
            return 1;
        }

        if (operation_get_id(expression[i]) == NO_OP && !(expression[i] >= '0' && expression[i] <= '9')) {
            printf("Not a digit : %c\n", expression[i]);
            return 1;
        }
    }

    return 0;
}

void token_print(TokenList token_list) {
    for (int i = 0; i < token_list.count; i++) {
        printf("%s", token_list.tokens[i]);
        if (i + 1 < token_list.count)
            printf(" -> ");
    }
}

void token_free(TokenList token_list) {
    for (int i = 0; i < token_list.count; i++)
        free(token_list.tokens[i]);
    free(token_list.tokens);
}

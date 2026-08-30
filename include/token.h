#pragma once

typedef struct TokenList {
    int count;
    char **tokens;
} TokenList;

TokenList token_get_from_string(char *expression);
char* token_remove_spaces(char* expression);
int token_validate(char* expression);
void token_print(TokenList token_list);
void token_free(TokenList token_list);

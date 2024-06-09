#include "token.h"

token *token_new_token(char *str, size_t s_len, int type, size_t line_number){
    token *tok = malloc(sizeof *tok);
    if (tok == NULL){
        printf("No Memory\n");
        exit(EXIT_FAILURE);
    }

    tok->text = malloc(s_len + 1);
    tok->type = type;
    tok->line_number = line_number;

    if (tok->text == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(tok->text, str);

    return tok;
}


#include "token.h"

token *token_new_token(char *str, size_t s_len, int type){
    token *tok = malloc(sizeof *tok);
    if (tok == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    tok->type = type;
    tok->text = malloc(s_len + 1);

    if (tok->text == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    strncpy(tok->text, str, s_len);

    return tok;
}

char *token_get_name(token *tok){
    return "NOT IMPLEMENTED";
}

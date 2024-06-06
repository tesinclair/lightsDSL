#include "token.h"

token token_new_token(char *str, size_t s_len, int type){
    token tok = {
        .type = type,
        .text = malloc(s_len + 1)
    };

    if (tok.text == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(tok.text, str);

    return tok;
}


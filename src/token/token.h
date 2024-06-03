#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum token_types{
    AT,
    R_CURLY_BRACE,
    L_CURLY_BRACE,
    LETTERS,
    SEMI,
    R_PAREN,
    L_PAREN,
    COMMA,
    UNDERSCORE,
    COLON,
    INT,
    FLOAT,
    EQUAL,
    PIPE,
    DOLLAR,
    DASH
};

typedef struct{
    int type;
    char *text;
} token;

// @params: the tokens text, the length of the text, 
//          and the type of the token (defined above)
// @returns: a new token with the defined data
// @errors: errors on no memory
token *token_new_token(char *str, size_t s_len, int type);

// @params: takes a token
// @returns: a string representation fo the token
// @errors: none
char *token_get_name(token *tok);

#endif

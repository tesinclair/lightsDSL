#ifndef TOKEN_H
#define TOKEN_H

#define AT 0
#define R_CURLY_BRACE 1
#define L_CURLY_BRACE 2
#define LETTERS 3
#define SEMI 4
#define R_PAREN 5
#define L_PAREN 6
#define COMMA 7
#define UNDERSCORE 8
#define COLON 9
#define INT 10
#define FLOAT 11
#define EQUAL 12
#define PIPE 13
#define DOLLAR 14
#define DASH 15

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

#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include "../utils/util.h"
#include "../errors/errors.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<math.h>

#ifndef EOF
#define EOF -1
#endif

typedef struct{
    char* input;
    int index;
    char c;
} lexer;

/// @params: takes a string input
/// @returns: a new lexer for that input
/// @errors: returns NULL if input is not given
lexer *lexer_new_lexer(char *input);

/// @params: takes a lexer
/// @returns: returns a token, can be found in token.h
/// @errors: None
token lexer_next_token(lexer *lexer);

/// @params: takes a lexer
/// @returns: a string built from the lexer.
///      the lexers index is moved to the end of the string
/// @errors: panics on no memory
char* lexer_build_string(lexer *lexer);

/// @params: takes a lexer
/// @returns: a built integer, the lexers
///      position is moved to the end of the int
/// @errors: panics on no memory
int lexer_build_int(lexer *lexer);

/// @params: takes a lexer
/// @returns: a built float, the lexers
///      position is moved to the end of the float
/// @errors: panics on no memory
double lexer_build_float(lexer *lexer);

/// @params: takes a lexer
/// @returns: None
/// @errors: None
void lexer_consume(lexer *lexer);

/// @params: lexer, and a character to match
/// @returns: None
/// @errors: throws a lexing error (found in errors.h)
///          if chars don't match
void lexer_match(lexer *lexer, char x);

/// @params: lexer, an integer id for a token (refs found in token.h)
/// @returns: a string name of the token
/// @errors: panics if the token is not found
char* lexer_get_token_name(lexer *lexer, int tokenType);

/// @params: lexer
/// @returns: a token; can be found in token.h
/// @errors: 
token lexer_letters(lexer *lexer);

/// @params: lexer
/// @returns: a list of tokens found in the input stream
/// @errors: does not throw errors itself, 
///          but the functions it calls may
token *lexer_lex(lexer *lexer);

#endif

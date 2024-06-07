#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "../token/token.h"
#include "../errors/errors.h"

typedef struct {
    token *token_stream[];
    token current_token;
    size_t index;
} parser;

/// @Params: a token stream
/// @returns: a new parser starting at the first token in the stream
parser *parser_new_parser(token *token_stream[]);

/// @Params: a parser
/// @Purpose: moved the index and current token to the next
///         in the token_stream
void parser_consume(parser *p);

/// @Params: a token to match and a parser
/// @Errors: Throws a parse error if match is false
void parser_match(parser *p, int token_key, char *token_text);

/// @Params: a parser
/// @Errors: throws parsing error
/// @Function: call to parse the parser
void parser_parse(parser *p);

/// @param: parser
/// @returns True if the current token is the 
///         start of a function else false
int isFunc(parser *p);

/// @Section: these are all the individual parsers

void parser_parse_root(parser *p);

void parser_parse_stat(parser *p);

void parser_parse_pin(parser *p);

void parser_parse_decl(parser *p);

void parser_parse_loop(parser *p);

void parser_parse_range(parser *p);

void parser_parse_val(parser *p);

void parser_parse_func(parser *p);

void parser_parse_assign(parser *p);

void parser_parse_expr(parser *p);

void parser_parse_array(parser *p);

void parser_parse_items(parser *p);

void parser_parse_color(parser *p);

void parser_parse_type(parser *p);

void parser_parse_var(parser *p);

void parser_parse_letters(parser *p);

#endif

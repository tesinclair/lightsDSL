#include "test_parser.h"

void test_parser_new_parser(){
    char *input = "@set { 100 };\n@decl type { strip };\n@decl addressable { 100 };";

    lexer *l = lexer_new_lexer(input);
    token **token_stream = lexer_lex(l);

    free(l);

    parser *p = parser_new_parser(token_stream);

    testing_assert(
            p != NULL,
            "<parser_new_parser> returned \"NULL\". Expected \"parser\"."
            );

    testing_assert(
            p->index == 0,
            "<parser_new_parser> (\"index\") returned \"%d\". Expected \"0\".",
            p->index
            );

    testing_assert(
            p->current_token->type == AT,
            "<parser_new_parser> (\"current_token.type\") returned \"%d\". Expected \"AT\".",
            p->current_token->type
            );

    while (p->token_stream[p->index]->type != EOF){
        free(p->token_stream[p->index]->text);
        free(p->token_stream[p->index]);
        p->index++;
    }

    free(p->token_stream[p->index]->text);
    free(p->token_stream[p->index]);
    free(p->token_stream);
    free(p);
}

void test_parser_is_func(){
    char *input = "@dun { @decl new face };\n@decl type { strip };\n@decl addressable { 100 };";

    lexer *l = lexer_new_lexer(input);
    token **token_stream = lexer_lex(l);

    free(l);

    parser *p = parser_new_parser(token_stream);

    parser_consume(p);
    parser_consume(p);

    testing_assert(
            parser_is_func(p),
            "<parser_is_func> (\"%s\") returned \"FALSE\". Expected \"TRUE\".",
            p->current_token->text
            );
    while (p->token_stream[p->index]->type != EOF){
        free(p->token_stream[p->index]->text);
        free(p->token_stream[p->index]);
        p->index++;
    }
    free(p->token_stream[p->index]->text);
    free(p->token_stream[p->index]);
    free(p->token_stream);
    free(p);
}

void test_parser_with_example(){
    char *input;
    lexer *l;

    input = malloc(1);
    if (input == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    FILE *fptr = fopen("../examples/pulse.lts", "r");
    if (fptr == NULL){
        printf("No file\n");
        exit(EXIT_FAILURE);
    }

    char c;
    size_t index = 0;
    while ((c = fgetc(fptr)) != EOF){
        input[index] = c;

        input = realloc(input, ++index + 1);
    }

    l = lexer_new_lexer(input);
    if (l == NULL){
        printf("\n");
        exit(EXIT_FAILURE);
    }

    token **tokens = lexer_lex(l);

    free(l);
    free(input);

    parser *p = parser_new_parser(tokens);

    parser_parse(p);

    while (p->token_stream[p->index]->type != EOF){
        free(p->token_stream[p->index]->text);
        free(p->token_stream[p->index]);
        p->index++;
    }
    free(p->token_stream[p->index]->text);
    free(p->token_stream[p->index]);
    free(p->token_stream);
    free(p);
}

void test_parser(){
    test_parser_new_parser();
    printf("<test_parser_new_parser> \033[0;32mPASSED\033[0;37m\n");

    test_parser_is_func();
    printf("<test_parser_is_func> \033[0;32mPASSED\033[0;37m\n");

    test_parser_with_example();
    printf("<test_parser_with_example> \033[0;32mPASSED\033[0;37m\n");

}

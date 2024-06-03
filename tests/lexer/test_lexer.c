#include "test_lexer.h"

void test_lexer_build_string(){
    char *buf;

    lexer l_normal = {
        .input = "string",
        .index = 0,
        .c = 's'
    };

    buf = lexer_build_string(&l_normal);

    testing_assert(
            strcmp(buf, "string ") == 0,
            "Failed because <lexer_build_string> returned \"%s\", instead of \"string\"",
            buf
            );

    free(buf);

    lexer l_erroneous= {
        .input = "12345",
        .index = 0,
        .c = '1'
    };

    buf = lexer_build_string(&l_erroneous);

    testing_assert(
            strcmp(buf, "") == 0,
            "Failed because <lexer_build_string> returned \"%s\", instead of \"\"",
            buf
            );

    free(buf);

    lexer l_boundary = {
        .input = "hello",
        .index = 0,
        .c = 'h'
    };

    buf = lexer_build_string(&l_boundary);

    testing_assert(
            strcmp(buf, "hello") == 0,
            "Failed because <lexer_build_string> returned \"%s\", instead of \"hello\"\n\
            Maybe because it failed to stop adding to buf?",
            buf
            );

    free(buf);

    lexer l_sketchy = {
        .input = "hello_world ",
        .index = 0,
        .c = 'h'
    };

    buf = lexer_build_string(&l_sketchy);

    testing_assert(
            strcmp(buf, "hello_world") == 0,
            "Failed because <lexer_build_string> returned \"%s\", instead of \"hello_world\"",
            buf
            );

    free(buf);

    lexer l_complex = {
        .input = "this is example code 12345",
        .index = 8,
        .c = 'e'
    };

    buf = lexer_build_string(&l_complex);

    testing_assert(
            strcmp(buf, "example") == 0,
            "Failed because <lexer_build_string> returned \"%s\", instead of \"example\"",
            buf
            );

    free(buf);

    testing_assert(
            l_complex.index == 15,
            "Failed because <lexer_build_string> did not push the index enough.\n\
            Current index: \"%d\". Expected index: 15",
            l_complex.index 
            );

    printf("Tests passed for <lexer_build_string>");
}

void test_lexer_build_int(){
    int result;

    lexer l_normal = {
        .input = "123 ",
        .index = 0,
        .c = '1'
    };

    result = lexer_build_int(&l_normal);

    testing_assert(
            result == 123,
            "Failed because <lexer_build_int> returned \"%d\" instead of \"123\"",
            result
            );

    lexer l_boundry = {
        .input = "123",
        .index = 0,
        .c = '1'
    };

    result = lexer_build_int(&l_normal);

    testing_assert(
            result == 123,
            "Failed because <lexer_build_int> returned \"%d\" instead of \"123\"\n\
            Maybe because the function didn't stop correctly?",
            result
            );

    lexer l_erroneous = {
        .input = "word",
        .index = 0,
        .c = 'w'
    };

    result = lexer_build_int(&l_normal);

    testing_assert(
            result == -1,
            "Failed because <lexer_build_int> returned \"%d\" instead of \"123\"\n\
            Maybe because the function didn't stop correctly?",
            result
            );

    lexer l_complex = {
        .input = "@this is a number: 102but it ends",
        .index = 19,
        .c = '1'
    };

    result = lexer_build_int(&l_complex);

    testing_assert(
            result == 102,
            "Failed because <lexer_build_int> returned \"%d\" instead of \"102\"",
            result
            );
}

void test_lexer_next_token(){
    token *tok;

    lexer l = {
        .input = "@set { 123;",
        .index = 0,
        .c = '@'
    };

    tok = lexer_next_token(&l);

    testing_assert(
            tok->type == AT,
            "Failed because <next_toke> returned \"%s\" instead of \"@\"",
            tok->text
            );

    free(tok->text);
    free(tok);

    tok = lexer_next_token(&l);

    testing_assert(
            tok->type == LETTERS,
            "Failed because <next_toke> returned \"%s\" instead of \"set\"",
            tok->text
            );

    free(tok->text);
    free(tok);

    tok = lexer_next_token(&l);

    testing_assert(
            tok->type == L_CURLY_BRACE,
            "Failed because <next_toke> returned \"%s\" instead of \"{\"",
            tok->text
            );

    free(tok->text);
    free(tok);

    tok = lexer_next_token(&l);

    testing_assert(
            tok->type == INT,
            "Failed because <next_toke> returned \"%s\" instead of \"123\"",
            tok->text
            );

    free(tok->text);
    free(tok);
        
    tok = lexer_next_token(&l);

    testing_assert(
            tok->type == SEMI,
            "Failed because <next_token> returned \"%s\" instead of \";\"",
            tok->text
            );

    free(tok->text);
    free(tok);

    printf("Tests for <test_lexer_next_token> passed\n");
}

void test_lexer_lex(){
    token **tok_list;

    lexer l = {
        // There is a good change _ will regester as a letter, 
        // which should be fixed
        .input = "@use { 10 };\n@decl type { () _ _word :387 = || --",
        .index = 0,
        .c = '@'
    };

    tok_list = lexer_lex(&l);

    int comparison_list[] = {
        AT, 
        LETTERS, 
        L_CURLY_BRACE, 
        INT, 
        R_CURLY_BRACE, 
        SEMI, 
        AT, 
        LETTERS, 
        LETTERS, 
        L_CURLY_BRACE, 
        L_PAREN,
        R_PAREN,
        UNDERSCORE,
        LETTERS,
        COLON,
        INT,
        EQUAL,
        PIPE,
        PIPE,
        DASH,
        DASH
    };

    size_t comp_list_len = 21;

    for (int i = 0; i < comp_list_len; i++){
        testing_assert(
                comparison_list[i] == tok_list[i]->type,
                "Lexer failed to return %d, returned %d instead for token: %s",
                comparison_list[i],
                tok_list[i]->type,
                tok_list[i]->text
                );
        free(tok_list[i]->text);
        free(tok_list[i]);
    }

    free(tok_list);

    printf("Passed test <test_lexer_lex>\n");
}

void test_lexer(){
    test_lexer_build_string();
    test_lexer_build_int();
    test_lexer_next_token();
    test_lexer_lex();
}

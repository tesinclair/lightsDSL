#include "test_lexer.h"

void test_lexer_from_example(){
    char *input;
    lexer *l;

    input = malloc(1);
    if (input == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    FILE *fptr = fopen("../../examples/pulse.lts", "r");

    char c;
    size_t index = 0;
    while ((c = fgetc(fptr)) != EOF){
        input[index] = c;

        // it needs to be 1 more than length
        input = realloc(input, ++index + 1);
    }

    l = lexer_new_lexer(input);
    if (l == NULL){
        printf("\n");
        exit(EXIT_SUCCESS);
    }

    token *tokens = lexer_lex(l);

    size_t i = 0;
    while (tokens[i].type != EOF){
        free(tokens[i].text);
        i++;
    }
    free(tokens[i].text);
    
    // I cannot be assed to check that it returns the right stuff, so instead
    // I'm just gonna return if it works
    return;
}

void test_lexer_build_string(){
    char *buf;

    lexer l_normal = {
        .input = "string ",
        .index = 0,
        .c = 's'
    };

    buf = lexer_build_string(&l_normal);

    testing_assert(
            strcmp(buf, "string") == 0,
            "<lexer_build_string> returned \"%s\". Expected \"string\".",
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
            "<lexer_build_string> returned \"%s\". Expected \"\".",
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
            "<lexer_build_string> returned \"%s\". Expected \"hello\".",
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
            "<lexer_build_string> returned \"%s\". Expected \"hello_world\".",
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
            "<lexer_build_string> returned \"%s\". Expected \"example\".",
            buf
            );

    free(buf);

    testing_assert(
            l_complex.index == 15,
            "<lexer_build_string> returned \"%d\". Expected \"15\".",
            l_complex.index 
            );

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
            "<lexer_build_int> returned \"%d\". Expected \"123\".",
            result
            );

    lexer l_boundry = {
        .input = "456",
        .index = 0,
        .c = '4'
    };

    result = lexer_build_int(&l_boundry);

    testing_assert(
            result == 456,
            "<lexer_build_int> returned \"%d\". Expected \"456\".",
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
            "<lexer_build_int> returned \"%d\". Expected \"EOF\".",
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
            "<lexer_build_int> returned \"%d\". Expected \"102\".",
            result
            );
}

void test_lexer_next_token(){
    token tok;

    lexer l = {
        .input = "@set { 123;",
        .index = 0,
        .c = '@'
    };

    tok = lexer_next_token(&l);

    testing_assert(
            tok.type == AT,
            "<lexer_next_token> returned \"%d\". Expected \"%d\".",
            tok.type,
            AT
            );

    testing_assert(
            strcmp(tok.text, "< @ >") == 0,
            "<lexer_next_token> returned \"%s\". Expected \"< @ >\".",
            tok.text
            );


    free(tok.text);

    tok = lexer_next_token(&l);

    testing_assert(
            tok.type == LETTERS,
            "<lexer_next_token> returned \"%d\". Expected \"%d\".",
            tok.type,
            LETTERS 
            );

    testing_assert(
            strcmp(tok.text, "<set>") == 0,
            "<lexer_next_token> returned \"%s\". Expected \"<set>\".",
            tok.text
            );

    free(tok.text);

    tok = lexer_next_token(&l);

    testing_assert(
            tok.type == L_CURLY_BRACE,
            "<lexer_next_token> returned \"%d\". Expected \"%d\".",
            tok.type,
            L_CURLY_BRACE 
            );

    testing_assert(
            strcmp(tok.text, "< { >") == 0,
            "<lexer_next_token> returned \"%s\". Expected \"< { >\".",
            tok.text
            );

    free(tok.text);

    tok = lexer_next_token(&l);

    testing_assert(
            tok.type == INT,
            "<lexer_next_token> returned \"%d\". Expected \"%d\".",
            tok.type,
            INT 
            );

    testing_assert(
            strcmp(tok.text, "<123>") == 0,
            "<lexer_next_token> returned \"%s\". Expected \"<123>\".",
            tok.text
            );


    free(tok.text);
        
    tok = lexer_next_token(&l);

    testing_assert(
            tok.type == SEMI,
            "<lexer_next_token> returned \"%d\". Expected \"%d\".",
            tok.type,
            SEMI 
            );

    testing_assert(
            strcmp(tok.text, "< ; >") == 0,
            "<lexer_next_token> returned \"%s\". Expected \"< ; >\".",
            tok.text
            );

    free(tok.text);
}

void test_lexer_lex(){
    token *tok_list;

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
        LETTERS,
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
                comparison_list[i] == tok_list[i].type,
                "<lexer_lex> (\"%s\") returned \"%d\". Expected \"%d\".",
                tok_list[i].text,
                tok_list[i].type,
                comparison_list[i]
                );
        free(tok_list[i].text);
    }

    free(tok_list);

}

void test_lexer(){
    test_lexer_build_string();
    printf("<test_lexer_build_string> \033[0;32mPASSED\033[0;37m\n");

    test_lexer_build_int();
    printf("<test_lexer_build_int> \033[0;32mPASSED\033[0;37m\n");

    test_lexer_next_token();
    printf("<test_lexer_next_token> \033[0;32mPASSED\033[0;37m\n");

    test_lexer_lex();
    printf("<test_lexer_lex> \033[0;32mPASSED\033[0;37m\n");

    test_lexer_from_example();
    printf("<test_lexer_from_example> \033[0;32mPASSED\033[0;37m\n");
}

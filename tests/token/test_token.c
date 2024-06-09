#include "test_token.h"

void test_token_new_token(){
    token *tok;
    size_t line_num = 0;

    tok = token_new_token("< @ >", 5, AT, &line_num);

    testing_assert(
            strcmp(tok->text, "< @ >") == 0,
            "<token_new_token> returned \"%s\". Expected \"< @ >\".",
            tok->text
            );

    testing_assert(
            tok->type == AT,
            "<token_new_token> returned \"%d\". Expected \"%d\".",
            tok->type,
            AT
            );

    free(tok->text);

    char *normal_text = "< ( >";
    size_t normal_size = 5;
    int normal_type = L_PAREN;

    tok = token_new_token(normal_text, normal_size, normal_type, &line_num);

    testing_assert(
            strcmp(tok->text, "< ( >") == 0,
            "<token_new_token> returned \"%s\". Expected \"< ( >\".",
            tok->text
            );

    testing_assert(
            tok->type == L_PAREN,
            "<token_new_token> returned \"%d\". Expected \"%d\".",
            tok->type,
            L_PAREN 
            );

    free(tok->text);
    free(tok);

    tok = token_new_token("<words>", 7, LETTERS, &line_num);

    testing_assert(
            strcmp(tok->text, "<words>") == 0,
            "<token_new_token> returned \"%s\". Expected \"<words>\".",
            tok->text
            );

    testing_assert(
            tok->type == LETTERS,
            "<token_new_token> returned \"%d\". Expected \"%d\".",
            tok->type,
            LETTERS 
            );

    free(tok->text);
}

void test_token(){
    test_token_new_token();
    printf("<test_token_new_token> \033[0;32mPASSED\033[0;37m\n");
}

    

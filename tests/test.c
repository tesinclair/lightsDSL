#include "lexer/test_lexer.h"
#include "utils/test_util.h"
#include "token/test_token.h"
#include "parser/test_parser.h"
#include <stdio.h>

int main(){
    test_util();
    printf("\033[1;32mUtil Tests Passed!\n\n\033[0;37m");

    test_token();
    printf("\033[1;32mToken Tests Passed!\n\n\033[0;37m");

    test_lexer();
    printf("\033[1;32mLexing Tests Passed\n\n\033[0;37m");

    test_parser();
    printf("\033[1;32mParseing Tests Passed\n\n\033[0;37m");

    printf("\n\n\033[1;32m=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("   ALL TESTS PASSED!\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    fflush(stdout);

    return 0;
}

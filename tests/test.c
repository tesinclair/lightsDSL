#include "./lexer/test_lexer.h"
#include "./utils/test_util.h"
#include <stdio.h>

int main(){
    test_util();
    printf("\033[1;32mUtil tests passed!\n");

    test_lexer();
    printf("\033[1;32mLexing tests passed\n\033");

    printf("\n\n\033[1;32m=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("   ALL TESTS PASSED!\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    fflush(stdout);

    return 0;
}

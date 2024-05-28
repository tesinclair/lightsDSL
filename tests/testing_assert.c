#include<stdarg.h>
#include<stdio.h>
#include<assert.h>

void testing_assert(int expr, char *failMsgFormat, ...){
    if (!expr){
        va_list args;

        va_start(args);

        sprintf(stderr, "<Assert Error>: Assertion failed\n");
        sprintf(stderr, failMsgFormat, args);

        va_end(args);
    } 

    assert(expr);
}


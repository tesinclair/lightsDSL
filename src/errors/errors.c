#include <stdarg.h>
#include <stdio.h>

void throw_lexing_error(char *errTextFormat, ErrCode errCode, ...){
    va_list args;

    va_start(args);

    sprintf(stderr, "Now, I'm certain *that* shouldn't be there!\n");
    sprintf(stderr, "<Lexer Error>: %d\n", errCode);
    sprintf(stderr, errTextFormat, args);
    sprintf(stderr, "\n");

    exit(errCode);
}

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void throw_lexing_error(char *errTextFormat, int errCode, ...){
    va_list args;

    va_start(args, NULL);

    fprintf(stderr, "Now, I'm certain *that* shouldn't be there!\n");
    fprintf(stderr, "<Lexer Error>: %d\n", errCode);
    fprintf(stderr, errTextFormat, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(errCode);
}

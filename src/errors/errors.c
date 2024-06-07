#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void throw_lexing_error(char *errTextFormat, int errCode, ...){
    va_list args;

    va_start(args, NULL);

    fprintf(stderr, "\033[1;31m<Error Lexing Code>: \033[0;31m%d\033[0;37m\n\n", errCode);
    vfprintf(stderr, errTextFormat, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(errCode);
}

void throw_lexing_error(char *errTextFormat, int errCode, ...){
    va_list args;

    va_start(args, NULL);

    fprintf(stderr, "\033[1;31m<Error Parsing Code>: \033[0;31m%d\033[0;37m\n\n", errCode);
    vfprintf(stderr, errTextFormat, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(errCode);
}

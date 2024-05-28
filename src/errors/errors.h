#ifndef ERRORS_H
#define ERRORS_H

typedef enum{
    LEXING_ERROR_UNDEFINED = 100,
    LEXING_ERROR_INVALID_CHARACTER,
    LEXING_ERROR_UNEXPECTED_EOF,
} ErrCodes;

// @params: takes a format string error message, an errorcode 
//          (defined above) and var_args of the data to format
// @returns: None
// @errors: causes error of specified error code
void throw_lexing_error(char *errTextFormat, int errCode, ...);

#endif

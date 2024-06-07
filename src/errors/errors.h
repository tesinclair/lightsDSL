#ifndef ERRORS_H
#define ERRORS_H

enum ErrCodes{
    LEXING_ERROR_UNDEFINED = 100,
    LEXING_ERROR_INVALID_CHARACTER,
    LEXING_ERROR_UNEXPECTED_TOKEN,
    LEXING_ERROR_UNEXPECTED_EOF,
    PARSE_ERROR_EOF,
    PARSE_ERROR_UNEXPECTED_TOKEN,
    PARSE_ERROR_PARSE_FAILED
};

/// @params: takes a format string error message, an errorcode 
///          (defined above) and var_args of the data to format
/// @returns: None
/// @errors: causes error of specified error code
void throw_lexing_error(char *errTextFormat, int errCode, ...);

/// @params: takes a format string, and error code and 
///         var args to be printed
/// @errors: throw parsing error
void throw_parse_error(char *errTextFormat, int errCode, ...);

#endif

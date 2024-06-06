#include "lexer.h"

lexer *lexer_new_lexer(char *input){
    if (input == NULL || strlen(input) <= 0){
        return NULL;
    }
    lexer *l = malloc(sizeof *l);

    l->input = input;
    l->index = 0;
    l->c = input[0];

    return l;
}

token *lexer_lex(lexer *lexer){
    token *token_stream;
    token current_token;  
    size_t num_tokens = 0;

    token_stream = malloc(sizeof &current_token);
    if (token_stream == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    current_token = lexer_next_token(lexer);
    num_tokens++;
    size_t index = 0;
    
    while (current_token.type != EOF){
        token_stream[index] = current_token;
        token_stream = realloc(
                token_stream, 
                (num_tokens + 1) * sizeof(current_token) 
                );

        if (token_stream == NULL){
            printf("No memory\n");
            exit(EXIT_FAILURE);
        }
        current_token = lexer_next_token(lexer);
        num_tokens++;
        index++;
    }

    // Should be EOF
    assert(current_token.type == EOF);
    token_stream[index] = current_token;

    return token_stream;
}

token lexer_next_token(lexer *lexer){
    token tok;

    if (lexer->c == EOF){
        tok = token_new_token("<EOF>", 5, EOF);
    }else if (lexer->c == '#'){

        while (lexer->c != '\n'){
            lexer_consume(lexer);

            if (lexer->c == EOF)
                tok = lexer_next_token(lexer);
        }
    }else if (lexer->c == '['){
        while (lexer->c != ']'){
            lexer_consume(lexer);

            if (lexer->c == EOF){
                throw_lexing_error(
                        "Expected \"< ] >\", but found \"< %c >\"",
                        LEXING_ERROR_UNEXPECTED_TOKEN,
                        lexer->c
                        );
            }
        }
        lexer_consume(lexer);
        tok = lexer_next_token(lexer);
    }else{
        switch (lexer->c){
            case ' ': case '\n': case '\t': case '\r':
                lexer_consume(lexer);
                tok = lexer_next_token(lexer);
                break;
            case '@':
                lexer_consume(lexer);
                tok = token_new_token("< @ >", 5, AT);
                break;
            case '}':
                lexer_consume(lexer);
                tok = token_new_token("< } >", 5, R_CURLY_BRACE);
                break;
            case '{':
                lexer_consume(lexer);
                tok = token_new_token("< { >", 5, L_CURLY_BRACE);
                break;
            case ';':
                lexer_consume(lexer);
                tok = token_new_token("< ; >", 5, SEMI);
                break;
            case ')':
                lexer_consume(lexer);
                tok = token_new_token("< ) >", 5, R_PAREN);
                break;
            case '(':
                lexer_consume(lexer);
                tok = token_new_token("< ( >", 5, L_PAREN);
                break;
            case ',':
                lexer_consume(lexer);
                tok = token_new_token("< , >", 5, COMMA);
                break;
            case ':':
                lexer_consume(lexer);
                tok = token_new_token("< : >", 5, COLON);
                break;
            case '=':
                lexer_consume(lexer);
                tok = token_new_token("< = >", 5, EQUAL);
                break;
            case '|':
                lexer_consume(lexer);
                tok = token_new_token("< | >", 5, PIPE);
                break;
            case '$':
                lexer_consume(lexer);
                tok = token_new_token("< $ >", 5, DOLLAR);
                break;
            case '-':
                lexer_consume(lexer);
                tok = token_new_token("< - >", 5, DASH);
                break;
            default:
                if (util_is_digit(lexer->c)){
                    int val;
                    size_t len_val;
                    char *str_val;

                    val = lexer_build_int(lexer);

                    // Adding 2 for < and >
                    len_val = (size_t) (ceil(log10(val)) + 2);

                    str_val = malloc(len_val + 1);
                    if (str_val == NULL){
                        printf("No Memory\n");
                        exit(EXIT_FAILURE);
                    }
                    snprintf(str_val, len_val + 1, "<%d>", val);

                    tok = token_new_token(str_val, len_val, INT);
                    free(str_val);
                    break;

                }else if(util_is_char(lexer->c)){
                    char *built_s;
                    size_t s_len;
                    char *final_buf;

                    built_s = lexer_build_string(lexer);

                    // Adding 2 for < and >
                    s_len = strlen(built_s) + 2;

                    final_buf = malloc(s_len + 1);
                    if (final_buf == NULL){
                        printf("No memory\n");
                        exit(EXIT_FAILURE);
                    }
                    snprintf(final_buf, s_len + 1, "<%s>", built_s);
                    tok = token_new_token(final_buf, s_len, LETTERS);

                    free(built_s);
                    free(final_buf);
                    break;

                }else {
                    throw_lexing_error(
                            "Unexpected Token: \"< %c >\"\n", 
                            LEXING_ERROR_UNEXPECTED_TOKEN, 
                            lexer->c
                            );
                }
        }

    }
    return tok;
}

void lexer_consume(lexer *lexer){
    lexer->index++;
    if (lexer->index >= strlen(lexer->input)){
        lexer->c = EOF;
    }else{
        lexer->c = lexer->input[lexer->index];
    }
}

void lexer_match(lexer *lexer, char x){
    if (lexer->c == x){
        lexer_consume(lexer);
    }else{
        throw_lexing_error(
                "Expecting %c; found %c", 
                LEXING_ERROR_INVALID_CHARACTER,
                x,
                lexer->c
                );
    }
}

char* lexer_build_string(lexer *lexer){
    char *buf;
    int index;

    buf = malloc(2);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    index = 0;

    while (util_is_char(lexer->c)){
        util_add_to_buf(buf, lexer->c, &index);
        lexer_consume(lexer);
    }
    buf[index] = '\0';

    return buf;
}

int lexer_build_int(lexer *lexer){
    int val;
    char *buf;
    int index;

    buf = malloc(2);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    index = 0;

    while (util_is_digit(lexer->c)){
        util_add_to_buf(buf, lexer->c, &index);
        lexer_consume(lexer);
    }
    buf[index] = '\0';
    val = atoi(buf);

    // If atoi could not convert the string
    // Maybe the function was called inappropriately, or 
    // is_int didn't work properly
    if ((val == 0) && !(strcmp(buf, "0") == 0)){
        return -1;
    }

    free(buf);

    return val;
}

double lexer_build_float(lexer *lexer){
    double val;
    char *buf;
    int found_floatingpoint = FALSE;
    int index;

    index = 0;

    buf = malloc(2);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    while (util_is_digit(lexer->c) || (!found_floatingpoint && lexer->c == '.')){
        if (lexer->c == '.'){
            found_floatingpoint = TRUE;
        }
        util_add_to_buf(buf, lexer->c, &index);
        lexer_consume(lexer);
    }
    buf[index] = '\0';
    val = atof(buf);
    free(buf);

    return val;
}

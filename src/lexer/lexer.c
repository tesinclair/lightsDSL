#include "lexer.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

token **lexer_lex(lexer *lexer){
    token **token_stream;
    token *current_token;
    token_stream = malloc(sizeof *current_token);
    if (token_stream == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    current_token = lexer_next_token(lexer);
    int index = 0;
    
    while (current_token->type != EOF){
        token_stream[index] = current_token;
        token_stream = realloc(token_stream, sizeof(token_stream) + sizeof(*current_token));
        if (token_stream == NULL){
            printf("No memory\n");
            exit(EXIT_FAILURE);
        }
        current_token = lexer_next_token(lexer);
        index++;
    }

    // Should be EOF
    assert(current_token->type == EOF);
    token_stream[index] = current_token;

    return token_stream;
}

token *lexer_next_token(lexer *lexer){
    token *tok;

    while (lexer->c != EOF){
        if (lexer->c == '#'){
            do{
                lexer_consume(lexer);
            } while (lexer-> != '\n');
        }

        switch (lexer->c){
            case ' ': case '\n': case '\t': case '\r':
                lexer_consume(lexer);
                continue;
            case '@':
                lexer_consume(lexer);
                tok = token_new_token("< @ >", 5, AT);
                continue;
            case '}':
                lexer_consume(lexer);
                tok = token_new_token("< } >", 5, R_CURLY_BRACE);
                continue;
            case '{':
                lexer_consume(lexer);
                tok = token_new_token("< { >", 5, L_CURLY_BRACE);
                continue;
            case ';'
                lexer_consume(lexer);
                tok = token_new_token("< ; >", 5, SEMI);
                continue;
            case ')':
                lexer_consume(lexer);
                tok = token_new_token("< ) >", 5, R_PAREN);
                continue;
            case '(':
                lexer_consume(lexer);
                tok = token_new_token("< ( >", 5, L_PAREN);
                continue;
            case ',':
                lexer_consume(lexer);
                tok = token_new_token("< , >", 5, COMMA);
                continue;
            case '_':
                lexer_consume(lexer);
                tok = token_new_token("< _ >", 5, UNDERSCORE);
                continue;
            case ':':
                lexer_consume(lexer);
                tok = token_new_token("< : >", 5, COLON);
                continue;
            case '=':
                lexer_consume(lexer);
                tok = token_new_token("< = >", 5, EQUAL);
                continue;
            case '|':
                lexer_consume(lexer);
                tok = token_new_token("< | >", 5, PIPE);
                continue;
            case '$':
                lexer_consume(lexer);
                tok = token_new_token("< $ >", 5, DOLLAR);
                continue;
            case '-':
                lexer_consume(lexer);
                tok = token_new_token("< - >", 5, DASH);
                continue;
            default:
                if (util_is_digit(lexer->c)){
                    int val;
                    size_t len_val;
                    char *str_val;

                    val = lexer_build_int(lexer);
                    len_val = (size_t) ciel(log10(num));
                    str_val = malloc(len_val + 1);
                    snprintf(str_val, len_val, "<%d>", val);

                    // Adding 2 for the < and >
                    tok = token_new_token(str_val, len_val + 2, INT);
                    free(str_val);

                    continue;

                }else if(util_is_char(lexer->c)){
                    char *built_s;
                    size_t s_len;
                    char *final_buf;

                    built_s = lexer_build_string(lexer);

                    // Adding 2 for < and >
                    s_len = strlen(built_s) + 2;

                    final_buf = malloc(s_len + 1);
                    snprintf(final_buf, s_len, "<%s>", built_s);
                    tok = token_new_token(final_buf, s_len, LETTERS);

                    free(built_s);
                    free(final_buf);

                    continue;
                }else {
                    throw_lexing_error("Now, I'm certain *that* shoudln't be there!\n<Parser Error> Unexpected Token: <%c>\n", lexer->c);
                }
        }
    }
    tok = token_new_token("<EOF>", 5, EOF);
    return tok;
}

void lexer_consume(lexer *lexer){
    lexer->index++;
    if (lexer->index > strlen(lexer->input)){
        lexer->c = EOF;
    }else{
        lexer->c = lexer->input[index];
    }
}

void lexer_match(lexer *lexer, char x){
    if (lexer->c == x){
        lexer_consume(lexer);
    }else{
        throw_lexing_error("Expecting %c; found %c", x, lexer->c);
    }
}

char* lexer_build_string(lexer *lexer){
    char *buf;

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

    buf = malloc(2);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    index = 0;

    while (util_is_int(lexer->c)){
        util_add_to_buf(buf, lexer->c, &index);
        lexer_consume(lexer);
    }
    buf[index] = '\0';
    val = atoi(buf);
    free(buf);

    return val;
}

double lexer_build_float(lexer *lexer){
    double val;
    char *buf;
    int found_floatingpoint = FALSE

    buf = malloc(2);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    while (util_is_int(lexer->c) || (!found_floatingpoint && lexer->c == '.')){
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



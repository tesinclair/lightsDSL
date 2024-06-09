#include "parser.h"

parser *parser_new_parser(token **token_stream){
    parser *p;

    p = malloc(sizeof *p);
    if (p == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    p->token_stream = token_stream;
    p->index = 0;
    p->current_token = p->token_stream[0];

    return p;
}

void parser_consume(parser *p){
    if (p->current_token->type == EOF){
        throw_parse_error(
                "Cannot Consume EOF token",
                PARSE_ERROR_EOF
                );
    }
    p->index++;
    p->current_token = p->token_stream[p->index];
}

void parser_expect(parser *p, int token_key, char *token_text){
    if (p->current_token->type != token_key){
        throw_parse_error(
                "<Unexpected Token> On line <%ld>. Found: \"%s\", Expected: \"%s\"\n",
                PARSE_ERROR_UNEXPECTED_TOKEN,
                p->current_token->line_number,
                p->current_token->text,
                token_text
                );
    }
    parser_consume(p);
}

int parser_is_func(parser *p){
    if (p->current_token->type != L_CURLY_BRACE){
        return 0;
    }
    if (p->token_stream[p->index + 1]->type != AT){
        return 0;
    }
    return 1;
}

void parser_parse(parser *p){
    while (p->current_token->type != EOF){
        parser_parse_root(p);
    }
}


void parser_parse_root(parser *p){
    parser_expect(p, AT, "< @ >");
    parser_parse_stat(p);
    parser_expect(p, SEMI, "< ; >");
}

void parser_parse_stat(parser *p){
    char *tok_text = p->current_token->text;
    char *opts[] = {
        "<use>",
        "<decl>",
        "<set>",
        "<pick>",
        "<color>",
        "<for>",
        "<run>",
        "<brightness>",
        "<delay>",
        "<loop>"
    };
    
    int opt_len = 10;
    int _case = -1;

    for (int i = 0; i < opt_len; i++){
        if (strncmp(tok_text, opts[i], strlen(opts[i])) == 0){
            _case = i;
            parser_consume(p);
        }
    }

    switch(_case){
        // <use>
        case 0:
            parser_expect(p, L_CURLY_BRACE, "< { >");
            parser_expect(p, INT, "<INT>");
            parser_expect(p, R_CURLY_BRACE, "< } >");
            break;
        // <decl>
        case 1:
            parser_parse_decl(p);
            break;
        // <set>
        case 2:
            parser_parse_assign(p);
            break;
        // <pick>
        case 3:
            parser_parse_var(p);
            parser_expect(p, L_CURLY_BRACE, "< { >");
            parser_parse_var(p);
            parser_expect(p, COMMA, "< , >");
            parser_expect(p, INT, "<INT>");
            parser_expect(p, R_CURLY_BRACE, "< } >");
            break;
        // <color>
        case 4:
            // Not sure if this works
            parser_parse_assign(p);
            break;
        // <for>
        case 5:
            parser_expect(p, L_PAREN, "< ( >");
            parser_parse_range(p);
            parser_expect(p, R_PAREN, "< ) >");
            parser_expect(p, PIPE, "< | >");
            parser_parse_var(p);
            parser_expect(p, PIPE, "< | >");
            parser_parse_func(p);
            break;
        // <run>
        case 6:
            parser_parse_pin(p);
            break;
        // <brightness>
        case 7:
            parser_parse_assign(p);
            break;
        // <delay>
        case 8:
            parser_parse_pin(p);
            parser_parse_val(p);
            break;
        // <loop>
        case 9:
            parser_parse_loop(p);
            parser_parse_val(p);
            break;
        default:
            if (_case == -1){
                throw_parse_error(
                        "<Unexpected Token> On line <%ld>. Found \"%s\". Expected \"<stat>\"\n",
                        PARSE_ERROR_UNEXPECTED_TOKEN,
                        p->current_token->line_number,
                        tok_text
                        );
            }
            else{
                throw_parse_error(
                        "Unexpected Situation Occurred. \
Check <parser.c|parser_parse_stat>\n",
                        PARSE_ERROR_PARSE_FAILED
                        );
            }
    }
}

void parser_parse_pin(parser *p){
    if (strncmp(p->current_token->text, "<pin>", 5) == 0){
        parser_consume(p);
        if (p->current_token->type == DASH){
            parser_consume(p);
            parser_expect(p, L_CURLY_BRACE, "< { >");
            parser_parse_range(p);
            parser_expect(p, R_CURLY_BRACE, "< } >");
        }
        return;
    }
    if (strncmp(p->current_token->text, "<pins>", 6) == 0){
        parser_consume(p);
        parser_expect(p, DASH, "< - >");
        parser_parse_array(p);
        return;
    }
    throw_parse_error(
            "<Unexpected Token> On line: <%ld>. Found \"%s\". Expected \"<pin(s)>\"\n",
            PARSE_ERROR_UNEXPECTED_TOKEN,
            p->current_token->line_number,
            p->current_token->text
            );
}

void parser_parse_decl(parser *p){
    char *tok_text = p->current_token->text;
    char *opts[] = {
        "<type>",
        "<addressable>"
    };

    int opt_len = 2;
    int _case = -1;

    if (p->current_token->type == AMP){
        parser_parse_loop(p);
        return;
    }

    for (int i = 0; i < opt_len; i++){
        if (strncmp(tok_text, opts[i], strlen(opts[i])) == 0){
            _case = i;
            parser_consume(p);
        }
    }

    switch(_case){
        // <type>
        case 0:
            parser_expect(p, L_CURLY_BRACE, "< { >");
            parser_parse_type(p);
            parser_expect(p, R_CURLY_BRACE, "< } >");
            break;
        // <addressable>
        case 1:
            parser_expect(p, L_CURLY_BRACE, "< { >");
            parser_expect(p, INT, "<INT>");
            parser_expect(p, R_CURLY_BRACE, "< } >");
            break;
        default:
            if (_case == -1){
                throw_parse_error(
                        "<Unexpected Token> On line <%ld> Found \"%s\". Expected \"<decl>\"\n",
                        PARSE_ERROR_UNEXPECTED_TOKEN,
                        p->current_token->line_number,
                        tok_text
                        );
            }
            else{
                throw_parse_error(
                        "Unexpected Situation Occurred. \
Check <parser.c|parser_parse_stat>\n",
                        PARSE_ERROR_PARSE_FAILED
                        );
            }   

    }
    
}

void parser_parse_loop(parser *p){
    parser_expect(p, AMP, "< & >");
    parser_parse_letters(p);
}

void parser_parse_range(parser *p){
    parser_parse_val(p);
    parser_expect(p, COLON, "< : >");
    parser_parse_val(p);
}

void parser_parse_val(parser *p){
    if (p->current_token->type == INT){
        parser_expect(p, INT, "<INT>");
        return;
    }
    parser_parse_var(p);
}

void parser_parse_func(parser *p){
    parser_expect(p, L_CURLY_BRACE, "< { >");
    while (p->current_token->type == AT){
        parser_parse_root(p);
    }
    parser_expect(p, R_CURLY_BRACE, "< } >");
}

void parser_parse_assign(parser *p){
    if (p->current_token->type == DOLLAR){
        parser_parse_var(p);
    }else{
        parser_parse_pin(p);
    }

    parser_expect(p, EQUAL, "< = >");
    parser_parse_expr(p);

    if (p->current_token->type != SEMI){
        parser_expect(p, PIPE, "< | >");
        parser_parse_expr(p);
    }
}

void parser_parse_expr(parser *p){
    if (parser_is_func(p)){
        parser_parse_func(p);
    }else if (p->current_token->type == DOLLAR){
        parser_parse_var(p);
    }else if (p->current_token->type == L_CURLY_BRACE){
        parser_parse_array(p);
    }else{
        parser_expect(p, INT, "<INT>");
    }
}

void parser_parse_array(parser *p){
    parser_expect(p, L_CURLY_BRACE, "< { >");
    parser_parse_items(p);
    parser_expect(p, R_CURLY_BRACE, "< } >");
}

void parser_parse_items(parser *p){
    if (p->current_token->type != R_CURLY_BRACE){
        parser_parse_item(p);
    }
    while (p->current_token->type == COMMA){
        parser_consume(p);
        parser_parse_item(p);
    }
    if (p->current_token->type != R_CURLY_BRACE){
        parser_parse_item(p);
    }
}

void parser_parse_item(parser *p){
    if (p->current_token->type == L_CURLY_BRACE){
        parser_parse_array(p);
    }else if (p->current_token->type == L_PAREN){
        parser_parse_color(p);
    }else{
        parser_expect(p, INT, "<INT>");
    }
}

void parser_parse_color(parser *p){
    parser_expect(p, L_PAREN, "< ( >");
    parser_expect(p, INT, "<INT>");
    parser_expect(p, COMMA, "< , >");
    parser_expect(p, INT, "<INT>");
    parser_expect(p, COMMA, "< , >");
    parser_expect(p, INT, "<INT>");
    parser_expect(p, R_PAREN, "< ) >");
}

void parser_parse_type(parser *p){
    char *tok_text = p->current_token->text;
    char *opts[] = {
        "<strip>",
    };

    int opt_len = 1;
    int _case = -1;

    for (int i = 0; i < opt_len; i++){
        if (strncmp(tok_text, opts[i], strlen(opts[i])) == 0){
            _case = i;
            parser_consume(p);
        }
    }

    switch(_case){
        // <strip>
        case 0:
            break;
        default:
            if (_case == -1){
                throw_parse_error(
                        "<Unexpected Token> On line <%ld>. Found \"%s\". Expected \"<type>\"\n",
                        PARSE_ERROR_UNEXPECTED_TOKEN,
                        p->current_token->line_number,
                        tok_text
                        );
            }
            else{
                throw_parse_error(
                        "Unexpected Situation Occurred. \
Check <parser.c|parser_parse_stat>\n",
                        PARSE_ERROR_PARSE_FAILED
                        );
            }   

    }
    
}

void parser_parse_var(parser *p){
    parser_expect(p, DOLLAR, "< $ >");
    parser_parse_letters(p);
}

void parser_parse_letters(parser *p){
    parser_expect(p, LETTERS, "<LETTERS>");
}

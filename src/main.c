#include <stdio.h>
#include <stdlib.h>
#include "lexer/lexer.h"

int is_valid_file(char *file){
    int file_len = strlen(file);
    int point_idx = -1;

    for (int i = 0; i < strlen(file); i++){
        if (file[i] == '.'){
            // Allow relative file paths (./, ../)
            if (i == 0 || file[i - 1] == '.'){
                continue;
            }
            // First char after point
            point_idx = i + 1;
            break;
        }
    }
    if (point_idx == -1){
        return FALSE;
    }

    char buf[file_len];
    for (int i = 0; i < file_len; i++){
        if (file[point_idx + i] == '\0'){
            buf[i] = '\0';
            break;
        }
        buf[i] = file[point_idx + i];
    }

    if (strncmp(buf, "lts", 3) == 0){
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char *argv[]){
    FILE *fptr;
    lexer *l;
    char *input;

    if (argc < 2){
        printf("Target file must be specified\n");
        exit(EXIT_FAILURE);
    }
    
    if (is_valid_file(argv[1]) != TRUE){
        printf("Target is not an accepted file type\n");
        exit(EXIT_FAILURE);
    }

    fptr = fopen(argv[1], "r");

    if (fptr == NULL){
        printf("Target file does not exist\n");
        exit(EXIT_FAILURE);
    }
    
    input = malloc(1);
    if (input == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    char c;
    size_t index = 0;
    while ((c = fgetc(fptr)) != EOF){
        input[index] = c;

        // it needs to be 1 more than length
        input = realloc(input, ++index + 1);
    }

    l = lexer_new_lexer(input);
    if (l == NULL){
        printf("\n");
        exit(EXIT_SUCCESS);
    }

    token *tokens = lexer_lex(l);
}

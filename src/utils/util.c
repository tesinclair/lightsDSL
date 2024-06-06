#include "util.h"

int util_is_digit(char c){
    regex_t regex;
    char *stringified = malloc(2);

    if (stringified == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }

    sprintf(stringified, "%c", c);

    if (regcomp(&regex, "[0-9]", 0) != 0){
        printf("Regex failed to compile\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, stringified, 0, NULL, 0) == 0){
        return TRUE;
    }else{
        return FALSE;
    }
}

int util_is_char(char c){
    regex_t regex;
    char *stringified = malloc(2);

    if (stringified == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    
    sprintf(stringified, "%c", c);

    if (regcomp(&regex, "[a-zA-Z_]", 0) != 0){
        printf("Regex failed to compile\n");
        exit(EXIT_FAILURE);
    }

    if (regexec(&regex, stringified, 0, NULL, 0) == 0){
        return TRUE;
    }else{
        return FALSE;
    }
}

void util_add_to_buf(char *buf, char c, int *pos){
    buf[*pos] = c;
    buf = realloc((void *)buf, sizeof(buf) + 1);
    if (buf == NULL){
        printf("No memory\n");
        exit(EXIT_FAILURE);
    }
    (*pos)++;
}


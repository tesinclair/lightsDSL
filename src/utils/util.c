#include "util.h"

int util_is_digit(char c){
    regex_t regex;

    regcomp(&regex, "[0-9]", 0);

    if (regexec(&regex, &c, 0, NULL, 0) == REG_NOMATCH){
        return FALSE;
    }else{
        return TRUE;
    }
}

int util_is_char(char c){
    regex_t regex;

    regcomp(&regex, "[a-zA-Z_]", 0);

    if (regexec(&regex, &c, 0, NULL, 0) == REG_NOMATCH){
        return FALSE;
    }else{
        return TRUE;
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


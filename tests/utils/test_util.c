#include "test_util.h"

void test_util_is_digit(){
    int result;

    char data_true[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
    size_t len_true = 10;

    char data_false[] = {
        'a', 'r', '!', '+', '_', '\n'
    };
    size_t len_false = 6;

    for (int i = 0; i < len_true ; i++){
        result = util_is_digit(data_true[i]);

        testing_assert(
                result == TRUE, 
                "<util_is_digit> (\"%c\") returned \"FALSE\". Expected \"TRUE\".",
                data_true[i]
                );

    }

    for (int i = 0; i < len_false; i++){
        result = util_is_digit(data_false[i]);

        testing_assert(
                result == FALSE,
                "<util_is_digit> (\"%c\") returned \"TRUE\". Expected \"FALSE\".",
                data_false[i]
                );
    }
}

void test_util_is_char(){
    int result;

    char data_true[] = {
        'a', 'b', 'X', 'Y', 'z', '_' 
    };
    size_t len_true = 6;

    char data_false[] = {
        '0', '1', '9', '(', '-', '"', '\n', '/', '\''
    };
    size_t len_false = 9;

    for (int i = 0; i < len_true; i++){
        result = util_is_char(data_true[i]);

        testing_assert(
                result == TRUE,
                "<util_is_char> (\"%c\") returned \"FALSE\". Expected \"TRUE\".",
                data_true[i]
                );
    }

    for (int i = 0; i < len_false; i++){
        result = util_is_char(data_false[i]);

        testing_assert(
                result == FALSE,
                "<util_is_char> (\"%c\") returned \"TRUE\". Expected \"FALSE\".",
                data_false[i]
                );
    }
}

void test_util_add_to_buf(){
    // Add "ello, World!" to h
    char *buf = malloc(2);
    char str_to_add[] = {
        'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'
    };
    char str_to_cmp[14];
    size_t max_buf = 13;

    buf[0] = 'H';
    int index = 1;

    for (int i = 0; i < 13; i++){
        util_add_to_buf(buf, str_to_add[i], &index);
    }

    testing_assert(
        index == 14,
        "<util_add_to_buf> returned \"%d\". Expected \"14\".",
        index
        );
}


void test_util(){
    test_util_is_digit();
    printf("<test_util_is_digit> \033[0;32mPASSED\033[0;37m\n");
    
    test_util_add_to_buf();
    printf("<test_util_add_to_buf> \033[0;32mPASSED\033[0;37m\n");

    test_util_is_char();
    printf("<test_util_is_char> \033[0;32mPASSED\033[0;37m\n");
}

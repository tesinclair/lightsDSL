#include "../../src/utils/util.h"
#include "../testing_assert.h"

#define TRUE 1
#define FALSE 0

void test_util_is_digit(){
    int result;

    char data_true = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
    size_t len_true = 10;

    char data_false = {
        'a', 'r', '!', '+', '_', '\n'
    };
    size_t len_false = 6;

    for (int i = 0; i < len_true ; i++){
        result = util_is_digit(data_true[i]);

        testing_assert(
                result == TRUE, 
                "Failed because %c did not return TRUE from function <util_is_digit> defined in utils/util.c",
                data_true[i]
                );

    }

    for (int i = 0; i < len_false; i++){
        result = util_is_digit(data_false[i]);

        testing_assert(
                result == FALSE,
                "Failed because %c did not return FALSE from function <util_is_digit> defined in utils/util.c",
                data_false[i]
                );
    }

    printf("Tests for <util_is_digit> passed");
}

void test_util_is_char(){
    int result;

    char data_true = {
        'a', 'b', 'x', 'y', 'z', '_'
    };
    size_t len_true = 6;

    char data_false = {
        '0', '1', '9', '(', '-', '"', '\n', '/', '\''
    };
    size_t len_false = 9;

    for (int i = 0; i < len_true; i++){
        result = util_is_char(data_true[i]);

        testing_assert(
                result == TRUE,
                "Failed because %c did not return TRUE from function <util_is_char> defined in utils/util.c",
                data_true[i]
                );
    }

    for (int i = 0; i < len_false; i++){
        result = util_is_char(data_false[i]);

        testing_assert(
                result == FALSE,
                "Failed because %c did not return FALSE from function <util_is_char> defined in utils/util.c",
                data_false[i]
                );
    }

    printf("Tests for <util_is_char> passed");
}

void test_util_add_to_buf(){

    // Add "ello, World!" to h
   
    char *buf = malloc(2);
    char *str_to_add = {
        'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'
    };
    char str_to_cmp[14]
    size_t max_buf = 13;

    buf[0] = 'H';

    for (int i = 0; i < 13; i++){
        util_add_to_buf(buf, str_to_add[i], &(i + 1));
}

int main(){
    test_util_is_digit();
    test_util_is_char();
}
        


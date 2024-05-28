#ifndef TEST_LEXER_H
#define TEST_LEXER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../testing_assert.h"
#include"../../lexer/lexer.h"

void test_lexer_next_token();

void test_lexer_build_string();

void test_lexer_build_int();

// No testing yet - not used
//void test_lexer_build_float();

// Not testing since it would take
// longer to test that it did to 
// write
// void test_lexer_consume();

// No testing yet - not used
//void test_lexer_match();

// No testing yet - likely to delete
void test_lexer_letters();

void test_lexer_lex();

#endif

#ifndef UTIL_H
#define UTIL_H

#define TRUE 1
#define FALSE 0

#include<regex.h>
#include<stdlib.h>
#include<stdio.h>

int util_is_digit(char c);

int util_is_char(char c);

void util_add_to_buf(char *buf, char c, int *pos);

#endif

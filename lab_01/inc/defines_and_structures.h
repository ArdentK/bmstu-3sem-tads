#ifndef DEFINES_AND_STRUCTURES_H
#define DEFINES_AND_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define INPUT_DIVIDENT_ERROR -1
#define INPUT_DIVISOR_ERROR -2
#define DIVISION_BY_ZERO -3
#define WRONG_STR_LEN -4
#define WRONG_SIGN -5
#define WRONG_ORDER -6
#define TOO_LONG_NUM -7
#define OVERLOW -8

#define MAX_NUM_LEN 31
#define MAX_STR_LEN 40
#define LEN_ORDER 6

typedef struct
{
    char sign;
    int number[MAX_NUM_LEN];
    long order;
    size_t num_len;
} real_t;

typedef struct
{
    char sign;
    int number[MAX_NUM_LEN];
    size_t num_len;
} int_t;

#endif //DEFINES_AND_STRUCTURES_H
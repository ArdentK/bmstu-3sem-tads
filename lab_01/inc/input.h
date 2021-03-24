#ifndef INPUT_H
#define INPUT_H

#include "../inc/defines_and_structures.h"

int is_divisor_correct(int_t *divisor, char str_divisor[MAX_NUM_LEN + 2]);
int is_divident_correct(real_t *divident, char str_divident[MAX_STR_LEN]);
void print(FILE *f);

#endif // INPUT_H
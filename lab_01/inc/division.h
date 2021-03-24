#ifndef DIVISION_H
#define DIVISION_H

#include <stdio.h>
#include <stdlib.h>

#include "../inc/defines_and_structures.h"

//Вычитание. (После выполнения уменьшаемое превращается в остаток)
void subtraction(int minuend[], size_t *size_m, int subtrahend[], size_t size_s);

// Деление
char division_by_subtraction(int divident[], size_t *len_1, int divisor[], size_t len_2);

// Проверка, больше ли первое число (числа представлены строками)
int is_greater(int num_1[], size_t size_1, int num_2[], size_t size_2);

//Деление
int division(real_t divident, int_t divisor, real_t *answer);

#endif //DIVISION_H
#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#include "../inc/defines_and_structures.h"

//Вывод числа
void print_array(int a[], size_t n);

//Проверка, равно ли число нулю
int is_zero(int num[MAX_NUM_LEN], size_t len);

// Удаление ведущих нулей в целом числе (число записано в формате строки)
void del_prev_zero(int num[], size_t *size);

// Удаление незначащих нулей с конца
void del_last_zeroes(int num[], size_t *len);

// Выровнять по длине. (длина массива а > длины массива b)
void align_to_length(size_t size_a, int b[], size_t *size_b);

// Добавление незначащих нулей в конец
void append_zeroes(int num[], size_t *len);

void int_print(int_t num);
void real_print(real_t num);

#endif //ARRAY_H
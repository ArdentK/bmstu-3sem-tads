#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

// Обмен элементов
void swap(void *p, void *q, size_t elem_size);

// Сортировка вставками с помощью таблицы ключей
void insertion_sort_with_new_table(key_price_t key[], int len);

// Сортировка вставками без использования таблицы ключей
void insertion_sort(car_t cars[], int len);

// Создание таблицы ключей
void create_arr_of_key(car_t cars[], int len, key_price_t key[]);

// Сравнение цен в массиве структур car_t
int compare_price(const void *p, const void *q);

// Сравнение полей в таблице ключей
int compare_price_key(const void *p, const void *q);

#endif //SORT_H
#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"

// 1 запись в хеш-таблице
typedef struct
{
    int data;       // Данные
    int is_free;    // Свобободна ли ячейка хеш-таблицы
    int is_deleted; // Были ли удалены данные из ячейки
} data_record_t;

// Хеш-таблица
typedef struct
{
    data_record_t *arr; // Массив записей
    int table_size;     // Максимальный размер таблицы
    int cur_size;       // Текущий размер таблицы
} hash_table_t;

// хеш-функции
int hash6432shift(long long key, int size);
int Hash_UInt_M3(long long key, int size);
int hash32shiftmult(int key, int size);

// функции хеш-таблицы
int hash(int key, int table_size);
void clean_hash_table(data_record_t *arr, int arr_size);
void insert_in_hash_table(hash_table_t *hash_t, int data, int *num_of_collision, int *temp_cmp);
int find_in_hash_table(hash_table_t *hash_t, int data, int *temp_cmp);
int delete_in_hash_table(hash_table_t *hash_t, int data, int *num_cmp);
int change_hash_function(hash_table_t *hash_t);
void print_hash_table(hash_table_t *hash_t);
int hash_table_init(hash_table_t *hash_t, int size);
int create_hash_table(hash_table_t *hash_t, int size, FILE *f, int *num_of_collisions, int *temp_cmp, int max_colls);

#endif // HASH_H
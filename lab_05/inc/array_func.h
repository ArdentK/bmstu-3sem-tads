#ifndef _ARRAY_FUNC_H
#define _ARRAY_FUNC_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "io.h"

// Посчет памяти, которую занимает массив
size_t get_queue_array_memory_size(size_t max_len);

// Удаление элемента из очереди
int pop_queue_array(queue_array_t *arr, request_t *del);

// Добавление элемента в очередь
void push_queue_array(queue_array_t *arr, request_t *new_elem);

// Увеличение размера массива
void increase_queue_array(queue_array_t *arr);

// Пустой ли массив
int is_empty_queue_array(queue_array_t *arr);

// Заполнен ли массив
int is_full_queue_array(queue_array_t *arr);

// Освобождение массива
void free_queue_array(queue_array_t *arr);

// Изменить размер массива
queue_array_t *resize_queue_array(queue_array_t *arr, size_t new_size);

// Опустошение массива
void make_empty_queue_array(queue_array_t *arr);

// Создание массива
queue_array_t *create_queue_array();

#endif // _ARRAY_FUNC_H
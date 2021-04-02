#ifndef _LIST_FUNC_H
#define _LIST_FUNC_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "io.h"

// Подсчет памяти, которую занимает очередь-список
size_t get_queue_list_memory_size(size_t len);

// Удаление элемента из очереди
int pop_queue_list(queue_list_t *list, request_t *item);

// Пустой ли список
int is_empty_queue_list(queue_list_t *list);

// Освобождение очереди
void free_queue_list(queue_list_t *list);

//Опустошение списка
void make_empty_queue_list(queue_list_t *list);

// Создание списка
queue_list_t *create_queue_list();

// Освобождение памяти из-под списка
void free_list(node_t *head);

// Удаление узла списка
void node_free(node_t *elem);

// Добавление элемента в очередь
void push_queue_list(request_t *new_elem, queue_list_t *list);

// СОздание узла списка
node_t *node_create(request_t *data);

#endif // _LIST_FUNC_H
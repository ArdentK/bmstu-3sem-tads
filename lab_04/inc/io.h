#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <defines.h>

// Вывод соответствующих сообщений об ошибках
void print_err(int err);

// Является ли строка str целым положительным числом
int is_pos_digit(char *str, long *res);

// Соответствует ли выбор пользователя правилам ввода
int my_choice(char *str, int *c);

// Вывод содержимого файла
int print_file(char *name);

// Является ли введенная строка валидным именем файла
int select_file(char name[STR_MAX]);

int init_array(array_t *arr, long count, FILE *f);
int create_list(size_t count, FILE *f, node_t **head);
void list_free_all(node_t **head);
void node_free(node_t *elem);
void free_array_t(array_t *arr);
int node_create(FILE *f, node_t *new_elem);
node_t *list_add_front(node_t *head, node_t *elem);
node_t *list_add_end(node_t *head, node_t *word);

void del_last_arr_elem(array_t *arr);
int add_elem_in_array(FILE *f, array_t *arr);

node_t *list_free_front(node_t *head);

int input_elem_count(FILE *f, size_t *count);

#endif // IO_H
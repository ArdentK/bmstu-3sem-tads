#ifndef IO_H
#define IO_H

#include "defines.h"

#include <string.h>

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

int input_point_of_grapth(graph_t *graph, size_t *point);

#endif // IO_H
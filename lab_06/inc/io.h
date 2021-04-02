#ifndef IO_H
#define IO_H

#include "defines.h"
#include "tree.h"

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

int is_digit(char *str, long *res);

void show_picture_status(char *name);

void print_tree(tree_node_t *node, size_t tab, int is_left, int is_right, unsigned int notch, int is_root);

#endif // IO_H
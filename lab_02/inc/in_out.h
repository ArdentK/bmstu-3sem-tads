#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

// Чтение исходных данных из файла
int read_data(FILE *f, car_t cars[], int *len);

// Вывод данных
void print_data(car_t cars[], int len);

// Вывод 1 записи
void print_car(car_t car);

// Вывод содержания файла на экран
int print_file(char *name);

// Добавление пользователем новой записи в массив
int append(car_t cars[], int *len);

// Проверка правильности ввода выбора пользователя
int my_choice(char *str, int *c);

// Добавление новой записи в массив (не пользователем)
int append_car(char *str, car_t *car);

// Введено ли число
int is_digit(char *str, long *res);

// Вывод соответсвующих комментариев к кодам ошибок
void print_error(int err);

// Выполнение пункта меню 4
int menu_4(car_t cars[], int len);

// Вывод записей, отсортированных с использованием дополнительной таблицы ключей
void print_by_new_table(car_t cars[], key_price_t key[], int len);

// Вывод таблицы ключей
void print_key(key_price_t key[], int len);

#endif // IN_OUT_H
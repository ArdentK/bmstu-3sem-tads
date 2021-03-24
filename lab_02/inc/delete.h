#ifndef DELETE_H
#define DELETE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

// Ввод пользователем названия поля, по значению которого следует удалить элементы
int input_field(char *field);

// Ввод значения удаляемых полей
int input_value(char *value);

// Удаление элементов
void delete_elem(char *field, char *value, car_t cars[], int *len);

// Смещение элементов
void offset(car_t cars[], int *len, int index);

// Удаление записей по соответсвующим полям значениям
void delete_by_brand(car_t cars[], int *len, char *value);
void delete_by_country(car_t cars[], int *len, char *value);
void delete_by_price(car_t cars[], int *len, char *value);
void delete_by_colour(car_t cars[], int *len, char *value);
void delete_by_warranty(car_t cars[], int *len, char *value);
void delete_by_year(car_t cars[], int *len, char *value);
void delete_by_mileage(car_t cars[], int *len, char *value);
void delete_by_repairs(car_t cars[], int *len, char *value);
void delete_by_owners(car_t cars[], int *len, char *value);

#endif // DELETE_H
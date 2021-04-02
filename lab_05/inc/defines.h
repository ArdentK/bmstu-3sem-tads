#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCCESS 0
#define INPUT_ERROR -1
#define WRONG_STR -2
#define OPEN_FILE_ERROR -3
#define NOT_POSITIVE -4
#define MEMORY_ERROR -5

#define NUM_T1 1000
#define STR_MAX 41
#define COUNT 2

#include <stdio.h>
#include <stdlib.h>

// Заявка
typedef struct
{
    size_t id;     // Номер заявки
    void *address; // Адрес заявки
} request_t;

// Очередь, реализованная с помощью массива
typedef struct
{
    request_t *buf; // Массив заявок
    size_t max_len; // Максимальная длина очереди
    size_t cur_len; // Текущая длина очереди
    size_t head;    // Номер "головы"
    size_t tail;    // Номер "хвоста"
} queue_array_t;

// Описание узла списка
typedef struct node node_t;
struct node
{
    request_t data; // Данные узла (заявка)
    node_t *next;   // Ссылка на следующий элемент узла
};

// Структура для хранения очереди, реализованной с помощью списка
typedef struct
{
    node_t *head;   // "Голова" списка
    node_t *tail;   // "Хвост" списка
    size_t cur_len; // Текущаяя длина списка
} queue_list_t;

// Интервалы времени поступления и обработки заявок разных типов
typedef struct
{
    double in_time_t1[COUNT];   // Интервал времени, за которое могут поступать заявки типа T1
    double oper_time_t1[COUNT]; // Интервал времени, за которое могут обрабатываться заявки типа Т1
    double in_time_t2[COUNT];   // Интервал времени, за которое могут приходить заявки типа Т2
    double oper_time_t2[COUNT]; // Интервал времени, за которео могут обрабатываться заявки типа Т2
} times_t;

#endif // DEFINES_H
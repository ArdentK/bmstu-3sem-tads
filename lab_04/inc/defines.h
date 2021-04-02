#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCCESS 0
#define INPUT_ERROR -1
#define WRONG_STR -2
#define OPEN_FILE_ERROR -3
#define NOT_POSITIVE -4
#define MEMORY_ERROR -5

#define N_MAX 10000
#define STR_MAX 41

// структура для реализации стека списком
typedef struct node node_t;

struct node
{
    char *word;   // слово
    node_t *next; // ссылка на следующий элемент
};

// структра для реализации стека массивом
typedef struct
{
    long pos;     // позиция текущего последнего элемента
    char **words; // массив слов
} array_t;
/*
//структура для хранения массива свободных областей
typedef struct
{
    size_t len;               // количество свободных областей
    char ptr[N_MAX][STR_MAX]; // адреса свободных областей
} free_places;
*/
#endif // DEFINES_H
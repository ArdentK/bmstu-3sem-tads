#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCCESS 0
#define INPUT_ERROR -1
#define WRONG_STR -2
#define OPEN_FILE_ERROR -3
#define NOT_POSITIVE -4
#define MEMORY_ERROR -5

#define STR_MAX 40

#include <stdio.h>
#include <stdlib.h>

// Матрица
typedef struct
{
    size_t rows; // Количество строк
    size_t cols; // Количество столбцов
    int **data;  // Буффер с данными
} matrix_t;

// Орграф
typedef struct
{
    size_t num;                 // Количество вершин графа
    matrix_t *adjacency_matrix; // Матрица смежности
    matrix_t *reachability;     // Матрица достижимости
} graph_t;

#endif // DEFINES_H
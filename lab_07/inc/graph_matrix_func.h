#ifndef MATRIX_FUNC_H
#define MATRIX_FUNC_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "io.h"

// Инициализация матрицы
matrix_t *allocate_matrix(size_t rows, size_t cols);

// Создание графа из файла
graph_t *create_graph_from_file(FILE *file);

// Создание матрицы достижимости
void create_reachability_matrix(graph_t *graph);

// Освобождение памяти из-под матрицы
void free_matrix(matrix_t *matrix);

// Освобождение матрицы из-под графа
void free_graph(graph_t *graph);

// Суммирование матриц
matrix_t *addition(matrix_t *mtx_1, matrix_t *mtx_2);

// Умножение матриц
matrix_t *multiplication(matrix_t *mtx_1, matrix_t *mtx_2);

// Поиск недостижимых вершин
void find_points(graph_t graph, size_t point);

// Запись на языку dot таблицы достижимости в файл
void export_dot_reachability(FILE *file, graph_t *graph, size_t point);

#endif // MATRIX_FUNC_H
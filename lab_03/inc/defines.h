#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCCESS 0
#define INPUT_ERROR -1
#define MULTIPLICATION_ERROR -2
#define WRONG_STR -3
#define OPEN_FILE_ERROR -4
#define NOT_POSITIVE -5

#define N_MAX 151
#define ELEM_MAX 10000
#define STR_MAX 40

// Стандартный вид хранения
typedef struct
{
    size_t rows;          // Количество строк
    size_t columns;       // Количество столбцов
    long A[N_MAX][N_MAX]; // Значения элементов
} matrix_t;

// Хранение матрицы в разреженном виде
typedef struct
{
    size_t row_num;      // Количество строк
    size_t elems_num;    // Количество ненулевых элементов
    long A[ELEM_MAX];    // Значения ненулевых элементов
    size_t JA[ELEM_MAX]; // Массив номеров столбцов каждого ненулевого элемента
    size_t IA[N_MAX];    // Массив номеров элементов, с которых начинается описание каждой строки
} sparse_t;

// Хранение вектора в стандартном виде
typedef struct
{
    size_t len;       // Длина вектора
    long A[ELEM_MAX]; // Массив значений вектора
} std_vector_t;

// Хранение вектора в разреженном виде
typedef struct
{
    size_t size;
    size_t len;       // Количество ненулевых элементов
    long A[N_MAX];    // Массив ненулевых элементов вектора
    size_t JA[N_MAX]; // Массив номеров столбцов каждого ненулевого элемента
} sparse_vector_t;

#endif // DEFINES_H
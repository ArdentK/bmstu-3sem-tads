#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/io.h"

int print_file(char *name)
{
    FILE *f;
    char str[256];

    f = fopen(name, "r");

    if (!f)
        return OPEN_FILE_ERROR;

    while (fgets(str, 256, f) != NULL)
        printf("%s", str);

    fclose(f);

    return EXIT_SUCCESS;
}

int my_choice(char *str, int *c)
{
    long res;

    str[strlen(str) - 1] = '\0';

    if (is_pos_digit(str, &res))
        return INPUT_ERROR;

    *c = res;

    return EXIT_SUCCESS;
}

int is_pos_digit(char *str, long *res)
{
    char *end;

    *res = strtol(str, &end, 10);
    if (*end)
        return INPUT_ERROR;

    if (*res <= 0)
        return NOT_POSITIVE;

    return EXIT_SUCCESS;
}

void from_std_to_sparse_mtx(matrix_t mtx, sparse_t *new_mtx)
{
    new_mtx->elems_num = 0;
    new_mtx->row_num = mtx.rows + 1;

    for (size_t i = 0; i < mtx.rows; i++)
    {
        for (size_t j = 0; j < mtx.columns; j++)
            if (mtx.A[i][j])
            {
                new_mtx->A[new_mtx->elems_num] = mtx.A[i][j];
                new_mtx->JA[new_mtx->elems_num] = j + 1;
                new_mtx->elems_num += 1;
            }

        new_mtx->IA[i + 1] = new_mtx->elems_num + 1;
    }

    if (new_mtx->elems_num > 0)
    {
        new_mtx->IA[0] = 1;
        new_mtx->IA[new_mtx->row_num - 1] = new_mtx->elems_num + 1;
    }
}

void from_std_to_sparse_vector(std_vector_t vector, sparse_vector_t *new_vector)
{
    new_vector->size = vector.len;
    new_vector->len = 0;

    for (size_t i = 0; i < vector.len; i++)
        if (vector.A[i])
        {
            new_vector->A[new_vector->len] = vector.A[i];
            new_vector->JA[new_vector->len] = i + 1;
            new_vector->len += 1;
        }
}

int std_input_vector(FILE *f, std_vector_t *vector)
{
    if (f == stdin)
        printf("Введите количество элементов: ");

    if (fscanf(f, "%zu", &vector->len) != 1)
        return INPUT_ERROR;

    if (f == stdin)
        printf("Вводите значения элементов вектора-строки по порядку через пробел: ");

    for (size_t i = 0; i < vector->len; i++)
    {
        if (fscanf(f, "%ld", &vector->A[i]) != 1)
            return INPUT_ERROR;
    }

    return EXIT_SUCCESS;
}

int input_vector(FILE *f, sparse_vector_t *vector)
{

    if (f == stdin)
        printf("Введите длину вектора: ");

    if (fscanf(f, "%zu", &vector->size) != 1)
        return INPUT_ERROR;

    if (f == stdin)
        printf("Введите количество ненулевых элементов: ");

    if (fscanf(f, "%zu", &vector->len) != 1)
        return INPUT_ERROR;

    if (f == stdin)
        printf("Введите значения ненулевых элементов: ");

    for (size_t i = 0; i < vector->len; i++)
    {
        if (fscanf(f, "%ld", &vector->A[i]) != 1)
            return INPUT_ERROR;
    }

    if (f == stdin)
        printf("Введите номера столбцов каждого ненулевого элемента: ");

    for (size_t i = 0; i < vector->len; i++)
    {
        if (fscanf(f, "%zu", &vector->JA[i]) != 1)
            return INPUT_ERROR;
    }

    return EXIT_SUCCESS;
}

int input_matrix(FILE *f, sparse_t *mtx)
{
    if (f == stdin)
        printf("Введите количество строк в матрице: ");

    if (fscanf(f, "%zu", &mtx->row_num) != 1)
        return INPUT_ERROR;

    mtx->row_num += 1;

    if (f == stdin)
        printf("Введите количество ненулевых элементов в матрице: ");

    if (fscanf(f, "%zu", &mtx->elems_num) != 1)
        return INPUT_ERROR;

    if (f == stdin)
        printf("Введите значения ненулевых элементов в матрице: ");

    for (size_t i = 0; i < mtx->elems_num; i++)
    {
        if (fscanf(f, "%ld", &mtx->A[i]) != 1)
            return INPUT_ERROR;
    }
    if (f == stdin)
        printf("Введите номера столбцов каждого ненулевого элемента: ");

    for (size_t i = 0; i < mtx->elems_num; i++)
    {
        if (fscanf(f, "%zu", &mtx->JA[i]) != 1)
            return INPUT_ERROR;
    }
    if (f == stdin)
        printf("Введите номера элементов, с которых начинается описание каждой строки:");

    for (size_t i = 0; i < mtx->row_num; i++)
    {
        if (fscanf(f, "%zu", &mtx->IA[i]) != 1)
            return INPUT_ERROR;
    }

    return EXIT_SUCCESS;
}

int std_input_matrix(FILE *f, matrix_t *mtx)
{

    char str[STR_MAX];
    long input_num;
    int err = EXIT_SUCCESS;
    if (f == stdin)
        printf("Введите количество строк в матрице: ");
    /*
    if (fscanf(f, "%zu", &mtx->rows) != 1)
        return INPUT_ERROR;
    */
    if (!fgets(str, STR_MAX + 2, f))
        return INPUT_ERROR;

    str[strlen(str) - 1] = '\0';
    err = is_pos_digit(str, &input_num);
    if (err)
        return err;
    mtx->rows = input_num;
    if (f == stdin)
        printf("Введите количество столбцов в матрице: ");
    /*
    if (fscanf(f, "%zu", &mtx->columns) != 1)
        return INPUT_ERROR;
    */

    if (!fgets(str, STR_MAX + 2, f))
        return INPUT_ERROR;

    str[strlen(str) - 1] = '\0';
    err = is_pos_digit(str, &input_num);
    if (err)
        return err;
    mtx->columns = input_num;
    if (f == stdin)
        printf("Вводите целочисленные элементы строки матрицы через пробел.\n");
    /*
    for (size_t i = 0; i < mtx->rows; i++)
        for (size_t j = 0; j < mtx->columns; j++)
            if (fscanf(f, "%ld", &mtx->A[i][j]) != 1)
                return INPUT_ERROR;
    */
    for (size_t i = 0; i < mtx->rows; i++)
    {
        char p[STR_MAX] = "";
        char spec[STR_MAX] = "";

        if (!fgets(str, STR_MAX + 2, f))
            return INPUT_ERROR;

        if (strlen(str) < 2 || str[strlen(str) - 1] != '\n')
            return WRONG_STR;

        for (size_t j = 0; j < mtx->columns; j++)
        {
            strcat(spec, p);
            strcat(spec, "%ld");
            if (sscanf(str, spec, &mtx->A[i][j]) != 1)
                return INPUT_ERROR;
            strcat(p, "%*d");
            strcpy(spec, "");
        }
    }

    //    std_output_matrix(*mtx);

    return EXIT_SUCCESS;
}

void output_matrix(sparse_t mtx)
{
    printf("\nМассив значений: ");
    for (size_t i = 0; i < mtx.elems_num; i++)
        printf("%ld ", mtx.A[i]);

    printf("\nМассив номеров столбцов: ");
    for (size_t i = 0; i < mtx.elems_num; i++)
        printf("%zu ", mtx.JA[i]);

    printf("\nМассив IA[]: ");
    for (size_t i = 0; i < mtx.row_num; i++)
        printf("%zu ", mtx.IA[i]);

    printf("\n");
}

void std_output_matrix(matrix_t mtx)
{
    for (size_t i = 0; i < mtx.rows; i++)
    {
        for (size_t j = 0; j < mtx.columns; j++)
            printf("%ld ", mtx.A[i][j]);
        printf("\n");
    }
}

void std_output_vector(std_vector_t vector)
{
    for (size_t i = 0; i < vector.len; i++)
        printf("%ld ", vector.A[i]);
    printf("\n");
}

void output_vector(sparse_vector_t vector)
{
    if (vector.len == 0)
        printf("\nВектор длины = %zu содержит только нулевые значения\n", vector.size);
    
    printf("\nМассив ненулевых значений: ");

    for (size_t i = 0; i < vector.len; i++)
        printf("%ld ", vector.A[i]);

    printf("\nМассив номеров строк каждого ненулевого элемента: ");

    for (size_t i = 0; i < vector.len; i++)
        printf("%zu ", vector.JA[i]);

    printf("\n");
}

void print_err(int err)
{
    if (err == INPUT_ERROR)
        printf("\nНекорректный ввод. Попробуйте еще раз\n");
    else if (err == MULTIPLICATION_ERROR)
        printf("\nУмножение не может быть выполнено. Некорректные входные данные.\n");
    else if (err == WRONG_STR)
        printf("\nНеверная длина строки. Напоминаем, максимальная длина = 40 символов\n");
    else if (err == OPEN_FILE_ERROR)
        printf("\nНеверное имя файла.\n");
}

int select_file(char name[STR_MAX])
{
    FILE *f;

    printf("Имя файла не должно превышать 40 символов.\nВведите имя файла: ");

    if (!fgets(name, STR_MAX + 1, stdin))
        return INPUT_ERROR;

    if (strlen(name) == STR_MAX + 1 && (name[strlen(name) - 1] != '\n' || strlen(name) < 2))
        return WRONG_STR;

    name[strlen(name) - 1] = '\0';

    f = fopen(name, "r");
    if (!f)
        return OPEN_FILE_ERROR;
    fclose(f);

    return EXIT_SUCCESS;
}

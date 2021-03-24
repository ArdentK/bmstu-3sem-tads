#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/multiplication.h"

int can_multiply_std(std_vector_t vector, matrix_t mtx)
{
    if (vector.len != mtx.columns)
        return MULTIPLICATION_ERROR;

    return EXIT_SUCCESS;
}

int can_multiply_sparse(sparse_vector_t vector, sparse_t mtx)
{
    if (vector.size != mtx.row_num - 1)
        return MULTIPLICATION_ERROR;

    return EXIT_SUCCESS;
}

// Стандартоное умножение на вектор-столбец
void std_multiplication(std_vector_t vector, matrix_t mtx, std_vector_t *res)
{
    double sum;
    res->len = vector.len;

    for (size_t j = 0; j < mtx.rows; j++)
    {
        sum = 0;

        for (size_t k = 0; k < vector.len; k++)
            sum += vector.A[k] * mtx.A[j][k];

        res->A[j] = sum;
    }
}

/*
void std_multiplication(std_vector_t vector, matrix_t mtx, std_vector_t *res)
{
    double sum;

    for (size_t i = 0; i < vector.len; i++)
        for (size_t j = 0; j < mtx.columns; j++)
        {
            sum = 0;

            for (size_t k = 0; k < vector.len; k++)
                sum += vector.A[k] * mtx.A[k][j];

            res->A[j] = sum;
        }
}
*/
void sparse_multiplication(sparse_vector_t vector, sparse_t mtx, sparse_vector_t *res)
{
    long curr_res = 0;

    res->size = mtx.row_num - 1;
    res->len = 0;

    std_vector_t IP;

    IP.len = mtx.row_num - 1;
    for (size_t i = 0; i < vector.len; i++)
        IP.A[vector.JA[i] - 1] = i + 1;

    /*
    printf("\nIP: ");
    for (size_t i = 0; i < IP.len; i++)
        printf("%ld ", IP.A[i]);
*/
    //  Умножение на вектор-столбец
    for (size_t k = 0; k < mtx.row_num - 1; k++)
    {
        curr_res = 0;
        //printf("mtx IA[k] = %zu, mtx IA[k + 1] = %zu\n", mtx.IA[k], mtx.IA[k + 1]);
        /*
        for (size_t j = 0; j < vector.len; j++)
            for (size_t i = mtx.IA[k] - 1; i < mtx.IA[k + 1] - 1; i++)
            {
                //printf("mtx JA = %zu, vector JA = %zu\n", mtx.JA[i], vector.JA[j]);
                if (vector.JA[j] == mtx.JA[i])
                    curr_res += vector.A[j] * mtx.A[i];
            }
        */

        for (size_t i = mtx.IA[k] - 1; i < mtx.IA[k + 1] - 1; i++)
            if (IP.A[mtx.JA[i] - 1] != 0)
                curr_res += mtx.A[i] * vector.A[IP.A[mtx.JA[i] - 1] - 1];
        /*
            for (size_t j = 0; j < vector.len; j++)
            {
                //printf("mtx JA = %zu, vector JA = %zu\n", mtx.JA[i], vector.JA[j]);
                if (vector.JA[j] == mtx.JA[i])
                    curr_res += vector.A[j] * mtx.A[i];
            }
            */

        if (curr_res)
        {
            res->JA[res->len] = k + 1;
            res->A[res->len] = curr_res;
            res->len += 1;
        }

        //printf("k = %zu, res = %ld\n", k, curr_res);
    }
}

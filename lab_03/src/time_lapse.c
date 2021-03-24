#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/time_lapse.h"

#define N 10000

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int std_input_mtx_from_file(FILE *f, matrix_t *mtx)
{
    if (fscanf(f, "%zu", &mtx->rows) != 1)
        return INPUT_ERROR;

    if (fscanf(f, "%zu", &mtx->columns) != 1)
        return INPUT_ERROR;

    for (size_t i = 0; i < mtx->rows; i++)
        for (size_t j = 0; j < mtx->columns; j++)
            if (fscanf(f, "%ld", &mtx->A[i][j]) != 1)
                return INPUT_ERROR;

    return EXIT_SUCCESS;
}

int time_lapse(FILE *f_sparse, FILE *f_std, std_vector_t std_v, matrix_t std_mtx, std_vector_t std_res, sparse_vector_t sp_v, sparse_t sp_mtx, sparse_vector_t sp_res)
{
    uint64_t start, stop;
    int64_t elapsed_time = 0;
    int err = EXIT_SUCCESS;

    // Замер времени для умножения в стандартной форме
    err = std_input_mtx_from_file(f_std, &std_mtx);
    if (err)
        return err;

    err = std_input_vector(f_std, &std_v);
    if (err)
        return err;

    err = can_multiply_std(std_v, std_mtx);
    if (err)
        return err;

    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        start = tick();
        std_multiplication(std_v, std_mtx, &std_res);
        stop = tick();
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    size_t mem = sizeof(long) * (std_res.len + std_mtx.rows * std_mtx.columns + std_v.len) + sizeof(size_t) * 4;

    printf("%13lld | %14zu |", elapsed_time, mem);

    // Замер врмени для специального вида хранения
    err = input_matrix(f_sparse, &sp_mtx);
    if (err)
        return err;

    err = input_vector(f_sparse, &sp_v);
    if (err)
        return err;

    err = can_multiply_sparse(sp_v, sp_mtx);
    if (err)
        return err;

    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        start = tick();
        sparse_multiplication(sp_v, sp_mtx, &sp_res);
        stop = tick();
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    mem = (sizeof(size_t) + sizeof(long)) * (sp_res.len + sp_v.len + sp_mtx.elems_num + sp_mtx.row_num) + sizeof(size_t) * 4;

    printf("%14lld | %13zu |\n", elapsed_time, mem);

    return EXIT_SUCCESS;
}
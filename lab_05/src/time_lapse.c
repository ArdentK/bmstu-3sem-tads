#define __USE_MINGW_ANSI_STDIO 1

#include "time_lapse.h"

#define N 10000000

uint64_t ticks(void)
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

int time_lapse(queue_array_t *arr, queue_list_t *list)
{
    uint64_t start, stop;
    int64_t elapsed_time = 0;
    int err = EXIT_SUCCESS;
    size_t k = 0;
    // Время добавления и удаления элемента из списка
    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        request_t r = {k++};
        start = ticks();
        push_queue_list(&r, list);
        stop = ticks();
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    printf("| %12lld ", elapsed_time);

    size_t mem = get_queue_list_memory_size(list->cur_len);

    elapsed_time = 0;
    k = 0;
    for (size_t i = 0; i < N; i++)
    {
        request_t r;
        start = ticks();
        pop_queue_list(list, &r);
        stop = ticks();
        elapsed_time += stop - start;
    }
    elapsed_time /= N;

    printf("| %12lld ", elapsed_time);

    printf("| %12zu ", mem);

    // Врема добавления и удаления элемента из массива
    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        request_t r = {k++};
        start = ticks();
        push_queue_array(arr, &r);
        stop = ticks();
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    printf("| %12lld ", elapsed_time);

    mem = get_queue_array_memory_size(arr->max_len);

    elapsed_time = 0;
    k = 0;
    for (size_t i = 0; i < N; i++)
    {
        request_t r;
        start = ticks();
        pop_queue_array(arr, &r);
        stop = ticks();
        elapsed_time += stop - start;
    }
    elapsed_time /= N;

    printf("| %12lld ", elapsed_time);

    printf("| %12zu |\n", mem);

    return err;
}

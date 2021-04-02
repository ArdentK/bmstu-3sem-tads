#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/time_lapse.h"

#define N 100000

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

int time_lapse(FILE *f_in)
{
    uint64_t start, stop;
    int64_t elapsed_time = 0;
    int err = EXIT_SUCCESS;
    array_t arr;
    size_t count = 0;
    char str[STR_MAX];
    node_t *head;

    // Замер времени для вывода слов из стека, реализованного в виде массива
    elapsed_time = 0;

    fseek(f_in, 0, SEEK_SET);
    err = input_elem_count(f_in, &count);
    if (err)
    {
        print_err(err);
        return err;
    }

    err = init_array(&arr, count, f_in);
    if (err)
    {
        print_err(err);
        return err;
    }
    // Добавление элемента в массив
    for (size_t i = 0; i < N; i++)
    {
        fseek(f_in, 0, SEEK_SET);
        start = tick();
        err = add_elem_in_array(f_in, &arr);
        stop = tick();
        del_last_arr_elem(&arr);
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    printf("%13lld |", elapsed_time);
    // Удаление элемента из массива
    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        start = tick();
        del_last_arr_elem(&arr);
        stop = tick();
        fseek(f_in, 0, SEEK_SET);
        fgets(str, STR_MAX, f_in);
        err = add_elem_in_array(f_in, &arr);
        elapsed_time += stop - start;
    }

    elapsed_time /= N;

    size_t mem = sizeof(char) * STR_MAX * count;

    printf("%13lld | %12zu |", elapsed_time, mem);

    while (arr.pos > -1)
        del_last_arr_elem(&arr);
    free(arr.words);

    // Замер времени для вывода слов из стека, реализованного в виде списка
    // Добавление элемента в список
    fseek(f_in, 0, SEEK_SET);
    err = input_elem_count(f_in, &count);
    if (err)
    {
        print_err(err);
        return err;
    }

    head = malloc(sizeof(node_t));

    if (!head)
        return MEMORY_ERROR;

    err = node_create(f_in, head);

    if (err)
        return err;

    err = create_list(count, f_in, &head);
    if (err)
    {
        fclose(f_in);
        print_err(err);
        return err;
    }
    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        fseek(f_in, 0, SEEK_SET);
        start = tick();
        node_t *curr = malloc(sizeof(node_t));

        if (!curr)
            return MEMORY_ERROR;

        err = node_create(f_in, curr);

        if (err)
        {
            list_free_all(&head);
            return err;
        }

        head = list_add_front(head, curr);
        stop = tick();
        head = list_free_front(head);
        elapsed_time += stop - start;
    }
    elapsed_time /= N;

    printf("%13lld |", elapsed_time);

    // Удаление элемента из списка
    elapsed_time = 0;
    for (size_t i = 0; i < N; i++)
    {
        start = tick();
        head = list_free_front(head);
        stop = tick();
        elapsed_time += stop - start;
        node_t *curr = malloc(sizeof(node_t));

        if (!curr)
            return MEMORY_ERROR;
        fseek(f_in, 0, SEEK_SET);
        int err = node_create(f_in, curr);

        if (err)
        {
            list_free_all(&head);
            return err;
        }
        head = list_add_front(head, curr);
    }
    elapsed_time /= N;

    mem = (sizeof(node_t *) + STR_MAX * sizeof(char)) * count;

    printf("%13lld | %12zu |\n", elapsed_time, mem);

    list_free_all(&head);

    return EXIT_SUCCESS;
}

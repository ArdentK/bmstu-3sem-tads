#define __USE_MINGW_ANSI_STDIO 1

#include "time_lapse.h"

#define N 100

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

void time_lapse(char name[STR_MAX], int count)
{
    uint64_t start, stop;
    int64_t elapsed_time = 0;
    hash_table_t hash_t;
    tree_node_t *head = NULL;
    int num_of_collision = 0, temp_cmp = 0;

    FILE *f_in = fopen(name, "r");

    // Время удаления в ДДП
    for (size_t i = 0; i < N; i++)
    {
        fseek(f_in, 0, SEEK_SET);
        head = init_tree(f_in);
        start = ticks();
        del(head, 4);
        stop = ticks();
        elapsed_time += stop - start;
        tree_free(head);
    }

    elapsed_time /= N;
    size_t mem = get_height(head) * sizeof(tree_node_t);

    printf("| %12d | %12lld | %12zu ", count, elapsed_time, mem);

    elapsed_time = 0;
    // Время удаления в сбалансированном дереве
    for (size_t i = 0; i < N; i++)
    {
        fseek(f_in, 0, SEEK_SET);
        head = init_balance_tree(f_in);
        start = ticks();
        del_in_avl(head, 4);
        stop = ticks();
        elapsed_time += stop - start;
        tree_free(head);
    }

    elapsed_time /= N;
    mem = get_height(head) * sizeof(tree_node_t);

    printf("| %12lld | %12zu ", elapsed_time, mem);

    elapsed_time = 0;
    // Время удаления в хеш-таблице
    for (size_t i = 0; i < N; i++)
    {
        fseek(f_in, 0, SEEK_SET);
        create_hash_table(&hash_t, START_SIZE, f_in, &num_of_collision, &temp_cmp, 100000);
        start = ticks();
        delete_in_hash_table(&hash_t, 4, &temp_cmp);
        stop = ticks();
        elapsed_time += stop - start;
    }

    elapsed_time /= N;
    mem = hash_t.table_size * sizeof(data_record_t *) + 2 * sizeof(int);

    printf("| %12lld | %12zu ", elapsed_time, mem);

    elapsed_time = 0;
    // Время удаления в файле
    for (size_t i = 0; i < N; i++)
    {
        uint64_t t = 0;
        fseek(f_in, 0, SEEK_SET);
        delete_in_file(name, 4, &temp_cmp, &t);
        elapsed_time += t;
    }

    elapsed_time /= N;
    mem = sizeof(FILE *) + sizeof(int) * count;

    printf("| %12lld | %12zu |\n", elapsed_time, mem);
}
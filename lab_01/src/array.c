#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/array.h"

//Вывод числа
void print_array(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d", a[i]);
}

//Проверка, равно ли число нулю
int is_zero(int num[MAX_NUM_LEN], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (num[i] != 0)
            return 0;
    }

    return 1;
}

// Удаление ведущих нулей в целом числе (число записано в формате строки)
void del_prev_zero(int num[], size_t *size)
{
    size_t j;
    while (num[0] == 0 && *size > 0)
    {
        for (j = 0; j < *size - 1; j++)
            num[j] = num[j + 1];
        *size -= 1;
    }
}

// Удаление незначащих нулей с конца
void del_last_zeroes(int num[], size_t *len)
{
    while (*len - 1 > 0 && num[*len - 1] == 0)
        *len -= 1;
}

// Добавление незначащих нулей в конец
void append_zeroes(int num[], size_t *len)
{
    for (size_t i = *len; i < MAX_NUM_LEN; i++)
        num[i] = 0;
    *len = MAX_NUM_LEN;
}

// Выровнять по длине. (длина массива а > длины массива b)
void align_to_length(size_t size_a, int b[], size_t *size_b)
{
    int difference = size_a - *size_b;

    if (difference > 0)
    {
        while (difference)
        {
            *size_b += 1;
            for (size_t i = *size_b - 1; i > 0; i--)
                b[i] = b[i - 1];
            b[0] = 0;
            difference--;
        }
    }
}

void real_print(real_t num)
{
    printf("sign = %c, mantissa = ", num.sign);
    for (size_t i = 0; i < num.num_len; i++)
        printf("%d", num.number[i]);
    printf(" order = %ld\n", num.order);
}
void int_print(int_t num)
{
    printf("sign = %c, num = ", num.sign);
    for (size_t i = 0; i < num.num_len; i++)
        printf("%d", num.number[i]);
    printf("\n");
}
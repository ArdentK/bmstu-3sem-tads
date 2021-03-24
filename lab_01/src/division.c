#define __USE_MINGW_ANSI_STDIO 1

#include <string.h>

#include "../inc/division.h"
#include "../inc/array.h"

//Вычитание. (После выполнения уменьшаемое превращается в остаток)
void subtraction(int minuend[], size_t *size_m, int subtrahend[], size_t size_s)
{
    if (!is_greater(minuend, *size_m, subtrahend, size_s))
        return;

    align_to_length(*size_m, subtrahend, &size_s);

    for (int i = *size_m - 1; i >= 0; i--)
    {
        if (minuend[i] >= subtrahend[i])
            minuend[i] -= subtrahend[i];
        else
        {
            minuend[i] += 10 - subtrahend[i];
            minuend[i - 1]--;
        }
    }

    del_prev_zero(minuend, size_m);
    del_prev_zero(subtrahend, &size_s);
}

// Деление
char division_by_subtraction(int divident[], size_t *len_1, int divisor[], size_t len_2)
{
    int k = 0;

    while (is_greater(divident, *len_1, divisor, len_2) && k < 10)
    {
        k++;
        subtraction(divident, len_1, divisor, len_2);
    }

    return k;
}

// Проверка, больше ли первое число (числа представлены строками)
int is_greater(int num_1[], size_t size_1, int num_2[], size_t size_2)
{
    if (size_1 < size_2)
        return 0;
    else if (size_1 > size_2)
        return 1;

    for (size_t i = 0; i < size_1; i++)
    {
        if (num_1[i] - num_2[i] > 0)
            return 1;
        else if (num_1[i] - num_2[i] < 0)
            return 0;
    }

    return 1;
}

//Деление вещественного числа на целое
int division(real_t divident, int_t divisor, real_t *answer)
{
    answer->sign = '+';
    answer->num_len = 0;
    answer->order = 0;

    // Проверка, равен ли делитель нулю
    if (is_zero(divisor.number, divisor.num_len))
        return DIVISION_BY_ZERO;

    // Если делимое = 0, частное = 0
    if (is_zero(divident.number, divident.num_len))
        return EXIT_SUCCESS;

    int remainder[MAX_NUM_LEN]; // остаток на каждой стадии деления
    size_t size_r = 0;          // длина текущего остатка
    int exp = 0;                // насколько изменился порядок

    append_zeroes(divident.number, &divident.num_len);
    answer->order = divident.order;

    // Определение знака частного
    if (divident.sign == divisor.sign)
        answer->sign = '+';
    else
        answer->sign = '-';

    //printf("\n\nОтладка деления:\n");
    // Деление
    size_t count = MAX_NUM_LEN;
    for (size_t i = 0; i < count; i++)
    {
        del_prev_zero(remainder, &size_r);

        // Записываем следующуу цифру в остаток
        size_r++;
        remainder[size_r - 1] = divident.number[i];
        // Удаление всех незначащих нулей в остатке
        del_prev_zero(remainder, &size_r);

        if (is_greater(remainder, size_r, divisor.number, divisor.num_len))
        {
            answer->num_len++;
            answer->number[answer->num_len - 1] = division_by_subtraction(remainder, &size_r, divisor.number, divisor.num_len);
        }
        else
        {
            answer->num_len++;
            answer->number[answer->num_len - 1] = 0;
        }
        exp = answer->num_len;
        del_prev_zero(answer->number, &answer->num_len);
        exp -= answer->num_len;

        answer->order -= exp;

        if (exp != 0)
            count++;
    }

    // Округление
    if (answer->number[MAX_NUM_LEN - 1] == 0)
        del_last_zeroes(answer->number, &answer->num_len);
    else if (answer->number[MAX_NUM_LEN - 1] >= 5)
    {
        answer->number[MAX_NUM_LEN - 2]++;
        answer->num_len--;
    }
    else
        answer->num_len--;

    del_last_zeroes(answer->number, &answer->num_len);

    // Проверка порядка
    if (abs(answer->order) > 99999)
        return OVERLOW;

    return EXIT_SUCCESS;
}
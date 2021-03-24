#define __USE_MINGW_ANSI_STDIO 1

#include <string.h>
#include <ctype.h>

#include "../inc/input.h"
#include "../inc/array.h"

// Корректно ли введено делимое (вещественное число)
int is_divident_correct(real_t *divident, char str_divident[MAX_STR_LEN])
{
    size_t i = 0, len_num;
    char order[LEN_ORDER];
    int res;
    char *end;
    char sign;
    int flag = 0;

    divident->order = 0;

    // Корректна ли длина строки
    if (strlen(str_divident) > MAX_STR_LEN || strlen(str_divident) <= 2)
        return WRONG_STR_LEN;

    str_divident[strlen(str_divident) - 1] = '\0';

    // Корректно ли введен знак числа
    if (str_divident[0] == '-' && (isdigit(str_divident[1]) || str_divident[1] == '.'))
        divident->sign = '-';
    else if (str_divident[0] == '+' && (isdigit(str_divident[1]) || str_divident[1] == '.'))
        divident->sign = '+';
    else
        return WRONG_SIGN;

    i = 1;
    len_num = 0;

    // Проверка правильности записи самого числа
    while (str_divident[i] != 'E' && str_divident[i] != '\0')
    {
        // Находим целую часть и изменяем порядок
        if (str_divident[i] == '.' && !flag)
        {
            flag = 1;
            divident->order += i - 1;
            i++;
        }
        else if (str_divident[i] == '.' && flag)
            return INPUT_DIVIDENT_ERROR;

        if (i == 32)
            return TOO_LONG_NUM;

        if (isdigit(str_divident[i]))
        {
            divident->number[len_num] = str_divident[i] - '0';
            len_num++;
        }
        else
            return INPUT_DIVIDENT_ERROR;

        i++;
    }

    // Если вещественное число записано как целое (без ".")
    if (!flag)
        divident->order += i - 1;

    //Удаление ведущих нулей и изменение порядка, если требуется
    divident->num_len = len_num;
    int exp = divident->num_len;
    del_prev_zero(divident->number, &divident->num_len);
    exp -= divident->num_len;
    divident->order -= exp;

    del_last_zeroes(divident->number, &divident->num_len);

    // Если число не записано в экспоненциальном виде, порядок = 0
    if (str_divident[i] == '\0')
        return EXIT_SUCCESS;

    // Если число записано в экспоненциальном виде, проверить запись порядка
    else if (str_divident[i] == 'E')
    {
        // Считываем символы порядка в отдельную строку
        i += 1;
        size_t j = 0;
        if (str_divident[i] == '+' || str_divident[i] == '-')
        {
            sign = str_divident[i];
            i++;
        }
        else
            return WRONG_ORDER;

        while (str_divident[i] != '\0' && str_divident[i] != '\n' && j < LEN_ORDER)
        {
            if (isdigit(str_divident[i]))
                order[j] = str_divident[i];
            i++;
            j++;
        }
        order[j] = '\0';

        // Проверка порядка на корректность и его запись в структуру
        res = strtol(order, &end, 10);
        if (*end || abs(res) > 99999)
            return WRONG_ORDER;
        if (sign == '-')
            res = 0 - res;

        divident->order += res;
    }
    return EXIT_SUCCESS;
}

// Корректно ли введен делитель (целое число)
int is_divisor_correct(int_t *divisor, char str_divisor[MAX_NUM_LEN + 2])
{
    size_t i;

    // Корректна ли длина строки
    if (strlen(str_divisor) > MAX_NUM_LEN + 1 || strlen(str_divisor) < 2)
        return WRONG_STR_LEN;

    str_divisor[strlen(str_divisor) - 1] = '\0';

    // Корректен ли знак числа
    if (str_divisor[0] == '-' && isdigit(str_divisor[1]))
        divisor->sign = '-';
    else if (str_divisor[0] == '+' && isdigit(str_divisor[1]))
        divisor->sign = '+';
    else
        return WRONG_SIGN;

    // Корректно ли введено целое число
    for (i = 1; str_divisor[i] != '\n' && str_divisor[i] != '\0'; i++)
    {
        if (isdigit(str_divisor[i]))
            divisor->number[i - 1] = str_divisor[i] - '0';
        else
            return INPUT_DIVISOR_ERROR;
    }
    divisor->num_len = i - 1;

    return EXIT_SUCCESS;
}

void print(FILE *f)
{
    char str[256];
    while (fgets(str, 256, f) != NULL)
        printf("%s", str);
}

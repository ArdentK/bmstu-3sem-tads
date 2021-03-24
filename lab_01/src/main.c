#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/defines_and_structures.h"
#include "../inc/input.h"
#include "../inc/division.h"
#include "../inc/array.h"

int main()
{
    FILE *f;
    char real_num[MAX_STR_LEN];
    char int_num[MAX_NUM_LEN + 2];
    real_t divident;
    int_t divisor;
    real_t result;
    int err;

    setbuf(stdout, NULL);

    f = fopen("txt/intro.txt", "r");
    print(f);
    fclose(f);

    f = fopen("txt/requirements_for_real_num.txt", "r");
    print(f);
    fclose(f);

    printf("\n                            ±|           мантисса          |порядок|\n");
    printf("                            -|---------|---------|---------|E±-----|\n");
    printf("                             1        10        20        30       \n");
    printf("Введите вещественное число: ");

    // Проверка ввода делимого (вещественного числа)
    if (!fgets(real_num, MAX_STR_LEN + 2, stdin))
        return INPUT_DIVIDENT_ERROR;

    err = is_divident_correct(&divident, real_num);
    if (err == WRONG_STR_LEN)
    {
        printf("Неверная длина строки.Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return WRONG_STR_LEN;
    }
    else if (err == WRONG_SIGN)
    {
        printf("Знак числа введен неверно. Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return WRONG_SIGN;
    }
    else if (err == TOO_LONG_NUM)
    {
        printf("Мантисса содержит более 30 цифр. Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return TOO_LONG_NUM;
    }
    else if (err == WRONG_ORDER)
    {
        printf("Ошибка в записи порядка числа. Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return WRONG_ORDER;
    }
    else if (err == INPUT_DIVIDENT_ERROR)
    {
        printf("Вещественно число (делимое) было введено неправильно."
               "\nПожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз\n\n");
        return INPUT_DIVIDENT_ERROR;
    }

    f = fopen("txt/requirements_for_int_num.txt", "r");
    print(f);
    fclose(f);

    printf("\n                     ±|           число            |\n");
    printf("                     -|--------|---------|---------|\n");
    printf("                      1       10        20        30       \n");
    printf("Введите целое число: ");

    // Проверка ввода делителя (целого числа)
    if (!fgets(int_num, MAX_NUM_LEN + 4, stdin))
        return INPUT_DIVISOR_ERROR;

    err = is_divisor_correct(&divisor, int_num);
    if (err == WRONG_STR_LEN)
    {
        printf("Неверная длина строки.Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return WRONG_STR_LEN;
    }
    else if (err == TOO_LONG_NUM)
    {
        printf("Число содержит более 30 цифр. Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return TOO_LONG_NUM;
    }
    else if (err == WRONG_SIGN)
    {
        printf("Знак числа введен неверно. Пожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return WRONG_SIGN;
    }
    else if (err == INPUT_DIVISOR_ERROR)
    {
        printf("Целое число (делитель) было введено неправильно."
               "\nПожалуйста, запустите программу заново и ознакомьтесь с требованиями к вводу еще раз.");
        return INPUT_DIVISOR_ERROR;
    }
    /*
    printf("\nПроверка: \n");
    real_print(divident);
    int_print(divisor);
*/
    // Деление
    err = division(divident, divisor, &result);

    if (err == DIVISION_BY_ZERO)
    {
        printf("Делитель не может быть равен нулю. Попробуйте еще раз.");
        return DIVISION_BY_ZERO;
    }
    else if (err == OVERLOW)
    {
        printf("Переполнение порядка. Попробуйте еще раз.");
        return OVERLOW;
    }

    // Вывод ответа
    printf("Ответ = %c0.", result.sign);
    print_array(result.number, result.num_len);
    printf("E%ld\n", result.order);

    return EXIT_SUCCESS;
}
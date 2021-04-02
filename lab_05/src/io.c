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

    if (*res < 0)
        return NOT_POSITIVE;

    return EXIT_SUCCESS;
}

void print_err(int err)
{
    if (err == INPUT_ERROR)
        printf("\nНекорректный ввод. Попробуйте еще раз\n");
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

void init_times(times_t *task)
{
    // Заявки типа T1 приходят по случайному закону с интервалом от 1 до 5
    task->in_time_t1[0] = 1;
    task->in_time_t1[1] = 5;

    // Заявки типа T1 обрабатываются по случайному закону с интервалом от 0 до 4
    task->oper_time_t1[0] = 0;
    task->oper_time_t1[1] = 4;

    // Заявки типа T2 приходят  по случайному закону с интервалом от 0 до 3
    task->in_time_t2[0] = 0;
    task->in_time_t2[1] = 3;

    // Заявки типа T2 обрабатываются по случайному закону с интервалом от 0 до 1
    task->oper_time_t2[0] = 0;
    task->oper_time_t2[1] = 1;
}

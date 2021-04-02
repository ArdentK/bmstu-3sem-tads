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

int input_point_of_grapth(graph_t *graph, size_t *point)
{
    printf("Введите номер вершины: ");

    int a = 0;

    if (scanf("%d", &a) != 1)
        return INPUT_ERROR;

    if (a < 1 || a > graph->num)
        return INPUT_ERROR;

    *point = a - 1;

    return EXIT_SUCCESS;
}

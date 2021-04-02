#define __USE_MINGW_ANSI_STDIO 1

#include "../inc/io.h"
#include "tree.h"

#define INDENT 5

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

int is_digit(char *str, long *res)
{
    char *end;

    str[strlen(str) - 1] = '\0';

    *res = strtol(str, &end, 10);
    if (*end)
        return INPUT_ERROR;

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
    else if (err == EMPTY_INPUT)
        printf("\nПустой ввод\n");
    else if (err == NOT_HASH_FUNC)
        printf("\nПревышено допустимое количество коллизий. Попробуйте еще раз\n");
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

void show_picture_status(char *name)
{
    printf("\nДля просмотра визуализации графа просьба открыть \nфайл '%s' в текущей директории.\n", name);
}

void print_tree(tree_node_t *node, size_t tab, int is_left, int is_right, unsigned int notch, int is_root)
{
    if (node)
    {
        print_tree(node->left, tab + 1, 1, 0, (is_left ? (notch << 1) : (notch << 1) | 1), 0);

        for (size_t i = 0; i < tab; i++)
        {
            if ((i != 0) && (notch & (1U << (tab - i - 1))))
                printf("|");
            else
                printf("  ");
            printf("%*s", INDENT, "");
        }

        printf("%s", (is_left ? "┌─" : (is_right ? "└─" : "")));

        int n = snprintf(NULL, 0, "%ld", node->data);
        printf("%.*s", (INDENT - n) * 3, "―――――");
        printf(" %ld ", node->data);

        if (is_root)
        {
            printf("├─");
        }
        // else
        // {
        //     if (node->left && node->right)
        //         printf("├─");
        //     else if (node->left)
        //         printf("─┘");
        //     else if (node->right)
        //         printf("─┐");
        // }
        printf("\n");

        print_tree(node->right, tab + 1, 0, 1, (is_right ? (notch << 1) : (notch << 1) | 1), 0);
    }
}

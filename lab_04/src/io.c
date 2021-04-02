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

node_t *list_add_end(node_t *head, node_t *word)
{
    node_t *curr = head;

    if (!head)
        return word;

    for (; curr->next; curr = curr->next)
        ;

    curr->next = word;

    return head;
}

node_t *list_add_front(node_t *head, node_t *elem)
{
    elem->next = head;
    return elem;
}

int node_create(FILE *f, node_t *new_elem)
{
    if (new_elem)
        new_elem->next = NULL;

    new_elem->word = malloc(STR_MAX * sizeof(char));

    if (!fgets(new_elem->word, STR_MAX + 1, f))
        return INPUT_ERROR;

    if ((strlen(new_elem->word) == STR_MAX + 1 && new_elem->word[strlen(new_elem->word) - 1] != '\n') || strlen(new_elem->word) < 2)
        return WRONG_STR;

    new_elem->word[strlen(new_elem->word) - 1] = '\0';

    return EXIT_SUCCESS;
}

void node_free(node_t *elem)
{
    free(elem->word);
    free(elem);
}

node_t *list_free_front(node_t *head)
{
    node_t *new_head;
    new_head = head->next;

    node_free(head);

    return new_head;
}

int create_list(size_t count, FILE *f, node_t **head)
{
    for (size_t i = 1; i < count; i++)
    {
        node_t *curr = malloc(sizeof(node_t));

        if (!curr)
            return MEMORY_ERROR;

        int err = node_create(f, curr);

        if (err)
        {
            list_free_all(head);
            return err;
        }

        *head = list_add_front(*head, curr);
    }

    return EXIT_SUCCESS;
}

void list_free_all(node_t **head)
{
    node_t *next;

    for (; *head; *head = next)
    {
        next = (*head)->next;
        node_free(*head);
    }
}

int add_elem_in_array(FILE *f, array_t *arr)
{
    arr->pos += 1;

    arr->words[arr->pos] = malloc(STR_MAX);

    if (!fgets(arr->words[arr->pos], STR_MAX + 1, f))
        return INPUT_ERROR;

    if ((strlen(arr->words[arr->pos]) == STR_MAX + 1 && arr->words[arr->pos][strlen(arr->words[arr->pos]) - 1] != '\n') || strlen(arr->words[arr->pos]) < 2)
        return WRONG_STR;

    arr->words[arr->pos][strlen(arr->words[arr->pos]) - 1] = '\0';

    return EXIT_SUCCESS;
}

int init_array(array_t *arr, long count, FILE *f)
{
    int err = EXIT_SUCCESS;
    // инициализация массива слов
    arr->words = malloc(2 * count * sizeof(char *));
    arr->pos = -1;

    while (arr->pos < count - 1 && !err)
    {
        err = add_elem_in_array(f, arr);
        //        printf("pos = %ld, word = %s\n", arr->pos, arr->words[arr->pos]);
    }
    /*
    for (long i = 0; i < count; i++)
        printf("i = %ld, word = %s\n", i, *(arr->words + i));
*/
    return err;
}

void free_array_t(array_t *arr)
{
    while (arr->pos > -1)
        del_last_arr_elem(arr);
    free(arr->words);
}

void del_last_arr_elem(array_t *arr)
{
    free(arr->words[arr->pos]);
    arr->pos -= 1;
}

int input_elem_count(FILE *f, size_t *count)
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX];
    long buf;

    if (f == stdin)
        printf("\nВведите количество элементов в списке: ");

    if (!fgets(str, STR_MAX + 1, f))
        return INPUT_ERROR;

    str[strlen(str) - 1] = '\0';

    err = is_pos_digit(str, &buf);
    if (err)
        return err;

    *count = buf;

    return EXIT_SUCCESS;
}

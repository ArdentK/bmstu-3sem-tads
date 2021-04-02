#define __USE_MINGW_ANSI_STDIO 1

#include "print.h"

void print_arr(array_t *arr, FILE *f_out)
{
    while (arr->pos > -1)
    {
        fprintf(f_out, "%41s\n", arr->words[arr->pos]);
        del_last_arr_elem(arr);
    }

    arr->pos = -1;
}

void print_arr_curr_state(array_t arr, FILE *f_out)
{
    if (arr.pos == -1)
    {
        fprintf(f_out, "     СТЕК ПУСТ    \n");
        return;
    }

    printf("\n|———————————————————————————————————————————|————————————————|\n");
    printf("|             Значение элемента             | Адрес элемента |\n");
    printf("|———————————————————————————————————————————|————————————————|\n");

    if (arr.pos == -1)
        fprintf(f_out, "     СТЕК ПУСТ    \n");

    for (int i = arr.pos; i > -1; i--)
        fprintf(f_out, "| %41s | %14p |\n", arr.words[i], &arr.words[i][0]);

    printf("|———————————————————————————————————————————|————————————————|\n");
}

node_t *print_list(node_t *head, FILE *f_out)
{
    for (; head; head = head->next)
    {
        fprintf(f_out, "%41s\n", head->word);
        free(head->word);
    }

    return NULL;
}

void print_list_curr_state(node_t *head, FILE *f_out)
{
    node_t *curr = head;

    if (!curr)
    {
        fprintf(f_out, "     СТЕК ПУСТ    \n");
        return;
    }
    printf("\n|———————————————————————————————————————————|————————————————|\n");
    printf("|             Значение элемента             | Адрес элемента |\n");
    printf("|———————————————————————————————————————————|————————————————|\n");

    for (; curr->next; curr = curr->next)
        fprintf(f_out, "| %41s | %14p |\n", curr->word, &curr->word[0]);

    fprintf(f_out, "| %41s | %14p |\n", curr->word, &curr->word[0]);
    printf("|———————————————————————————————————————————|————————————————|\n");
}
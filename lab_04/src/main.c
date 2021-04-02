#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "print.h"
#include "time_lapse.h"

int main()
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX];
    int choice;
    FILE *f_in, *f_out;
    size_t count = 0;
    array_t arr;
    node_t *head;

    setbuf(stdout, NULL);

    print_file("txt/intro.txt");
    print_file("txt/menu.txt");

    // Предоставление выбора пользователю
    printf("\n\nВведите ваш выбор: ");
    if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
    {
        printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
        return INPUT_ERROR;
    }

    while (choice)
    {
        if (choice == 1)
        {
            err = input_elem_count(stdin, &count);
            if (err)
            {
                print_err(err);
                return err;
            }

            head = malloc(sizeof(node_t));

            if (!head)
                return MEMORY_ERROR;

            int err = node_create(stdin, head);

            if (err)
                return err;

            err = create_list(count, stdin, &head);
            if (err)
            {
                print_err(err);
                return err;
            }

            printf("\n\nВведите ваш выбор: ");
            if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
            {
                printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                return INPUT_ERROR;
            }

            while (choice)
            {
                if (choice == 1)
                {
                    node_t *curr = malloc(sizeof(node_t));

                    if (!curr)
                        return MEMORY_ERROR;

                    int err = node_create(stdin, curr);

                    if (err)
                    {
                        list_free_all(&head);
                        return err;
                    }

                    head = list_add_front(head, curr);

                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_list_curr_state(head, stdout);
                }
                else if (choice == 2)
                {
                    head = list_free_front(head);

                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_list_curr_state(head, stdout);
                }
                else if (choice == 3)
                {
                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_list_curr_state(head, stdout);
                }
                else
                    break;

                printf("\n\nВведите ваш выбор: ");
                if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
                {
                    printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                    return INPUT_ERROR;
                }
            }

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПЕРЕД ВЫВОДОМ СЛОВ:\n");
            print_list_curr_state(head, stdout);

            printf("\nВЫВОД СЛОВ:\n");
            head = print_list(head, stdout);

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПОСЛЕ ВЫВОДА СЛОВ:\n");
            print_list_curr_state(head, stdout);

            list_free_all(&head);
        }

        else if (choice == 2)
        {
            err = input_elem_count(stdin, &count);
            if (err)
            {
                print_err(err);
                return err;
            }

            err = init_array(&arr, count, stdin);
            if (err)
            {
                print_err(err);
                return err;
            }

            printf("\n\nВведите ваш выбор: ");
            if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
            {
                printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                return INPUT_ERROR;
            }

            while (choice)
            {
                if (choice == 1)
                {
                    err = add_elem_in_array(stdin, &arr);
                    if (err)
                    {
                        print_err(err);
                        return err;
                    }
                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_arr_curr_state(arr, stdout);
                }
                else if (choice == 2)
                {
                    del_last_arr_elem(&arr);
                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_arr_curr_state(arr, stdout);
                }
                else if (choice == 3)
                {
                    printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА:\n");
                    print_arr_curr_state(arr, stdout);
                }
                else
                    break;

                printf("\n\nВведите ваш выбор: ");
                if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
                {
                    printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                    return INPUT_ERROR;
                }
            }

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПЕРЕД ВЫВОДОМ СЛОВ:\n");
            print_arr_curr_state(arr, stdout);

            printf("\nВЫВОД СЛОВ:\n");
            print_arr(&arr, stdout);

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПОСЛЕ ВЫВОДА СЛОВ:\n");
            print_arr_curr_state(arr, stdout);

            free_array_t(&arr);
        }

        else if (choice == 3)
        {
            err = select_file(str);

            if (err)
            {
                print_err(err);
                return err;
            }

            f_in = fopen(str, "r");

            err = input_elem_count(f_in, &count);
            if (err)
            {
                fclose(f_in);
                print_err(err);
                return err;
            }

            head = malloc(sizeof(node_t));

            if (!head)
                return MEMORY_ERROR;

            int err = node_create(f_in, head);

            if (err)
            {
                fclose(f_in);
                return err;
            }

            err = create_list(count, f_in, &head);
            if (err)
            {
                fclose(f_in);
                print_err(err);
                return err;
            }

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПЕРЕД ВЫВОДОМ СЛОВ:\n");
            print_list_curr_state(head, stdout);

            printf("\nВЫВОД СЛОВ:\n");
            head = print_list(head, stdout);

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПОСЛЕ ВЫВОДА СЛОВ:\n");
            print_list_curr_state(head, stdout);

            list_free_all(&head);
            fclose(f_in);
        }

        else if (choice == 4)
        {
            err = select_file(str);

            if (err)
            {
                print_err(err);
                return err;
            }

            f_in = fopen(str, "r");

            err = input_elem_count(f_in, &count);
            if (err)
            {
                fclose(f_in);
                print_err(err);
                return err;
            }

            err = init_array(&arr, count, f_in);
            if (err)
            {
                fclose(f_in);
                print_err(err);
                return err;
            }

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПОЕРЕД ВЫВОДОМ СЛОВ:\n");
            print_arr_curr_state(arr, stdout);

            printf("\nВЫВОД СЛОВ:\n");
            print_arr(&arr, stdout);

            printf("\nТЕКУЩЕЕ СОСТОЯНИЕ СТЕКА ПОСЛЕ ВЫВОДА СЛОВ:\n");
            print_arr_curr_state(arr, stdout);

            free_array_t(&arr);
            fclose(f_in);
        }

        else if (choice == 5)
        {
            printf("\n|                 |              Реализация стека              |              Реализация стека              |\n");
            printf("|                 |                  массивом                  |                    списком                 |\n");
            printf("|   Количество    |——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            printf("|    элементов    |  Добавление  |   Удаление   | Используемая |  Добавление  |   Удаление   | Используемая |\n");
            printf("|                 |——————————————|——————————————|    Память,   |——————————————|——————————————|    Память,   |\n");
            printf("|                 | Время, ticks | Время, ticks |       b      | Время, ticks | Время, ticks |       b      |\n");
            printf("|—————————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            printf("|        10       |");

            f_in = fopen("data/data_10.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        100      |");
            f_in = fopen("data/data_100.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        300      |");
            f_in = fopen("data/data_300.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        500      |");
            f_in = fopen("data/data_500.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        1000     |");
            f_in = fopen("data/data_1000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        2000     |");
            f_in = fopen("data/data_2000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        3000     |");
            f_in = fopen("data/data_3000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        4000     |");
            f_in = fopen("data/data_4000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        5000     |");
            f_in = fopen("data/data_5000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        6000     |");
            f_in = fopen("data/data_6000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        7000     |");
            f_in = fopen("data/data_7000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        8000     |");
            f_in = fopen("data/data_8000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|        9000     |");
            f_in = fopen("data/data_9000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);

            printf("|       10000     |");
            f_in = fopen("data/data_10000.txt", "r");
            f_out = fopen("out.txt", "w");
            err = time_lapse(f_in);
            fclose(f_in);
            fclose(f_out);
        }

        char buf[STR_MAX];
        fgets(buf, STR_MAX, stdin);

        printf("\n\nВведите ваш выбор (главное меню): ");
        if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
        {
            printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
            return INPUT_ERROR;
        }
    }

    return EXIT_SUCCESS;
}
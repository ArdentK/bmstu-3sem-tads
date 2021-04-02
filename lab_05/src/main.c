#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "time_lapse.h"
#include "list_func.h"
#include "array_func.h"
#include "model.h"

int main()
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX];
    int choice;
    //FILE *f_in, *f_out;

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
            queue_list_t *q_1, *q_2;
            q_1 = create_queue_list();
            q_2 = create_queue_list();

            err = model_list_queue(q_1, q_2);

            if (err)
                return err;

            free_queue_list(q_1);
            free_queue_list(q_2);
        }

        else if (choice == 2)
        {
            queue_array_t *q_1, *q_2;
            q_1 = create_queue_array();
            q_2 = create_queue_array();

            //printf("q_1 cur len = %zu\n", q_1->cur_len);
            //printf("q_2 cur len = %zu\n", q_2->cur_len);

            err = model_array_queue(q_1, q_2);

            if (err)
                return err;

            free_queue_array(q_1);
            free_queue_array(q_2);
        }
        else if (choice == 3)
        {
            printf("\n|————————————————————————————————————————————|————————————————————————————————————————————|\n");
            printf("|                               Количество элементов = 1000                               |\n");
            printf("|————————————————————————————————————————————|————————————————————————————————————————————|\n");
            printf("|              Реализация стека              |              Реализация стека              |\n");
            printf("|                    списком                 |                   массивом                 |\n");
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            printf("|  Добавление  |   Удаление   |              |  Добавление  |   Удаление   |              |\n");
            printf("|   в начало   |  последнего  | Используемая |   в начало   |  последнего  | Используемая |\n");
            printf("|——————————————|——————————————|    Память,   |——————————————|——————————————|    Память,   |\n");
            printf("| Время, ticks | Время, ticks |       b      | Время, ticks | Время, ticks |       b      |\n");
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");

            queue_list_t *list;
            queue_array_t *arr;

            list = create_queue_list();
            arr = create_queue_array();

            err = time_lapse(arr, list);
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");

            free_queue_array(arr);
            free_queue_list(list);
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
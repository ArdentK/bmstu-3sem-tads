#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "time_lapse.h"
#include "tree.h"
#include "hash.h"

int main()
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX], name[STR_MAX];
    int choice = 1;
    tree_node_t *head = NULL, *head_bal = NULL;
    FILE *f_in;
    FILE *f_out;
    hash_table_t hash_t;
    //int temp_value, rc, k;
    int num_of_collision = 0;
    int temp_cmp = 0;

    setbuf(stdout, NULL);

    print_file("txt/intro.txt");
    print_file("txt/menu.txt");

    while (choice)
    {
        // Предоставление выбора пользователю
        printf("\n\nВведите ваш выбор: ");
        if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
        {
            printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
            return INPUT_ERROR;
        }
        // Построение ДДП
        if (choice == 1)
        {
            err = select_file(name);
            if (err)
            {
                print_err(err);
                return err;
            }
            f_in = fopen(name, "r");
            head = init_tree(f_in);
            if (!head)
            {
                print_err(EMPTY_INPUT);
                return EMPTY_INPUT;
            }
            f_out = fopen("graph.gv", "w");
            export_dot_tree(f_out, head);
            fclose(f_out);
            fclose(f_in);
            system("dot -Tpng graph.gv -ograph.png");
            show_picture_status("graph.gv");

            int choice_2 = 1;
            while (choice_2)
            {
                // Предоставление выбора пользователю
                print_file("txt/menu_2.txt");
                if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice_2))
                {
                    printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                    return INPUT_ERROR;
                }

                if (choice_2)
                {
                    long num;
                    printf("Введите целое число: ");
                    if (!fgets(str, STR_MAX, stdin) || is_digit(str, &num))
                    {
                        printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                        return INPUT_ERROR;
                    }

                    del(head, num);

                    f_out = fopen("graph_after_del.gv", "w");
                    export_dot_tree(f_out, head);
                    fclose(f_out);
                    fclose(f_in);
                    system("dot -Tpng graph_after_del.gv -ograph_after_del.png");
                    show_picture_status("graph_after_del.gv");
                }
            }
        }
        // Балансировка дерева
        else if (choice == 2)
        {
            if (!head)
            {
                printf("Дерево пусто.\nПожалуйста, выберите пункт 1, чтобы построить дерево.\n");
                continue;
            }
            f_in = fopen(name, "r");
            head_bal = init_balance_tree(f_in);
            if (!head_bal)
            {
                print_err(EMPTY_INPUT);
                return EMPTY_INPUT;
            }
            f_out = fopen("graph_balance.gv", "w");
            export_dot_tree(f_out, head_bal);
            fclose(f_out);
            fclose(f_in);
            system("dot -Tpng graph_balance.gv -ograph_balance.png");
            show_picture_status("graph_balance.gv");
            print_tree(head_bal, 0, 0, 0, 0U, 0);

            int choice_2 = 1;
            while (choice_2)
            {
                // Предоставление выбора пользователю
                print_file("txt/menu_2.txt");
                if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice_2))
                {
                    printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                    return INPUT_ERROR;
                }

                if (choice_2)
                {
                    long num;
                    printf("Введите целое число: ");
                    if (!fgets(str, STR_MAX, stdin) || is_digit(str, &num))
                    {
                        printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                        return INPUT_ERROR;
                    }

                    del_in_avl(head_bal, num);

                    f_out = fopen("graph_bal_after_del.gv", "w");
                    export_dot_tree(f_out, head_bal);
                    fclose(f_out);
                    fclose(f_in);
                    system("dot -Tpng graph_bal_after_del.gv -ograph_bal_after_del.png");
                    show_picture_status("graph_bal_after_del.gv");
                    print_tree(head_bal, 0, 0, 0, 0U, 0);
                }
            }

            tree_free(head);
            tree_free(head_bal);
        }
        else if (choice == 3)
        {
            err = select_file(name);
            if (err)
            {
                print_err(err);
                return err;
            }
            f_in = fopen(name, "r");

            err = hash_table_init(&hash_t, START_SIZE);
            if (err)
            {
                print_err(err);
                return err;
            }

            char buf[STR_MAX];
            long max_colls = 0;
            printf("Введите максимальное количество коллизий: ");
            if (!fgets(buf, STR_MAX, stdin) || is_digit(buf, &max_colls))
            {
                printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                return INPUT_ERROR;
            }

            err = create_hash_table(&hash_t, START_SIZE, f_in, &num_of_collision, &temp_cmp, max_colls);
            if (err)
            {
                print_err(err);
                return err;
            }

            fclose(f_in);

            print_hash_table(&hash_t);

            int choice_2 = 1;
            while (choice_2)
            {
                // Предоставление выбора пользователю
                print_file("txt/menu_2.txt");
                if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice_2))
                {
                    printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                    return INPUT_ERROR;
                }

                if (choice_2)
                {
                    long num;
                    printf("Введите целое число: ");
                    if (!fgets(str, STR_MAX, stdin) || is_digit(str, &num))
                    {
                        printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
                        return INPUT_ERROR;
                    }

                    if (delete_in_hash_table(&hash_t, num, &temp_cmp))
                        printf("\nЗначение было успешно удалено\n");
                    else
                        printf("\nДанного значения нет в таблице\n");

                    print_hash_table(&hash_t);
                }
            }
        }
        else if (choice == 4)
        {
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            printf("|              |      Удаление из ДДП        |    Удаление из сбаланс.     |         Удаление из         |      Удаление из файла      |\n");
            printf("|  Количество  |                             |           дерева            |         хеш-таблицы         |                             |\n");
            printf("|   элементов  |——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            printf("|              | Время, ticks |   Память, b  | Время, ticks |   Память, b  | Время, ticks |   Память, b  | Время, ticks |   Память, b  |\n");
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");

            time_lapse("data/test.txt", 30);
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            time_lapse("data/data_100.txt", 100);
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            time_lapse("data/data_500.txt", 500);
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
            time_lapse("data/data_2000.txt", 2000);
            printf("|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|——————————————|\n");
        }
    }

    return EXIT_SUCCESS;
}
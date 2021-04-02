#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "graph_matrix_func.h"

int main()
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX];
    int choice;
    graph_t *graph;
    size_t point = 0;
    FILE *f_in;

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
            // Выбор файла
            err = select_file(str);
            if (err)
            {
                print_err(err);
                return err;
            }

            f_in = fopen(str, "r");

            // Создание графа из файла
            graph = create_graph_from_file(f_in);

            // Ввод вершины
            err = input_point_of_grapth(graph, &point);

            fclose(f_in);

            //  Поиск недостижимых вершин
            find_points(*graph, point);

            // Экспорт в язык dot
            FILE *file = fopen("temp_reach.txt", "w");
            export_dot_reachability(file, graph, point);
            fclose(file);
            system("dot -Tpng temp_reach.txt -otemp_reach.png");
        }

        char buf[STR_MAX];
        fgets(buf, STR_MAX, stdin);

        printf("\n\nВведите ваш выбор: ");
        if (!fgets(str, STR_MAX, stdin) || my_choice(str, &choice))
        {
            printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
            return INPUT_ERROR;
        }
    }

    return EXIT_SUCCESS;
}
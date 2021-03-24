#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "multiplication.h"
#include "time_lapse.h"

int main()
{
    int err = EXIT_SUCCESS;
    char str[STR_MAX];
    int choice;
    FILE *f;
    FILE *f_std;
    matrix_t std_mtx;
    std_vector_t std_v, std_res;
    sparse_t sp_mtx;
    sparse_vector_t sp_v, sp_res;

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
        // Ввод с клавиатуры в стандартном виде
        if (choice == 1)
        {
            err = std_input_matrix(stdin, &std_mtx);
            if (err)
            {
                print_err(err);
                return err;
            }

            err = std_input_vector(stdin, &std_v);
            if (err)
            {
                print_err(err);
                return err;
            }
            /*
            printf("\nВведенная матрица:\n");
            
            printf("main rows = %zu\n", std_mtx.rows);
            printf("main cols = %zu\n Elems:\n", std_mtx.columns);
            
            for (size_t i = 0; i < std_mtx.rows; i++)
            {
                for (size_t j = 0; j < std_mtx.columns; j++)
                    printf("%ld ", std_mtx.A[i][j]);
                printf("\n");
            }
            
            //std_output_matrix(std_mtx);

            printf("Введенный вектор:\n");
            std_output_vector(std_v);

            err = can_multiply_std(std_v, std_mtx);
            if (err)
            {
                print_err(err);
                return err;
            }
*/
            std_multiplication(std_v, std_mtx, &std_res);

            printf("\nОтвет: \n");
            std_output_vector(std_res);
        }

        // Ввод с клавиатуры в разреженном виде
        else if (choice == 2)
        {
            err = input_matrix(stdin, &sp_mtx);
            if (err)
            {
                print_err(err);
                return err;
            }

            err = input_vector(stdin, &sp_v);
            if (err)
            {
                print_err(err);
                return err;
            }

            err = can_multiply_sparse(sp_v, sp_mtx);
            if (err)
            {
                print_err(err);
                return err;
            }

            sparse_multiplication(sp_v, sp_mtx, &sp_res);

            output_vector(sp_res);
        }

        // Выбор готового файла с данными
        else if (choice == 3)
        {
            err = select_file(str);

            if (err)
            {
                print_err(err);
                return err;
            }

            printf("\n\nВведите 0, если этот файл содержит матрицы в стандартном виде или 1, если в разреженном: ");

            int format;

            if (scanf("%d", &format) != 1 || format < 0 || format > 1)
            {
                print_err(INPUT_ERROR);
                return INPUT_ERROR;
            }

            f = fopen(str, "r");

            if (format)
            {
                err = input_matrix(f, &sp_mtx);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                printf("\nПолученная матрица:");
                output_matrix(sp_mtx);

                err = input_vector(f, &sp_v);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                printf("\nПолученный вектор:");
                output_vector(sp_v);

                err = can_multiply_sparse(sp_v, sp_mtx);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                sparse_multiplication(sp_v, sp_mtx, &sp_res);

                printf("\nОтвет: \n");
                output_vector(sp_res);
            }
            else
            {
                err = std_input_matrix(f, &std_mtx);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                printf("\nПолученная матрица:\n");
                std_output_matrix(std_mtx);

                err = std_input_vector(f, &std_v);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                printf("\nПолученный вектор:");
                std_output_vector(std_v);

                err = can_multiply_std(std_v, std_mtx);
                if (err)
                {
                    print_err(err);
                    fclose(f);
                    return err;
                }

                std_multiplication(std_v, std_mtx, &std_res);

                printf("\nОтвет: \n");
                std_output_vector(std_res);
            }

            fclose(f);
        }

        else if (choice == 4)
        {
            err = std_input_matrix(stdin, &std_mtx);
            if (err)
            {
                print_err(err);
                return err;
            }

            err = std_input_vector(stdin, &std_v);
            if (err)
            {
                print_err(err);
                return err;
            }

            from_std_to_sparse_mtx(std_mtx, &sp_mtx);
            from_std_to_sparse_vector(std_v, &sp_v);

            printf("\nВведенная матрица:\n");
            output_matrix(sp_mtx);

            printf("\nВведенный вектор:\n");
            output_vector(sp_v);

            sparse_multiplication(sp_v, sp_mtx, &sp_res);

            printf("\nОтвет: \n");
            output_vector(sp_res);
        }

        else if (choice == 5)
        {
            printf("\n                                     10x10                                        \n");
            printf("|—————————————————————————————————————————————————————————————————————————————————|\n");
            printf("|                 |  Стандартный способ хранения  |  Специальный способ хранения  |\n");
            printf("| %% разреженности |——————————————|————————————————|———————————————|———————————————|\n");
            printf("|                 | Время, ticks |    Память, b   |  Время, ticks |   Память, b   |\n");
            printf("|—————————————————|——————————————|————————————————|———————————————|———————————————|\n");
            printf("|        5%%       |");

            f = fopen("data/sparse/data_10x10_5%.txt", "r");
            f_std = fopen("data/std/data_10x10_5%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        10%%      |");
            f = fopen("data/sparse/data_10x10_10%.txt", "r");
            f_std = fopen("data/std/data_10x10_10%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        20%%      |");
            f = fopen("data/sparse/data_10x10_20%.txt", "r");
            f_std = fopen("data/std/data_10x10_20%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        30%%      |");
            f = fopen("data/sparse/data_10x10_30%.txt", "r");
            f_std = fopen("data/std/data_10x10_30%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        40%%      |");
            f = fopen("data/sparse/data_10x10_40%.txt", "r");
            f_std = fopen("data/std/data_10x10_40%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        50%%      |");
            f = fopen("data/sparse/data_10x10_50%.txt", "r");
            f_std = fopen("data/std/data_10x10_50%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        60%%      |");
            f = fopen("data/sparse/data_10x10_60%.txt", "r");
            f_std = fopen("data/std/data_10x10_60%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        70%%      |");
            f = fopen("data/sparse/data_10x10_70%.txt", "r");
            f_std = fopen("data/std/data_10x10_70%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        80%%      |");
            f = fopen("data/sparse/data_10x10_80%.txt", "r");
            f_std = fopen("data/std/data_10x10_80%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        90%%      |");
            f = fopen("data/sparse/data_10x10_90%.txt", "r");
            f_std = fopen("data/std/data_10x10_90%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        100%%     |");
            f = fopen("data/sparse/data_10x10_100%.txt", "r");
            f_std = fopen("data/std/data_10x10_100%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|—————————————————————————————————————————————————————————————————————————————————|\n");
            printf("|                                     60x60                                       |\n");
            printf("|—————————————————————————————————————————————————————————————————————————————————|\n");
            printf("|                 |  Стандартный способ хранения  |  Специальный способ хранения  |\n");
            printf("| %% разреженности |——————————————|————————————————|———————————————|———————————————|\n");
            printf("|                 | Время, ticks |    Память, b   |  Время, ticks |   Память, b   |\n");
            printf("|—————————————————|——————————————|————————————————|———————————————|———————————————|\n");
            printf("|        5%%       |");
            f = fopen("data/sparse/data_60x60_5%.txt", "r");
            f_std = fopen("data/std/data_60x60_5%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        10%%      |");
            f = fopen("data/sparse/data_60x60_10%.txt", "r");
            f_std = fopen("data/std/data_60x60_10%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        20%%      |");
            f = fopen("data/sparse/data_60x60_20%.txt", "r");
            f_std = fopen("data/std/data_60x60_20%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        30%%      |");
            f = fopen("data/sparse/data_60x60_30%.txt", "r");
            f_std = fopen("data/std/data_60x60_30%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        40%%      |");
            f = fopen("data/sparse/data_60x60_40%.txt", "r");
            f_std = fopen("data/std/data_60x60_40%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        50%%      |");
            f = fopen("data/sparse/data_60x60_50%.txt", "r");
            f_std = fopen("data/std/data_60x60_50%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        60%%      |");
            f = fopen("data/sparse/data_60x60_60%.txt", "r");
            f_std = fopen("data/std/data_60x60_60%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        70%%      |");
            f = fopen("data/sparse/data_60x60_70%.txt", "r");
            f_std = fopen("data/std/data_60x60_70%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        80%%      |");
            f = fopen("data/sparse/data_60x60_80%.txt", "r");
            f_std = fopen("data/std/data_60x60_80%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        90%%      |");
            f = fopen("data/sparse/data_60x60_90%.txt", "r");
            f_std = fopen("data/std/data_60x60_90%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        100%%     |");
            f = fopen("data/sparse/data_60x60_100%.txt", "r");
            f_std = fopen("data/std/data_60x60_100%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|—————————————————————————————————————————————————————————————————————————————————|\n");
            printf("|                                    100x100                                      |\n");
            printf("|—————————————————————————————————————————————————————————————————————————————————|\n");
            printf("|                 |  Стандартный способ хранения  |  Специальный способ хранения  |\n");
            printf("| %% разреженности |——————————————|————————————————|———————————————|———————————————|\n");
            printf("|                 | Время, ticks |    Память, b   |  Время, ticks |   Память, b   |\n");
            printf("|—————————————————|——————————————|————————————————|———————————————|———————————————|\n");
            printf("|        5%%       |");
            f = fopen("data/sparse/data_100x100_5%.txt", "r");
            f_std = fopen("data/std/data_100x100_5%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        10%%      |");
            f = fopen("data/sparse/data_100x100_10%.txt", "r");
            f_std = fopen("data/std/data_100x100_10%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        20%%      |");
            f = fopen("data/sparse/data_100x100_20%.txt", "r");
            f_std = fopen("data/std/data_100x100_20%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        30%%      |");
            f = fopen("data/sparse/data_100x100_30%.txt", "r");
            f_std = fopen("data/std/data_100x100_30%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        40%%      |");
            f = fopen("data/sparse/data_100x100_40%.txt", "r");
            f_std = fopen("data/std/data_100x100_40%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        50%%      |");
            f = fopen("data/sparse/data_100x100_50%.txt", "r");
            f_std = fopen("data/std/data_100x100_50%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        60%%      |");
            f = fopen("data/sparse/data_100x100_60%.txt", "r");
            f_std = fopen("data/std/data_100x100_60%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        70%%      |");
            f = fopen("data/sparse/data_100x100_70%.txt", "r");
            f_std = fopen("data/std/data_100x100_70%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        80%%      |");
            f = fopen("data/sparse/data_100x100_80%.txt", "r");
            f_std = fopen("data/std/data_100x100_80%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        90%%      |");
            f = fopen("data/sparse/data_100x100_90%.txt", "r");
            f_std = fopen("data/std/data_100x100_90%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);

            printf("|        100%%     |");
            f = fopen("data/sparse/data_100x100_100%.txt", "r");
            f_std = fopen("data/std/data_100x100_100%.txt", "r");
            err = time_lapse(f, f_std, std_v, std_mtx, std_res, sp_v, sp_mtx, sp_res);
            if (err)
            {
                print_err(err);
                return err;
            }
            fclose(f);
            fclose(f_std);
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
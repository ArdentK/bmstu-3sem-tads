#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#include "../inc/defines.h"
#include "../inc/in_out.h"
#include "../inc/sort.h"
#include "../inc/delete.h"
#include "../inc/time_lapse.h"

int main()
{
    FILE *f;
    car_t cars[MAX_NUM]; // массив записей
    int len = 0;
    int choice;
    int err = EXIT_SUCCESS;
    char str[MAX_LEN];
    char field[MAX_LEN], value[MAX_LEN];
    key_price_t key[MAX_NUM];
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;

    setbuf(stdout, NULL);

    // Открытие и чтение заготовленных данных из файла
    f = fopen("data/data_40.txt", "r");

    if (!f)
    {
        printf("Неверное имя файла");
        return OPEN_FILE_ERROR;
    }

    // Вывод приветствия и меню программы
    print_file("txt/intro.txt");
    print_file("txt/menu.txt");

    err = read_data(f, cars, &len);

    if (err)
    {
        printf("Неверные входные данные");
        return INPUT_ERROR;
    }

    // Предоставление выбора пользователю
    printf("Введите ваш выбор: ");
    if (!fgets(str, MAX_LEN, stdin) || my_choice(str, &choice))
    {
        printf("\nЧисло было введено неверно. Попробуйте еще раз\n");
        return INPUT_ERROR;
    }

    while (choice)
    {
        // Вывод меню
        print_file("txt/menu.txt");

        // 1 - вывод данных
        if (choice == 1)
            print_data(cars, len);

        // 2 - добавление новой записи в массив записей
        else if (choice == 2)
        {
            err = append(cars, &len);
            if (err)
            {
                print_error(err);
                return err;
            }
        }

        // 3 - удаление записей
        else if (choice == 3)
        {
            err = input_field(field);

            if (err)
            {
                print_error(err);
                return err;
            }

            input_value(value);
            delete_elem(field, value, cars, &len);
        }

        // 4 - вывод цен не новых машин указанной марки с одним предыдущим собственником, отсутствием ремонта в указанном диапазоне цен
        else if (choice == 4)
        {
            err = menu_4(cars, len);

            if (err)
            {
                print_error(err);
                return err;
            }
        }

        // 5 - вывод упорядоченной исходной таблицы
        else if (choice == 5)
        {
            qsort(cars, len, sizeof(car_t), compare_price);
            print_data(cars, len);
        }

        // 6 - вывод упорядоченной таблицы ключей (цены автомобиля)
        else if (choice == 6)
        {
            create_arr_of_key(cars, len, key);
            qsort(key, len, sizeof(key_price_t), compare_price_key);
            print_key(key, len);
        }

        // 7 - вывод упорядоченной таблицы с использованием таблицы ключей
        else if (choice == 7)
        {
            create_arr_of_key(cars, len, key);
            qsort(key, len, sizeof(key_price_t), compare_price_key);
            print_by_new_table(cars, key, len);
        }

        // 8 - вывод эффективности разных алгоритмов сортировки на разных данных
        else if (choice == 8)
        {
            printf("           |  Медленная сортировка |  Медленная сортировка |   Быстрая сортировка  |   Быстрая сортировка \n"
                   "Количество |    исходной таблицы   |     таблицы ключей    |    исходной таблицы   |     таблицы ключей   \n"
                   "элементов  |———————————|———————————|———————————|———————————|———————————|———————————|———————————|——————————\n"
                   "           | время, µs | память, b | время, µs | память, b | время, µs | память, b | время, µs | память, b\n");
            printf("———————————|———————————|———————————|———————————|———————————|———————————|———————————|———————————|——————————\n");

            // Замер времени для сортировки 100 элементов
            f = fopen("data/data_100.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 500 элементов
            f = fopen("data/data_500.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 1000 элементов
            f = fopen("data/data_1000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 2000 элементов
            f = fopen("data/data_2000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 3000 элементов
            f = fopen("data/data_3000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 4000 элементов
            f = fopen("data/data_4000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 5000 элементов
            f = fopen("data/data_5000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 6000 элементов
            f = fopen("data/data_6000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 7000 элементов
            f = fopen("data/data_7000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 8000 элементов
            f = fopen("data/data_8000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 9000 элементов
            f = fopen("data/data_9000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);

            // Замер времени для сортировки 10000 элементов
            f = fopen("data/data_10000.txt", "r");
            err = time_lapse(f, cars, key, len);
            fclose(f);
        }
        else
            printf("Такого пункта в меню нет. Пожалуйста, выберите существующий пункт\n");

        // Предоставление пользователю выбора
        printf("\nВведите ваш выбор: ");
        if (!fgets(str, MAX_LEN, stdin) || my_choice(str, &choice))
        {
            printf("\nЧисло было введено неверно. Попробуйте еще раз.\n");
            return INPUT_ERROR;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}
#include "../inc/time_lapse.h"

#define N 5

int time_lapse(FILE *f, car_t cars[], key_price_t key[], int len)
{
    int err = EXIT_SUCCESS;
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time = 0;

    //Замер времени для медленной сортировка (вставками) исходной таблицы
    for (int i = 0; i < N; i++)
    {
        fseek(f, SEEK_SET, 0);
        err = read_data(f, cars, &len);
        if (err)
            return INPUT_ERROR;

        gettimeofday(&tv_start, NULL);
        insertion_sort(cars, len);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000 + tv_stop.tv_usec - tv_start.tv_usec;
        //printf("insertion_sort = %lld µs, size = %zu b\n", elapsed_time, sizeof(car_t) * len);
    }

    elapsed_time /= N;

    printf("%10d |", len);
    printf("%10lld | %9zu | ", elapsed_time, sizeof(car_t) * len);
    //printf("insertion_sort = %lld µs, size = %zu b\n", elapsed_time, sizeof(car_t) * len);

    elapsed_time = 0;
    // Замер времени для сортровки вставками таблицы ключей
    for (int i = 0; i < N; i++)
    {
        // Чтение данных из файла
        fseek(f, SEEK_SET, 0);
        err = read_data(f, cars, &len);
        if (err)
            return INPUT_ERROR;

        gettimeofday(&tv_start, NULL);
        create_arr_of_key(cars, len, key);
        insertion_sort_with_new_table(key, len);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000 + tv_stop.tv_usec - tv_start.tv_usec;
        //printf("insertion_sort_with_new_table = %lld µs, size = %zu b\n", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);
    }

    elapsed_time /= N;
    printf("%9lld | %9zu | ", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);
    //printf("insertion_sort_with_new_table = %lld µs, size = %zu b\n", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);

    elapsed_time = 0;
    // Замер времени для быстрой сортировки исходной таблицы
    for (int i = 0; i < N; i++)
    {
        fseek(f, SEEK_SET, 0);
        err = read_data(f, cars, &len);
        if (err)
            return INPUT_ERROR;

        gettimeofday(&tv_start, NULL);
        qsort(cars, len, sizeof(car_t), compare_price);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000 + tv_stop.tv_usec - tv_start.tv_usec;
        //printf("qsort = %lld µs, size = %zu b\n", elapsed_time, sizeof(car_t) * len);
    }

    elapsed_time /= N;
    printf("%9lld | %9zu | ", elapsed_time, sizeof(car_t) * len);
    //printf("qsort = %lld µs, size = %zu b\n", elapsed_time, sizeof(car_t) * len);

    elapsed_time = 0;
    // Замер времени для быстрой сортировки таблицы ключей
    for (int i = 0; i < N; i++)
    {
        fseek(f, SEEK_SET, 0);
        err = read_data(f, cars, &len);
        if (err)
            return INPUT_ERROR;

        gettimeofday(&tv_start, NULL);
        create_arr_of_key(cars, len, key);
        qsort(key, len, sizeof(key_price_t), compare_price_key);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000 + tv_stop.tv_usec - tv_start.tv_usec;
        //printf("qsort with new table = %lld µs, size = %zu b\n", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);
    }

    elapsed_time /= N;

    printf("%9lld | %9zu\n", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);
    //printf("qsort with new table = %lld µs, size = %zu b\n", elapsed_time, (sizeof(key_price_t) + sizeof(car_t)) * len);

    return err;
}
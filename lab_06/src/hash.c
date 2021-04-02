#define __USE_MINGW_ANSI_STDIO 1

#include "hash.h"

int HASHING_MODE = 0;

int Hash_UInt_M3(long long key, int size)
{
    key ^= (key << 13);
    key ^= (key >> 17);
    key ^= (key << 5);
    return abs(key % size);
}

int hash6432shift(long long key, int size)
{
    key = (~key) + (key << 18); // key = (key << 18) - key - 1;
    key = key ^ (key >> 31);
    key = key * 21; // key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);
    return abs(key % size);
}

int hash32shiftmult(int key, int size)
{
    int c2 = 0x27d4eb2d; // a prime or an odd constant
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * c2;
    key = key ^ (key >> 15);
    return abs(key % size);
}

int hash(int key, int table_size)
{
    switch (HASHING_MODE)
    {
    case 0:
        return Hash_UInt_M3(key, table_size);
    case 1:
        return hash6432shift(key, table_size);
    case 2:
        return hash32shiftmult(key, table_size);
    }
    return TRUE;
}

void clean_hash_table(data_record_t *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        arr[i].is_free = TRUE;
        arr[i].is_deleted = FALSE;
    }
}

int create_hash_table(hash_table_t *hash_t, int size, FILE *f, int *num_of_collisions, int *temp_cmp, int max_colls)
{
    int err = hash_table_init(hash_t, size);
    if (err)
        return err;

    int buf;
    while (fscanf(f, "%d", &buf) == 1)
    {
        insert_in_hash_table(hash_t, buf, num_of_collisions, temp_cmp);
        if (*num_of_collisions > max_colls)
        {
            printf("\nПревышено допустимое число коллизий. Хеш-таблица будет реструктурирована\n");
            change_hash_function(hash_t);
        }
        if (HASHING_MODE > 2)
            return NOT_HASH_FUNC;
    }

    return EXIT_SUCCESS;
}

int hash_table_init(hash_table_t *hash_t, int size)
{
    int err = EXIT_SUCCESS;
    data_record_t *temp = malloc(size * sizeof(data_record_t));

    if (!temp)
    {
        err = MEMORY_ERROR;
        return err;
    }

    hash_t->arr = temp;
    hash_t->table_size = size;
    hash_t->cur_size = 0;

    clean_hash_table(hash_t->arr, hash_t->table_size);

    return EXIT_SUCCESS;
}

int resize_hash_table(hash_table_t *hash_t)
{
    hash_table_t temp_hash_t;
    int num = 0;
    int temp_cmp = 0;

    int err = hash_table_init(&temp_hash_t, hash_t->table_size * 2);
    if (err)
        return err;

    // перезаписываем сатрые значения в новую табличу с новой хэшфункцией
    for (int i = 0; i < hash_t->table_size; ++i)
    {
        if (!hash_t->arr[i].is_free && hash_t->arr[i].is_deleted != TRUE)
        {
            insert_in_hash_table(&temp_hash_t, hash_t->arr[i].data, &num, &temp_cmp);
        }
    }
    // обновляем старую хэштаблицу
    free(hash_t->arr);
    *hash_t = temp_hash_t;

    return EXIT_SUCCESS;
}

void insert_in_hash_table(hash_table_t *hash_t, int data, int *num_of_collision, int *temp_cmp)
{
    if (hash_t->cur_size == hash_t->table_size)
        resize_hash_table(hash_t);

    int in_table = find_in_hash_table(hash_t, data, temp_cmp);
    if (in_table)
        return;

    int index = hash(data, hash_t->table_size);

    if (hash_t->arr[index].is_free == FALSE)
        *num_of_collision += 1;

    while (hash_t->arr[index].is_free == FALSE)
    {
        *temp_cmp += 1;
        index = (index + 1) % hash_t->table_size;
    }

    hash_t->arr[index].data = data;
    hash_t->arr[index].is_free = FALSE;
    hash_t->arr[index].is_deleted = FALSE;
    hash_t->cur_size += 1;
}

int find_in_hash_table(hash_table_t *hash_t, int data, int *temp_cmp)
{
    int index = hash(data, hash_t->table_size);

    while (hash_t->arr[index].is_free == FALSE || hash_t->arr[index].is_deleted == TRUE)
    {
        *temp_cmp += 1;

        if (hash_t->arr[index].is_deleted && hash_t->arr[index].data == data)
            return FALSE;

        if (hash_t->arr[index].data == data)
            return TRUE;

        index = (index + 1) % hash_t->table_size;
    }

    return FALSE;
}

int delete_in_hash_table(hash_table_t *hash_t, int data, int *num_cmp)
{
    int index = hash(data, hash_t->table_size);

    while (hash_t->arr[index].is_free == FALSE || hash_t->arr[index].is_deleted)
    {
        *num_cmp += 1;

        if (hash_t->arr[index].is_deleted)
            if (hash_t->arr[index].data == data)
                return FALSE;

        if (hash_t->arr[index].data == data)
        {
            hash_t->arr[index].is_free = TRUE;
            hash_t->arr[index].is_deleted = TRUE;
            --hash_t->cur_size;

            return TRUE; // вернули 1 - удачно удалили элемент
        }
        index = (index + 1) % hash_t->table_size;
    }

    return FALSE;
}

int change_hash_function(hash_table_t *hash_t)
{
    HASHING_MODE++;
    int num_of_collision = 0;

    if (HASHING_MODE >= 2)
    {
        printf("\nБольше хеш-функций нет.:(\n");
        return FALSE;
    }

    hash_table_t temp_hash_t;
    int temp_cmp = 0;
    hash_table_init(&temp_hash_t, hash_t->table_size);

    // перезаписываем старые значения в новую табличу с новой хэшфункцией
    for (int i = 0; i < hash_t->table_size; ++i)
        if (!hash_t->arr[i].is_free && hash_t->arr[i].is_deleted != TRUE)
            insert_in_hash_table(&temp_hash_t, hash_t->arr[i].data, &num_of_collision, &temp_cmp);

    // обновляем старую хэштаблицу
    free(hash_t->arr);
    *hash_t = temp_hash_t;

    return num_of_collision;
}

void print_hash_table(hash_table_t *hash_t)
{
    printf("\nХеш-таблица\n");
    printf("Выделено памяти под хеш-таблицу = %d,\n реально занимаемый размер хеш-таблицы = %d\n", hash_t->table_size, hash_t->cur_size);

    printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n");
    printf("┃  Значение хэш-функции  ┃    Данные    ┃\n");
    for (int i = 0; i < hash_t->table_size; i++)
    {
        printf("┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n");

        if (hash_t->arr[i].is_free == FALSE)
            printf("┃%24d┃%14d┃\n", hash(hash_t->arr[i].data, hash_t->table_size), hash_t->arr[i].data);
        else
            printf("┃                    empty              ┃\n");
    }
}

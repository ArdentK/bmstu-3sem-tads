#include "../inc/sort.h"

void insertion_sort_with_new_table(key_price_t key[], int len)
{
    size_t size = sizeof(key_price_t);

    for (int i = 0; i < len; i++)
        for (int j = i; j > 0 && key[j].price < key[j - 1].price; j--)
            swap(&key[j], &key[j - 1], size);
}

void insertion_sort(car_t cars[], int len)
{
    size_t size = sizeof(car_t);

    for (int i = 0; i < len; i++)
        for (int j = i; j > 0 && cars[j].price < cars[j - 1].price; j--)
            swap(&cars[j], &cars[j - 1], size);
}

void swap(void *p, void *q, size_t elem_size)
{
    char buf[elem_size];
    char *a = p;
    char *b = q;

    memcpy(buf, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, buf, elem_size);
}

void create_arr_of_key(car_t cars[], int len, key_price_t key[])
{
    for (int i = 0; i < len; i++)
    {
        key[i].index = i;
        key[i].price = cars[i].price;
    }
}

int compare_price(const void *p, const void *q)
{
    const car_t *a = p;
    const car_t *b = q;

    return a->price - b->price;
}

int compare_price_key(const void *p, const void *q)
{
    const key_price_t *a = p;
    const key_price_t *b = q;

    return a->price - b->price;
}

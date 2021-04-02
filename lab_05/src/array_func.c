#define __USE_MINGW_ANSI_STDIO 1

#include "array_func.h"

#define init_capacity 8

queue_array_t *create_queue_array()
{
    queue_array_t *arr = malloc(sizeof(queue_array_t));

    arr->max_len = init_capacity;
    arr->buf = calloc(init_capacity, sizeof(request_t));
    arr->head = 0;
    arr->tail = 0;
    arr->cur_len = 0;

    return arr;
}

void make_empty_queue_array(queue_array_t *arr)
{
    arr->head = 0;
    arr->tail = 0;
    arr->cur_len = 0;
}

queue_array_t *resize_queue_array(queue_array_t *arr, size_t new_size)
{
    arr->buf = realloc(arr->buf, sizeof(new_size * sizeof(request_t)));
    arr->max_len = new_size;
    arr->head = 0;
    arr->tail = 0;
    arr->cur_len = 0;

    return arr;
}

void free_queue_array(queue_array_t *arr)
{
    free(arr->buf);
    free(arr);
}

int is_full_queue_array(queue_array_t *arr)
{
    return (arr->cur_len == arr->max_len);
}

int is_empty_queue_array(queue_array_t *arr)
{
    int err = !(arr->cur_len);

    return err;
}

void increase_queue_array(queue_array_t *arr)
{
    size_t new_max_len = arr->max_len * 2;
    request_t *buf = malloc(new_max_len * sizeof(request_t));
    size_t cur_len = arr->cur_len;
    request_t *end = buf + cur_len;

    while (!is_empty_queue_array(arr))
    {
        end--;
        pop_queue_array(arr, end);
    }

    free(arr->buf);

    arr->buf = buf;
    arr->max_len = new_max_len;
    arr->head = 0;
    arr->tail = cur_len;
}

void push_queue_array(queue_array_t *arr, request_t *new_elem)
{
    if (is_full_queue_array(arr))
        increase_queue_array(arr);

    arr->buf[arr->tail] = *new_elem;
    arr->tail = (arr->tail + 1) % arr->max_len;
    arr->cur_len += 1;
}

int pop_queue_array(queue_array_t *arr, request_t *del)
{
    if (is_empty_queue_array(arr))
        return 0;

    if (del)
        *del = arr->buf[arr->head];

    arr->head = (arr->head + 1) % arr->max_len;
    arr->cur_len -= 1;

    return 1;
}

/*
int pop_queue_array(queue_array_t *arr, request_t *del)
{
    if (is_empty_queue_array(arr))
        return 0;

    if (del)
        *del = arr->buf[arr->head];

    //arr->head = (arr->head + 1) % arr->max_len;
    arr->cur_len--;
    for (size_t i = 0; i < arr->cur_len; i++)
        arr->buf[i] = arr->buf[i + 1];

    return 1;
}
*/

size_t get_queue_array_memory_size(size_t max_len)
{
    size_t mem = sizeof(queue_array_t *) + sizeof(queue_array_t) + sizeof(request_t) * max_len;

    return mem;
}

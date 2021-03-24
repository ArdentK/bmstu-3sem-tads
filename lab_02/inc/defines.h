#ifndef DEFINES_H
#define DEFINES_H

#define MAX_LEN 40
#define MAX_NUM 10000

#define EXIT_SUCCESS 0
#define OPEN_FILE_ERROR -1
#define ARGS_ERROR -2
#define INPUT_ERROR -3
#define WRONG_LEN -4
#define NOT_DIGIT -5
#define NEGATIVE -6

typedef struct
{
    char brand[MAX_LEN];   // Марка машины
    char country[MAX_LEN]; // Страна производителя
    long price;            // Цена машины
    char colour[MAX_LEN];  // Цвет машины
    int type;              // 0 - машина новая, 1 - машина подержанная
    union
    {
        struct
        {
            int warranty; // гарантия в годах
        } is_new;

        struct
        {
            int year;    // Год выпуска
            int mileage; // Пробег
            int repairs; // Количество ремонтов
            long owners; // Количество предыдущих владельцев
        } not_new;

    } state;
} car_t;

typedef struct
{
    int index;  // Индекс элемента
    long price; // Цена элемента
} key_price_t;

#endif //DEFINES_H
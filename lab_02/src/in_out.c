#include "../inc/in_out.h"

#define MAX_STR_LEN 256

// Вывод соответсвующих комментариев к кодам ошибок
void print_error(int err)
{
    if (err == INPUT_ERROR)
        printf("Ошибка ввода. Попробуйте еще раз.");
    else if (err == WRONG_LEN)
        printf("Неверная длина строки. Попробуйте еще раз.");
    else if (err == NOT_DIGIT)
        printf("Было введено не число. Попробуйте еще раз.");
    else if (err == NEGATIVE)
        printf("Число не может быть отрицательным. Попробуйте снова.");
}

// Проверка правильности ввода выбора пользователя
int my_choice(char *str, int *c)
{
    long res;

    str[strlen(str) - 1] = '\0';

    if (is_digit(str, &res))
        return INPUT_ERROR;

    *c = res;

    return EXIT_SUCCESS;
}

// Введено ли число
int is_digit(char *str, long *res)
{
    char *end;

    *res = strtol(str, &end, 10);
    if (*end)
        return INPUT_ERROR;

    return EXIT_SUCCESS;
}

// Добавление новой записи в массив (не пользователем)
int append_car(char *str, car_t *car)
{
    char *a;
    char *a_next;
    long res;
    char *end;
    char *sep = " \n";

    a = strtok(str, sep);
    strcpy(car->brand, a);
    //printf("brand = %s ", car->brand);

    a = strtok(NULL, sep);
    strcpy(car->country, a);
    //printf("country = %s ", car->country);

    a = strtok(NULL, sep);
    if (is_digit(a, &res))
        return INPUT_ERROR;
    car->price = res;
    //printf("price = %ld ", car->price);

    a = strtok(NULL, sep);
    strcpy(car->colour, a);
    //printf("colour = %s ", car->colour);

    a = strtok(NULL, sep);
    a_next = strtok(NULL, sep);

    if (is_digit(a, &res))
        return INPUT_ERROR;

    // Проверка, новая ли машина
    if (!a_next)
    {
        car->type = 0;
        car->state.is_new.warranty = res;
        //printf("warranty = %d\n", car->state.is_new.warranty);
        return EXIT_SUCCESS;
    }
    else
        car->type = 1;

    car->state.not_new.year = res;
    //printf("year = %d ", car->state.not_new.year);

    if (is_digit(a_next, &res))
        return INPUT_ERROR;

    car->state.not_new.mileage = res;
    //printf("mileage = %d ", car->state.not_new.mileage);

    a = strtok(NULL, sep);
    if (is_digit(a, &res))
        return INPUT_ERROR;
    car->state.not_new.repairs = res;
    //printf("repairs = %d ", car->state.not_new.repairs);

    a = strtok(NULL, sep);
    res = strtol(a, &end, 10);
    if (*end)
        return INPUT_ERROR;
    car->state.not_new.owners = res;
    //printf("owners = %d ", car->state.not_new.owners);

    return EXIT_SUCCESS;
}

// Чтение исходных данных из файла
int read_data(FILE *f, car_t cars[], int *len)
{
    char str[MAX_STR_LEN];
    *len = 0;
    car_t car;
    int err = EXIT_SUCCESS;

    while (fgets(str, MAX_STR_LEN, f) && !err)
    {
        *len += 1;
        err = append_car(str, &car);
        cars[*len - 1] = car;
    }

    //printf("len = %d ", *len);

    return err;
}

// Вывод 1 записи
void print_car(car_t car)
{
    printf("%15s", car.brand);
    printf("%15s", car.country);
    printf("%12ld", car.price);
    printf("%8s", car.colour);

    if (car.type == 0)
        printf("%8ld\n", car.state.is_new.warranty);
    else
    {
        printf("%8ld", car.state.not_new.year);
        printf("%8ld", car.state.not_new.mileage);
        printf("%5ld", car.state.not_new.repairs);
        printf("%5ld\n", car.state.not_new.owners);
    }
}

// Вывод содержания файла на экран
int print_file(char *name)
{
    FILE *f;
    char str[256];

    f = fopen(name, "r");

    if (!f)
        return OPEN_FILE_ERROR;

    while (fgets(str, 256, f) != NULL)
        printf("%s", str);

    fclose(f);
}

// Вывод данных
void print_data(car_t cars[], int len)
{
    for (int i = 0; i < len; i++)
        print_car(cars[i]);
}

// Добавление пользователем новой записи в массив
int append(car_t cars[], int *len)
{
    char str[MAX_LEN];
    car_t car;
    long res;

    printf("Предупреждаем! размер строки не должен превышать 40 символов\n"
           "После ввода каждого поля нажмите enter.\n");

    // Ввод марки машины
    printf("\nВведите марку машины: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    strcpy(car.brand, str);

    // Ввод страны производителя
    printf("Введите страну производителя: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    strcpy(car.country, str);

    // Ввод цены автомобиля
    printf("Введите цену автомобиля: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    if (is_digit(str, &res))
        return NOT_DIGIT;
    if (res < 0)
        return NEGATIVE;
    car.price = res;

    // Ввод цвета машины
    printf("Введите цвет машины: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    strcpy(car.colour, str);

    // Новая ли машина?
    printf("Машина новая: [yes/no] ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    if (strcmp(str, "yes") == 0)
        car.type = 0;
    else if (strcmp(str, "no") == 0)
        car.type = 1;
    else
        return INPUT_ERROR;

    if (!car.type)
    {
        printf("Введите гарантию на автомобиль (в годах): ");
        if (!fgets(str, MAX_LEN + 2, stdin))
            return INPUT_ERROR;
        if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
            return WRONG_LEN;
        str[strlen(str) - 1] = '\0';
        if (is_digit(str, &res))
            return NOT_DIGIT;
        if (res < 0)
            return NEGATIVE;
        car.state.is_new.warranty = res;
    }
    else
    {
        printf("Введите год выпуска автомобиля: ");
        if (!fgets(str, MAX_LEN + 2, stdin))
            return INPUT_ERROR;
        if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
            return WRONG_LEN;
        str[strlen(str) - 1] = '\0';
        if (is_digit(str, &res))
            return NOT_DIGIT;
        if (res < 0)
            return NEGATIVE;
        car.state.not_new.year = res;

        printf("Введите пробег автомобиля: ");
        if (!fgets(str, MAX_LEN + 2, stdin))
            return INPUT_ERROR;
        if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
            return WRONG_LEN;
        str[strlen(str) - 1] = '\0';
        if (is_digit(str, &res))
            return NOT_DIGIT;
        if (res < 0)
            return NEGATIVE;
        car.state.not_new.mileage = res;

        printf("Введите количество ремонтов: ");
        if (!fgets(str, MAX_LEN + 2, stdin))
            return INPUT_ERROR;
        if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
            return WRONG_LEN;
        str[strlen(str) - 1] = '\0';
        if (is_digit(str, &res))
            return NOT_DIGIT;
        if (res < 0)
            return NEGATIVE;
        car.state.not_new.repairs = res;

        printf("Введите количество предыдущих владельцев: ");
        if (!fgets(str, MAX_LEN + 2, stdin))
            return INPUT_ERROR;
        if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
            return WRONG_LEN;
        str[strlen(str) - 1] = '\0';
        if (is_digit(str, &res))
            return NOT_DIGIT;
        if (res < 0)
            return NEGATIVE;
        car.state.not_new.owners = res;
    }

    // Добавление новой машины в список машин
    cars[*len] = car;
    *len += 1;

    return EXIT_SUCCESS;
}

// Выполнение пункта меню 4
int menu_4(car_t cars[], int len)
{
    char str[MAX_LEN];
    char brand[MAX_LEN];
    long min, max;
    long buf;

    printf("Введите марку машины: ");
    if (!fgets(brand, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(brand) == MAX_LEN + 1 && brand[strlen(brand) - 1] != '\n' || strlen(brand) < 2)
        return WRONG_LEN;
    brand[strlen(brand) - 1] = '\0';

    printf("Далее следует ввести диапазон цен.\n");
    printf("Введите минимальное число: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    if (is_digit(str, &min))
        return NOT_DIGIT;
    if (min < 0)
        return NEGATIVE;

    printf("Введите максимальное число: ");
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;
    str[strlen(str) - 1] = '\0';
    if (is_digit(str, &max))
        return NOT_DIGIT;
    if (max < 0)
        return NEGATIVE;

    if (min > max)
    {
        buf = min;
        min = max;
        max = buf;
        printf("Границы диапазона цен были поменяны местами.\n");
    }

    for (int i = 0; i < len; i++)
    {
        if (cars[i].type && strcmp(cars[i].brand, brand) == 0 &&
            cars[i].state.not_new.repairs == 0 &&
            cars[i].price >= min && cars[i].price <= max &&
            cars[i].state.not_new.owners == 1)
            print_car(cars[i]);
    }

    return EXIT_SUCCESS;
}

// Вывод записей, отсортированных с использованием дополнительной таблицы ключей
void print_by_new_table(car_t cars[], key_price_t key[], int len)
{
    for (int i = 0; i < len; i++)
        print_car(cars[key[i].index]);
}

// Вывод таблицы ключей
void print_key(key_price_t key[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%5d %12ld\n", key[i].index, key[i].price);
}
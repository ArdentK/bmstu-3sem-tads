#include "../inc/delete.h"
#include "../inc/in_out.h"

int input_field(char *field)
{
    char str[MAX_LEN];

    //Указания к вводу
    printf("\nВыберете одно из следующих полей для удаления\n");
    printf("1. brand\n");
    printf("2. country\n");
    printf("3. price\n");
    printf("4. colour\n");
    printf("Если машина новая:\n");
    printf("                 5. warranty\n");
    printf("Если машина подержанная:\n");
    printf("                 5. year\n");
    printf("                 6. mileage\n");
    printf("                 8. number of repairs\n");
    printf("                 9. number of owners\n");

    printf("Введите название выбранного вами поля: ");

    // Проверка правильности ввода
    if (!fgets(str, MAX_LEN + 2, stdin))
        return INPUT_ERROR;

    if (strlen(str) == MAX_LEN + 1 && str[strlen(str) - 1] != '\n' || strlen(str) < 2)
        return WRONG_LEN;

    str[strlen(str) - 1] = '\0';

    // Запись
    if (strcmp(str, "brand") == 0)
        strcpy(field, "brand");

    else if (strcmp(str, "country") == 0)
        strcpy(field, "country");

    else if (strcmp(str, "price") == 0)
        strcpy(field, "price");

    else if (strcmp(str, "colour") == 0)
        strcpy(field, "colour");

    else if (strcmp(str, "warranty") == 0)
        strcpy(field, "warranty");

    else if (strcmp(str, "year") == 0)
        strcpy(field, "year");

    else if (strcmp(str, "mileage") == 0)
        strcpy(field, "mileage");

    else if (strcmp(str, "number of repairs") == 0)
        strcpy(field, "repairs");

    else if (strcmp(str, "number of owners") == 0)
        strcpy(field, "owners");

    else
        return INPUT_ERROR;

    return EXIT_SUCCESS;
}

int input_value(char value[MAX_LEN])
{
    printf("\nЗаписи, содержащие данное значение в выбранном ранее поле, будут удалены.");
    printf("\nВведите значение выбранного поля:");

    // Проверка правильности ввода
    if (!fgets(value, MAX_LEN + 2, stdin))
        return INPUT_ERROR;
    if (strlen(value) == MAX_LEN + 1 && value[strlen(value) - 1] != '\n' || strlen(value) < 2)
        return WRONG_LEN;

    value[strlen(value) - 1] = '\0';

    return EXIT_SUCCESS;
}

void offset(car_t cars[], int *len, int index)
{
    for (int i = index; i < *len - 1; i++)
        cars[i] = cars[i + 1];
    *len -= 1;
}

void delete_elem(char *field, char *value, car_t cars[], int *len)
{
    if (strcmp(field, "brand") == 0)
        delete_by_brand(cars, len, value);
    else if (strcmp(field, "country") == 0)
        delete_by_country(cars, len, value);
    else if (strcmp(field, "price") == 0)
        delete_by_price(cars, len, value);
    else if (strcmp(field, "colour") == 0)
        delete_by_colour(cars, len, value);
    else if (strcmp(field, "warranty") == 0)
        delete_by_warranty(cars, len, value);
    else if (strcmp(field, "year") == 0)
        delete_by_year(cars, len, value);
    else if (strcmp(field, "mileage") == 0)
        delete_by_mileage(cars, len, value);
    else if (strcmp(field, "repairs") == 0)
        delete_by_repairs(cars, len, value);
    else if (strcmp(field, "owners") == 0)
        delete_by_owners(cars, len, value);
}

void delete_by_brand(car_t cars[], int *len, char *value)
{
    int i = 0;

    while (i < *len)
    {
        if (strcmp(cars[i].brand, value) == 0)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_country(car_t cars[], int *len, char *value)
{
    int i = 0;

    while (i < *len)
    {
        if (strcmp(cars[i].country, value) == 0)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_price(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (cars[i].price == res)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_colour(car_t cars[], int *len, char *value)
{
    int i = 0;

    while (i < *len)
    {
        if (strcmp(cars[i].colour, value) == 0)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_warranty(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (!cars[i].type && cars[i].state.is_new.warranty == res)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_year(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (cars[i].type && cars[i].state.not_new.year == res)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_mileage(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (cars[i].type && cars[i].state.not_new.mileage == res)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_repairs(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (cars[i].type && cars[i].state.not_new.repairs == res)
            offset(cars, len, i);
        else
            i++;
    }
}

void delete_by_owners(car_t cars[], int *len, char *value)
{
    int i = 0;
    long res;

    if (is_digit(value, &res))
        return;

    while (i < *len)
    {
        if (cars[i].type && cars[i].state.not_new.owners == res)
            offset(cars, len, i);
        else
            i++;
    }
}
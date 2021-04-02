#ifndef _MODEL_H
#define _MODEL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list_func.h"
#include "array_func.h"
#include "defines.h"
#include "io.h"

// Получпение рандомного действительного числа в заданном диапазоне
double random_double(double bottom, double top);

// Расчет оживаемого среднего времени работы
double calculate_time(times_t queue, size_t requests_num);

// Моделирование очереди на списке
int model_list_queue(queue_list_t *q_1, queue_list_t *q_2);

// Моделирование очереди на массиве
int model_array_queue(queue_array_t *q_1, queue_array_t *q_2);

#endif
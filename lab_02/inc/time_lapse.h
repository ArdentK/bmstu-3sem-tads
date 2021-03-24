#ifndef TIME_LAPSE_H
#define TIME_LAPSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "sort.h"
#include "in_out.h"

// Замер времени работы и необходимой памяти для разных алгоритмов сортировки
int time_lapse(FILE *f, car_t cars[], key_price_t key[], int len);

#endif //TIME_LAPSE_H
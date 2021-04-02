#ifndef TIME_LAPSE_H
#define TIME_LAPSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "list_func.h"
#include "array_func.h"

uint64_t ticks(void);
int time_lapse(queue_array_t *arr, queue_list_t *list);

#endif //TIME_LAPSE_H
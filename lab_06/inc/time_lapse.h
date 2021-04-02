#ifndef TIME_LAPSE_H
#define TIME_LAPSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "file.h"
#include "hash.h"
#include "tree.h"

uint64_t ticks(void);
void time_lapse(char name[STR_MAX], int count);

#endif //TIME_LAPSE_H
#ifndef TIME_LAPSE_H
#define TIME_LAPSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "print.h"

uint64_t tick(void);
int time_lapse(FILE *f_in);

#endif //TIME_LAPSE_H
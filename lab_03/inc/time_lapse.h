#ifndef TIME_LAPSE_H
#define TIME_LAPSE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "defines.h"
#include "io.h"
#include "multiplication.h"

uint64_t tick(void);
// Замер времени работы и необходимой памяти для разных алгоритмов умножения
int time_lapse(FILE *f_sparse, FILE *f_std, std_vector_t std_v, matrix_t std_mtx, std_vector_t std_res, sparse_vector_t sp_v, sparse_t sp_mtx, sparse_vector_t sp_res);

#endif //TIME_LAPSE_H
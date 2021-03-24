#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

void sparse_multiplication(sparse_vector_t vector, sparse_t mtx, sparse_vector_t *res);
void std_multiplication(std_vector_t vector, matrix_t mtx, std_vector_t *res);
int can_multiply_sparse(sparse_vector_t vector, sparse_t mtx);
int can_multiply_std(std_vector_t vector, matrix_t mtx);

#endif // MULTIPLICATION_H
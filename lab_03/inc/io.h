#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <defines.h>

void print_err(int err);
void std_output_matrix(matrix_t mtx);
void output_matrix(sparse_t mtx);
void std_output_vector(std_vector_t vector);
void output_vector(sparse_vector_t vector);

int std_input_matrix(FILE *f, matrix_t *mtx);
int std_input_vector(FILE *f, std_vector_t *vector);

int input_matrix(FILE *f, sparse_t *mtx);
int input_vector(FILE *f, sparse_vector_t *vector);

void from_std_to_sparse_mtx(matrix_t mtx, sparse_t *new_mtx);
void from_std_to_sparse_vector(std_vector_t vector, sparse_vector_t *new_vector);

int is_pos_digit(char *str, long *res);
int my_choice(char *str, int *c);
int print_file(char *name);
int select_file(char name[STR_MAX]);

#endif // IO_H
#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "io.h"

void print_arr_curr_state(array_t arr, FILE *f_out);
void print_arr(array_t *arr, FILE *f_out);
node_t *print_list(node_t *head, FILE *f_out);
void print_list_curr_state(node_t *head, FILE *f_out);

#endif
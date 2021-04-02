#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "defines.h"

int find_in_file(char name[STR_MAX], int data, int *temp_cmp);
void delete_in_file(char name[STR_MAX], int data, int *temp_cmp, uint64_t *time);

#endif //FILE_H
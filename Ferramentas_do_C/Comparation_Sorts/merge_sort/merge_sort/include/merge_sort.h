#ifndef MERGE_H
#define MERGE_H

#include <stdlib.h>
#include <stdio.h>

typedef int type_data;

void merge_sort(type_data *A, int size);
void merge_sort_recursion(type_data *A, int l, int r);
void merge_sort_arrays(type_data *A, int l, int m, int r);

#endif
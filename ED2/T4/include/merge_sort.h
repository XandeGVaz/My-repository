#ifndef MERGE_H
#define MERGE_H

#include "aux.h"

typedef struct type_data data;
//////// Declaração de funções do merge sort//////////////////////////////////////////////////////////
void merge_sort(data *A, int size);
void merge_sort_recursion(data *A, int l, int r);
void merge_sort_arrays(data *A, int l, int m, int r);
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef int type_data;

void heap_sort(type_data *A, int size);
void organize_heap(type_data *A, int i, int size);
void controy_heap(type_data *A, int size);

#endif
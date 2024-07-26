#ifndef AUX_H
#define AUX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct type_data data;

////////////////Definição funções auxiliares///////////////////////////////////////
bool left_smaller_than(const data* A1, const data*A2, int a, int b);
data* make_data_array(int size);
void print_data_array(const data* A,int size);
void change_space(data* A, int a, int b);
data* return_invert_array(const data* A, int size, int size_invert);
int return_aprov(const data* A, int N, int M);
data* return_valid_array(const data* A, int size);
int len_valid_array(const data* A, int size);
///////////////////////////////////////////////////////////////////////////////////
#endif
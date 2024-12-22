#ifndef BUSCA_H
#define BUSCA_H

#include "indice.h"
#include "leitura.h"

// funcoes de busca
int busca_bin_string(char *nome_bin, char *nome_campo, char *valor_campom, int mode);
int busca_bin_int(char *nome_bin, char *nome_campo, int valor_campo, int mode);
int busca_bin_float(char *nome_bin, char *nome_campo, float valor_campo, int mode);

// busca no arquivo indice
int busca_arvoreB(FILE* arq, indCabecalho cab, long val, int *RRN_lista, int *tamLista);
long busca_em_nodo(FILE *arq, int noRRN, long val);

#endif
#ifndef BUSCA_H
#define BUSCA_H

#include "leitura.h"
#include "impressao.h"
#include "manipBin.h"

// funcoes de busca
int busca_bin_string(char *nome_bin, char *nome_campo, char *valor_campom, int mode);
int busca_bin_int(char *nome_bin, char *nome_campo, int valor_campo, int mode);
int busca_bin_float(char *nome_bin, char *nome_campo, float valor_campo, int mode);

#endif
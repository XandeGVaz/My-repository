#ifndef MANIPCAB_H
#define MANIPCAB_H

#include "leitura.h"

// manipulacao do cabecalho
void cabecalho_inicia(cabecalho* cab_aux);
int escreve_cab_bin(FILE *fp, cabecalho cab);
int set_status(FILE *fp, char c);
int set_topo(FILE *fp, int topo);
int set_proxRRN(FILE *fp, int prox);
int set_nroRegRem(FILE *fp, int removidos);
int set_nroPagDisco(FILE *fp, int paginas);
int set_qttCompacta(FILE *fp, int qtd);
int atualiza_nroPag(int proxRRN);






#endif
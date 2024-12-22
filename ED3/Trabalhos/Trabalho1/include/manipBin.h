#ifndef MANIPBIN_H
#define MANIPBIN_H

#include "leitura.h"
#include "entrada.h"
#include "busca.h"
#include "manipCab.h"

/* manipulacao do .bin */

// escrita em .bin
int escreve_reg_bin(FILE *fp, registro reg);
int escreve_reg_RRN(FILE *fp, registro reg, int RRN);
int escreve_rem_RRN(FILE* fp, int encad, int RRN);

// criação de arquivo .bin
int cria_bin(char* arq_in, char* arq_out);

// remoção de arquivo .bin
int remove_reg_bin(FILE* fp, int RRN);
int loop_remocoes(char* nome_bin, char* nome_campo, int mode);
int remove_nreg_bin(char *nome_bin, int n);

// inserção em arquivo .bin
int insere_reg_bin(FILE *fp, registro reg);
int insere_nreg_bin(char *nome_bin, int n);

// compactação em arquivo.bin
int compacta_bin(char *nome_bin);







#endif
#ifndef MANIPARVB_H
#define MANIPARVB_H

#include "leitura.h"
#include "busca.h"
#include "indice.h"
#include "impressao.h"
#include "entrada.h"
#include "manipBin.h"

// manipulação da Árvore B //

// criacao do arquivo indice : Árvore B
int cria_arquivo_ArvoreB(char* arq_in, char* arq_out);

// escrita de dados no cabecalho do arquivo indice
void inicia_cab_ind(indCabecalho *cab_aux);
int escreve_cab_ind(FILE *arq, indCabecalho cab);

// escrita de dados no arquivo indice                                                                 
void inicia_nodo_ind(indNodo *nodo_aux, char folha, int RRNdoNo);
int escreve_nodo_ind(FILE *arq, indNodo nodo);
int escreve_indNodo_RRN(FILE *arq, indNodo nodo , int RRN);
int atualiza_nodo_ind(FILE* arq, indNodo nodo);

// insercao no arquivo indice
int insere_arvoreB(FILE *arq, long valor, int RRN);

// etapas intermediárias da inserção
indNodo ordena_campos(indNodo *nodo, campo valor);
int insere_em_nodo(FILE *fp, campo valor, int *RRN_lista, int tamLista);
void analisa_valores(const indNodo* nodo, campo valor, campo* vetor_aux);
campo split(FILE *fp, campo valor, indNodo *nodo);

// função para inserção simultânea no arquivo de dados e arquivo indice
int insere_nreg_ambos(char* nome_dados, char* nome_arvore, int n);

# endif
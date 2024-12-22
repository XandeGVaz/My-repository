#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes_fornecidas.h"
#include "indice.h"

#define TAM_REG 160     // tamanho do registro em bytes
#define TAM_PAG 1600    // tamanho da página de disco em bytes
#define ERRO -50        // flag de erro
#define REM -100        // flag de remoção
#define OK -135         // flag de exito

#define DEBUG 1

//  STRUCTS

/*Definição da struct de registro
    -> Struct que corresponde a um registro de tamanho fixo
    -> Campos fixos e variáveis
    -> O total de espaço ocupado corresponde a TAM_REG == 160 bytes
*/
typedef struct{
    char removido;
    int encadeamento;
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    char nome[40];
    char especie[30];
    char habitat[30];
    char tipo[30];
    char dieta[30];
    char alimento[30];
} registro;


/*Definição da struct de cabeçalho
    -> Struct que corresponde a um cabeçalho de tamanho fixo
    -> Campos fixos
    -> O total de espaço ocupado corresponde a TAM_PAG == 1600 bytes
*/
typedef struct{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} cabecalho;

// leitura do BIN
cabecalho le_cab_bin(FILE *ptr_arq, int* f);
registro le_reg_bin(FILE *ptr_arq, int* f);
registro le_reg_RRN(FILE *ptr_arq, int* f, int RRN);

// leitura do CSV
registro le_campos_csv(FILE* ptr_arq, int first);

// leitura do arquivo indice (árvore B)
indCabecalho le_cab_ind(FILE *arq, int *f);
indNodo le_nodo_ind(FILE *arq, int *f);
indNodo le_indNodo_RRN(FILE *arq, int *f, int RRN);

#endif
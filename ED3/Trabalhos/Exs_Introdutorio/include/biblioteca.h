// Primeiro Exercício Prático - arquivo header de funções do programa
/*Alunos:
 *Vitor Alexandre Garcia Vaz(14611432)
 *Vitor Pardini Saconi(14611800)
*/
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define REG_TAM 131 //tamanho do registro

//Declaração da struct de registro
typedef struct t_registro reg;


//Declaração de funções usadas no programa principal (explicações no arquivo .c correspondente)
void adicionar_especies(FILE* arq, char* arqNome, int qntReg); //comando=1
int recuperar_especies(FILE* arq, char* arqName); //comando=2
void recuperar_RRN(FILE* arq, char* arqName, int RRN); //comando=3
void completar_especie(FILE* arq, char* arqName, int qntInfo, int ID); //comando=4


#endif

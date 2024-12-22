#ifndef INDICE_H
#define INDICE_H

// macros usada para debug do código
#define NDEBUG 0              

#define TAM_INDPAG 93           // tamanho das paginas de disco do arquivo indice
#define ORDEM 5                 // ordem da árvore B (m)
#define TAXA_OCUPAPAG 3         // taxa de ocupacao = (m/2) , arrendondando para cima
#define TAXA_OCUPAFOLHA 2       // taxa de ocupacao da folha = (m/2) - 1 , arredondando para cima
#define MEIO (int)(ORDEM/2)     // referrente ao índice de um elemento que será promovido no split 

// STRUCTS indice

/*Definiçao da struct de cabecalho do indice
    -> Campos e o cabecalho tem tamanhos fixos
    -> Deve corresponder ao tamanho de paginas de disco
*/
typedef struct{
    char status;            // byte-offset = 0
    int noRaiz;             // byte-offset = 1
    int RRNproxNo;          // byte-offset = 5
}indCabecalho;

/*Definicao da struct de nodo do indice
    -> Campos e nodo tem tamanho fixo
    -> Nodo corresponde a uma pagina de disco do indice
*/
typedef struct{
    char folha;             // byte-offset = 0
    int nroChavesNo;        // byte-offset = 1
    int RRNdoNo;            // byte-offset = 5
    int P[ORDEM];           // byte-offset = 9 + (i * 20) 
    long C[ORDEM-1];        // byte-offset = 13 + (i * 20)
    long Pr[ORDEM-1];       // byte-offset = 21 + (i * 20)
}indNodo;

/* Definição de struct auxiliar que contem C[x], Pr[x] e P[x+1] */
typedef struct{
    long C;
    long Pr;
    int P;
} campo;

#endif
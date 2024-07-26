#include "selection_sort.h"

typedef struct type_data {
    char nome[10]; //nome do aluno
    float nota; //nota ponderada
    int reprov; //reprovações
}data;

////////////////Função de uso do selection-sort /////////////////////////////////////////////////////
void selection_sort(data* A, int size){
    int smaller;
    /*Indice do menor elemento começa a cada laço no primeiro elemento da porção que ainda
    não está plenamente em ordem*/
    for(int i=0;i<size;i++){
        smaller=i;
        /*Se um elemento for menor que o indicado pelo indice menor,entao o indice passa a indicar
        esse elemento*/
        for(int j=i+1;j<size;j++){
            if(left_smaller_than(A,A,j,smaller)){
                smaller=j;
            }
        }
        /*O menor e o primeiro elemento da parte do vetor ainda nao ordenada sao trocados de
        lugar no vetor*/
        change_space(A,i,smaller);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

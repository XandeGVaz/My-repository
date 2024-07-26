#include "selection_sort.h"

//Função auxiliar que troca dois elementos da lista/vetor de lugar 
void change_space(type_data* A, int a, int b){
    type_data aux;
    aux=A[b];
    A[b]=A[a];
    A[a]=aux;
}


void selection_sort(type_data* A, int size){
    int smaller;
    /*Indice do menor elemento começa a cada laço no primeiro elemento da porção que ainda
    não está plenamente em ordem*/
    for(int i=0;i<size;i++){
        smaller=i;
        /*Se um elemento for menor que o indicado pelo indice menor,entao o indice passa a indicar
        esse elemento*/
        for(int j=i+1;j<size;j++){
            if(A[j]<A[smaller]){
                smaller=j;
            }
        }
        /*O menor e o primeiro elemento da parte do vetor ainda nao ordenada sao trocados de
        lugar no vetor*/
        change_space(A,i,smaller);
    }
}

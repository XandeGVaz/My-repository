#include "quick_sort.h"

//Função auxiliar que troca dois elementos da lista/vetor de lugar 
void change_space(type_data* A, int a, int b){
    type_data aux;
    aux=A[b];
    A[b]=A[a];
    A[a]=aux;
}

//Função recursiva do quick sort
void quick_sort_recursion(type_data* A, int begin, int end){
    int i,j;
    i=begin;
    
    /* i e j partem do começo do vetor.A cada passo j aumenta em 1. Se o elemento indicado por 
    j for menor que o último elemento(A[fim]=pivo), os elementos indicados por i e j trocam de lugar e i 
    passa a indicar o próximo elemento. Dessa forma, todos os elementos antes de i serao menores
    que o ultimo elemento de A, e os elementos entre i e j serao maiores que tal ultimo elemento*/
    for(j=i;j<end;j++){
        if(A[j]<A[end]){
            change_space(A,i,j);
            i++;
        }
    }
    
    /* como o for termina com j=end, todos os elementos antes de i e de i para o final serao
    , respectivamente, menores e maiores que A[fim], com isso podemos trocar A[fim] e A[i],
    pois assim A[fim] estara em seu lugar adequado no vetor ordenado*/
    change_space(A,i,end);

    //o mesmo processo acontece para as sublistas/subvetores antes e depois do pivo
    if(begin<i-1) quick_sort_recursion(A,begin,i-1);
    if(end>i+1) quick_sort_recursion(A,i+1,end);
}

void quick_sort(type_data* A, int size){
    quick_sort_recursion(A,0,size-1);
}

/*
Alunos [No USP]: 
Vitor Alexandre Garcia Vaz [14611432]
Vitor Pardini Saconi [14611800]
*/

#include "bubble_sort.h"

void bubble_sort(type_data *vetor , int tamanho)
{
    //Flag que sinaliza 1 enquanto o vetor não está ordenado.
    int flag=1;

    //Auxiliar usado para trocas de valores entre elementos do vetor.
    int aux=0;
    
    while(flag){
        /* 
            Se nao houver troca, a flag continua zerada, sinalizando 
            que o vetor está ordenado.
        */
        flag=0;

        for(int i=0;i<(tamanho-1);i++){
            
            if(vetor[i]>vetor[i+1]){
                /* 
                Se o elemento atual for maior que o proximo elemento, os valores 
                entre eles são trocados e a flag continua igual a um, ou seja, 
                houve troca de valores e o vetor ainda não esta ordenado crescentemente.
                */
                aux=vetor[i+1];
                vetor[i+1]=vetor[i];
                vetor[i]=aux;
                flag=1;
            }
        }
    }
    
}



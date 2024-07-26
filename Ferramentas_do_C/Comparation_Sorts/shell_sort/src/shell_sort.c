#include "shell_sort.h"

//Funcao de contruir vetor de passos criada para evitar realloc
//obs: alémd de alocar vetor, atribui seus elementos em um for com base em f(n)=3*f(n-1)+1
int* build_steps_array(int size_A, int size_steps){
    int aux=1;

    int *step=(int*)calloc(size_steps,sizeof(int));

    for(int i=0;i<size_steps;i++){
        if(i!=0){
            aux=aux*3+1;
        }
        step[i]=aux;  
    }
    
    return step;
}

void shell_sort(type_data* A, int size){  
    /*Usa-se um while para verificar qual vai ser o tamanho do vetor de passos sendo que
    esse vetor segue a ordem f(n)=3*f(n-1)+1*/
    int last=1,cont=1,i,j;

    while(last<size){
        last=3*last+1;
        cont++;
    
    }
    //Chama funcao que retorna o vetor de passos
    int *step=build_steps_array(size,cont);

    //For para percorre o vetor de passos do maior passo para o menor
    for(cont;cont>=0;cont--){

        //Para cada tamanho (h) de passa é realizada um "insertion sort" levando em conta esse tamanho
        int h=step[cont];

        for(i=h;i<size;i++){
            type_data aux=A[i];

            for(j=i-h;j>=0 && A[j]>aux;j-=h){
                
                A[j+h]=A[j]; // mudança de lugar de elementos para que A[i] ocupe sua posição correta para dado h
            }

            A[j+h]=aux; //Elemento passa a ocupar sua posição correta levanddo em conta um determinado h
        }
    }
}

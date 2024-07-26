#include "merge_sort.h"

/* Usuario insere somente o vetor que quer ordenar e o tamanho dele*/
void merge_sort(type_data *A, int size){
    /*a primeira recursão acontece com a divisão da esquerda 'l' iggual a zero e a
    a da direita 'r' igual ao indice do ultimo elemento
    */
    merge_sort_recursion(A,0,size-1);
}

void merge_sort_recursion(type_data *A, int l, int r){
    /* Só ordena se houver mais de um elemento envolvido na recursão
    obs:condicao para fim da pilha de recursoes*/
    if(l<r){
        /* m recebe o índice do elemento central entre a divisão l e a divisão r
        sendo que l e r indica o índice dos elementos das extremidades esqueda e direita
        respectivamente*/
        int m=l+(r-l)/2;

        //recursoes em si
        merge_sort_recursion(A,l,m);
        merge_sort_recursion(A,m+1,r);

        /* apos voltar da pilha de recursoes ordena elementos de A levando em conta duas arrays
        (dirieta e esqueda)*/
        merge_sort_arrays(A,l,m,r);
    }
}

void merge_sort_arrays(type_data *A, int l, int m, int r){
    
    //tamanho de subvetores da esquerda e direita
    int left_size= m-l+1; //+1 pois tera o elemento 'l'
    int right_size= r-m; // sem +1 pois nao tera elemento m

    /*Copia partes correspondentes do vetor A para os vetores da esqueda e direita 
    que serão usados nas próximas recursões*/
    type_data *left_array=calloc(left_size,sizeof(type_data));
    type_data *right_array=calloc(right_size,sizeof(type_data));

    for(int i=0;i<left_size;i++){
        left_array[i]=A[l+i];
    }
    for(int i=0;i<right_size;i++){
        right_array[i]=A[m+1+i];
    }
    /*ordena os elementos do vetor A, com base em uma comparação entre elementos do vetor da direita 
    e da esqueda*/
    int i=0,j=0,k;

    for(k=l;k<=r;k++){
        /*se o elemento do vetor da esqueda é menor que do da direita, esse elemento vai para A[k] e o indice
        i vai para o proximo elemento do vetor da esquerda.
        obs: isso também ocorre se todos os elementos do vetor da direita ja foram colocados em seus devidos
        lugares do vetor A*/
        if((i<left_size) && (j>=right_size || left_array[i]<=right_array[j])){
            A[k]=left_array[i];
            i++;
        }
        /*se o elemento do vetor da direita é menor que do da esquerda, esse elemento vai para A[k] e o indice
        j vau para o proximo elemento do vetor da direita
        obs: isso também ocorre se todos os elementos do vetor da esquerda ja foram colocados em seus devidos
        lugares do vetor A*/
        else{
            A[k]=right_array[j];
            j++;
        }
    }
    //Desaloca arrays da direita e esqueda pois não serão mais usadas
    free(left_array);
    free(right_array);
    
}

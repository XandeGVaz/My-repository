#include "heap_sort.h"

void change_space(type_data*,int,int);

void heap_sort(type_data *A, int size){
    controy_heap(A,size);//contrui a heap com base em A
    int size_heap=size;//determina o tamanho da heap
    
    while(size_heap>1){
        change_space(A,size_heap-1,0); //troca H[0] pelo ultimo elemento da heap
        size_heap--; //decresce o tamanho da heap em 1
        /* organiza a heap desde o seu primeiro elemento até antes do último nivel, pois esse corresponde
        ao elemento que foi trocado e agora está em sua posição certa*/
        organize_heap(A,0,size_heap);
    }
}

void controy_heap(type_data* A, int size){
    //i começa em (size/2)-1 para que a organização da heap comece do último nó não folha da heap//
    for(int i=(size/2)-1;i>=0;i--){
        organize_heap(A,i,size);
    }
}

void organize_heap(type_data* A, int i, int size){
    //Indices dos filhos da esqueda e direita do elemento i da heap H
    int l=2*i+1, r=2*i+2;
    int ms=0;

    //verifica se esses indices existem e, se sim, serão de fato os indices dos filhos de H[i]
    int ls=(l<size)? l:-1;
    int rs=(r<size)? r:-1;
    
    if(ls==-1) return;

    //acha ms -> o indice do maior filho de H[i]
    ms=(rs==-1 || A[ls]>A[rs])? ls:rs;

    //Verifica se H[i] e maior ou igual a H[ms] e , se nao, os dois são trocados de lugar em H
    if(A[i]>=A[ms]) return;
    else change_space(A,i,ms);

    /* Recusão para fazer o mesmo processo nos nós seguintes, até chegar no ponto em que o elemento
    H[i] esteja no lugar certo */
    organize_heap(A,ms,size);

}

void change_space(type_data*A, int a, int b){
    type_data aux;
    aux=A[b];
    A[b]=A[a];
    A[a]=aux;
}

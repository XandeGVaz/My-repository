#include "knap_sack.h"
#include "merge_sort.h"

////////Definição da structs//////////////////////////////////////////////////////////////////////////
/* --STRUCT DE UM DADO(ITEM)--
Elementos da struct de um dado
    *1: Peso do item
    *2: Valor do item
    *3: Índice (idx) do item no  vetor principal de entrada de todos os itens considerados
*/
typedef struct type_data{
    int weight;
    int val;
    int idx;
}data;

/* --STRUCT LISTA DE DADOS--
Elementos da struct de uma lista de dados
    *1: array de dados
    *2: tamanho da array de dados
*/
typedef struct type_ldata{
    data* arr;
    int len;
}ldata;
//////////////////////////////////////////////////////////////////////////////////////////////////////


/////// Definição de funções principais de resolução do problema da mochila///////////////////////////
ldata* KNPS_dinamic(int P, int Q, ldata* l){
    int s,A,B;
    int memory[Q+1][P+1];

    for(int i=0; i<(Q+1); i++){

        for(int j=0; j<(P+1); j++){
            
            s = j - l->arr[i-1].weight;
            if(i == 0) memory[i][j]=0;
            else if(s < 0) memory[i][j]=memory[i-1][j];
            else if(s >= 0){
                A = (l->arr[i-1].val) + (memory[i-1][s]);
                B = memory[i-1][j];
                memory[i][j]=return_max(A,B);
            }
        }
    }

    int aux[Q];
    int cont=0;
    
    int k=P;
    for(int i=Q; i>0; i--){

        if(memory[i][k]!=memory[i-1][k]){
            aux[i-1]=1;
            k-=l->arr[i-1].weight;
            cont++;
        }

        else aux[i-1]=0;
    }
    
    ldata* itens=create_list(cont);
    for(int i=Q; i>0 && cont>0 ; i--){

        if(aux[i-1]==1){
            itens->arr[cont-1]=l->arr[i-1];
            cont--;
        }
    }
    
    return itens;
}

ldata* KNPS_greedy(int P, int Q, ldata* l){
    
    int rest=P;

    data* order_array =(data*)calloc(Q,sizeof(data));
    for(int i=0;i<Q;i++){
        order_array[i]=l->arr[i];
    }
    
    merge_sort(order_array,Q);
    
    int j=Q-1;
    int cont=0;
    for(j;j>=0;j--){
        rest=rest-order_array[j].weight;
        if(rest>=0){
            cont++;
        }
        else break;
    }
    
    ldata* itens = create_list(cont);
    for(int k=j+1; k<Q; k++){
        itens->arr[k-j-1]=order_array[k];
    }

    return itens;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

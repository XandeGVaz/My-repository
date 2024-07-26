#include "aux.h"

////////Definição da structs/////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////


////////Definição de funções auxiliares////////////////////////////////////////////////////////

//  Função que retorna relação valor-peso de um dado
float return_rel(data D){
     return (PRECISION*D.val/D.weight);
}

/*
Função que retorna se um dado A é maior(1), igual(0) ou menor(-1) que um dado B
    *   Primeiro lugar: Relação entre valor e peso do item (com precisão de duas casas decimais após a vírgula).
    *   Segundo lugar: Item de menor peso caso tenham o mesmo valor de relação.
*/
int bigger_than(data A, data B){
    int relA, relB;
    relA=(int)(return_rel(A));
    relB=(int)(return_rel(B));
    if(relA!=relB){
        if(relA>relB) return 1;
        else return 0;
    }
    else{
        if(A.weight<B.weight) return 1;
        else return 0;
    }
}

//  Função que cria lista de itens
ldata* create_list(int Q){
    ldata* l=calloc(1,sizeof(ldata));
    l->arr=(data*)calloc(Q,sizeof(data));
    l->len=Q;
}

//  Função usado para que a entrada em uma lista l de uma quantidade Q de itens informados pelo usuário
void inptdata_list(ldata* l, int Q){
    int  weight,val;
    for(int i=0; i<Q; i++){
        scanf("%d %d",&weight,&val);
        l->arr[i].idx=i;
        l->arr[i].weight=weight;
        l->arr[i].val=val;
    }
}

//  Função usada para imprimir os índices (idx) dos dados de uma array crescentemente (0,1,2,..,len-1)
void printdata_list(ldata* l){
    for(int i=0; i<l->len-1; i++){
        printf("%d ",l->arr[i].idx);
    }
    printf("%d\n",l->arr[l->len-1].idx);
}

//  Função usada para imprimir os índices (idx) dos dados de uma array decrescentemente (len-1,len-2,...,0)
void invprintdata_list(ldata* l){
    for(int i=l->len-1; i>0; i--){
        printf("%d ",l->arr[i].idx);
    }
    printf("%d\n",l->arr[0].idx);
}

//  Função que retorna o valor total dos itens presente em uma array de dados
int totalval_list(ldata* l){
    int valt=0;
    for(int i=0; i<l->len; i++){
        valt+=l->arr[i].val;
    }
    return valt;
}

//  FUnção que retorna o valor máximo entre dois inteiros
int return_max(int A, int B){
    return (A>=B)? A:B;
}
///////////////////////////////////////////////////////////////////////////////////////////////
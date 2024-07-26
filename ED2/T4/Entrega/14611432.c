/* --TRABALHO 4 ESTRUTURA DE DADOS 2--
Dados do autor:
    *Aluno: Vitor Alexandre Garcia Vaz
    *No USP: 14611432
Data:   30/06/2024
*/

//////// Includes////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////// Defines//////////////////////////////////////////////////////////////////////////////////////
#define PRECISION 100 //precisão de comparação de floats
//////////////////////////////////////////////////////////////////////////////////////////////////////


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


/////// Declaração de funções auxiliares//////////////////////////////////////////////////////////////
float return_rel(data D);
int bigger_than(data A, data B);
ldata* create_list(int Q);
void inptdata_list(ldata* l);
void printdata_list(ldata* l);
void invprintdata_list(ldata* l);
int totalval_list(ldata* l);
int return_max(int A, int B);
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////// Declaração de funções do merge sort//////////////////////////////////////////////////////////
void merge_sort(data *A, int size);
void merge_sort_recursion(data *A, int l, int r);
void merge_sort_arrays(data *A, int l, int m, int r);
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////// Declaração de funções principais de resolução do problema da mochila/////////////////////////
/*
Entradas
    *   P: peso total suportado pela mochila
    *   Q: quantidade de itens que serão informados na array
    *   l: ponteiro para tipo lista com o vetor de dados e número total de itens nesse vetor
Saida
    *   Vetor de dados (itens) que correspondem ao valor máximo que pode ser levado na mochila
    *   ->Algoritmo dinâmico: itens em ordem crescente de índice (0,1,2,...,n-1)
    *   ->Algoritmo guloso: itens em ordem crescente de relação valor peso
*/
ldata* KNPS_dinamic(int P, int Q, ldata* l); //versão que usa programação dinâmica para a resolução do problema da mochila
ldata* KNPS_greedy(int P, int Q, ldata* l); //versão que usa algoritmo guloso para a resolução do problema da mochila
//////////////////////////////////////////////////////////////////////////////////////////////////////


///////// Execução em si do programa//////////////////////////////////////////////////////////////////
int main(){

    int P,Q;
    int d_valt,g_valt;

    ldata* l=NULL;
    ldata* ld=NULL;
    ldata* lg=NULL;

    scanf("%d %d",&P,&Q);

    l=create_list(Q);
    inptdata_list(l);

    ld=KNPS_dinamic(P,Q,l);
    lg=KNPS_greedy(P,Q,l);
    printdata_list(ld);
    invprintdata_list(lg);

    d_valt=totalval_list(ld);
    g_valt=totalval_list(lg);
    printf("%d %d\n",d_valt,g_valt);
    printf("%.2f\n",(float)100*g_valt/d_valt);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////


////////Definição de funções auxiliares///////////////////////////////////////////////////////////////
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

//  Função que cria lista de itens e retorna ponteiro para essa lista
ldata* create_list(int Q){
    ldata* l=calloc(1,sizeof(ldata));
    l->arr=(data*)calloc(Q,sizeof(data));
    l->len=Q;
    return l;
}

//  Função usado para que a entrada em uma lista l de uma quantidade l->len de itens informados pelo usuário
void inptdata_list(ldata* l){
    for(int i=0; i<l->len; i++){
        scanf("%d %d",&(l->arr[i].weight),&(l->arr[i].val));
        l->arr[i].idx=i;
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

//  Função que retorna o valor máximo entre dois inteiros
int return_max(int A, int B){
    return (A>=B)? A:B;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////


/////// Definição de funções do merge sort////////////////////////////////////////////////////////////
/* Usuario insere somente o vetor que quer ordenar e o tamanho dele*/
void merge_sort(data *A, int size){
    /*a primeira recursão acontece com a divisão da esquerda 'l' iggual a zero e a
    a da direita 'r' igual ao indice do ultimo elemento
    */
    merge_sort_recursion(A,0,size-1);
}

void merge_sort_recursion(data *A, int l, int r){
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

void merge_sort_arrays(data *A, int l, int m, int r){
    
    //tamanho de subvetores da esquerda e direita
    int left_size= m-l+1; //+1 pois tera o elemento 'l'
    int right_size= r-m; // sem +1 pois nao tera elemento m

    /*Copia partes correspondentes do vetor A para os vetores da esqueda e direita 
    que serão usados nas próximas recursões*/
    data *left_array=calloc(left_size,sizeof(data));
    data *right_array=calloc(right_size,sizeof(data));

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
        if((i<left_size) && (j>=right_size || bigger_than(left_array[i],right_array[j])==0)){
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
//////////////////////////////////////////////////////////////////////////////////////////////////////

/////// Definição de funções principais de resolução do problema da mochila///////////////////////////
// Função de programação dinâmica para resolução do problema da mochila (entrega solução ótima).
ldata* KNPS_dinamic(int P, int Q, ldata* l){
    int s,A,B;
    int memory[Q+1][P+1]; //matriz de memória cujas colunas correspondem aos possíveis pesos restantes e as linhas correspondem aos itens (obs uma linha a mais "memory[0]" na qual todos os elementos devem ser zero para que o problema possa ser resolvido)

    for(int i=0; i<(Q+1); i++){

        for(int j=0; j<(P+1); j++){
            
            s = j - l->arr[i-1].weight; //subtração: coluna(peso restante) - peso do item relacionado à linha atual
            if(i == 0) memory[i][j]=0;
            else if(s < 0) memory[i][j]=memory[i-1][j];
            else if(s >= 0){
                A = (l->arr[i-1].val) + (memory[i-1][s]);
                B = memory[i-1][j];
                memory[i][j]=return_max(A,B); //atualiza valor total somente se for maior que o correspondente na linha anterior
            }
        }
    }

    int aux[Q]; //vetor auxiliar usado para idicar se um item faz parte da melhor resposta (1->faz parte | 0->não faz parte)

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
    //cont corresponerá ao número e itens da melhor resposta
    ldata* itens=create_list(cont);
    for(int i=Q; i>0 && cont>0 ; i--){

        if(aux[i-1]==1){
            itens->arr[cont-1]=l->arr[i-1];
            cont--;
        }
    }
    
    return itens;
}

// Função de algoritmo guloso para resolução do problema da mochila (não garante resposta ótima mas prioriza elementos que tenham maior relação valor/peso)
ldata* KNPS_greedy(int P, int Q, ldata* l){
    
    int rest=P; // Peso disponível restante após saber que um dado elemento seria colocado na mochila

    data* order_array =(data*)calloc(Q,sizeof(data));
    for(int i=0;i<Q;i++){
        order_array[i]=l->arr[i];
    }
    
    merge_sort(order_array,Q); // Uso do merge-sort para ordenar crescentemente array de itens (sendo a relação valor/peso o parâmetro de ordenaçãom principal) -> mais detalhes na explicação da função bigger_than que é usada na ordenação.
    
    int j=Q-1;
    int cont=0;
    for(j;j>=0;j--){
        rest=rest-order_array[j].weight;
        if(rest>=0){
            cont++;
        }
        else break;
    }
    // cont será o número de itens da resposta
    ldata* itens = create_list(cont);
    for(int k=j+1; k<Q; k++){
        itens->arr[k-j-1]=order_array[k];
    }

    free(order_array);

    return itens;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
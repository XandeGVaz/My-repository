/*
    Aluno: Vitor Alexandre Garcia Vaz
    N USP: 14611432
    Turma: Engenharia de Computação
*/

//////////////// Includes necessários ///////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
////////////////////////////////////////////////////////////////////////////


/////////////// Struct de dados /////////////////////////////////////////////
typedef struct type_data {
    char nome[10]; //nome do aluno
    float nota; //nota ponderada
    int reprov; //reprovações
}data;
////////////////////////////////////////////////////////////////////////////


//////////////// Definição funções auxiliares //////////////////////////////
bool left_smaller_than(const data* A1, const data*A2, int a, int b);
data* make_data_array(int size);
void print_data_array(const data* A,int size);
void change_space(data* A, int a, int b);
data* return_invert_array(const data* A, int size, int size_invert);
int return_aprov(const data* A, int N, int M);
data* return_valid_array(const data* A, int size);
int len_valid_array(const data* A, int size);
////////////////////////////////////////////////////////////////////////////


//////////////// Definição função de uso do selection-sort /////////////////
void selection_sort(data *A, int size);
////////////////////////////////////////////////////////////////////////////


//////////////// Definição da funções de uso do merge-sort /////////////////
void merge_sort(data *A, int size);
void merge_sort_recursion(data *A, int l, int r);
void merge_sort_arrays(data *A, int l, int m, int r);
////////////////////////////////////////////////////////////////////////////


/////////////// Execução principal do programa //////////////////////////////////////////////////////////////
int main(){

    //Variáveis inteiras que serão indicadas pelo scanf
    int T,N,M;

    //Ponteiros de dados para formação de arrays de dados necessárias
    data *L=NULL,*A=NULL, *C=NULL;

    //Entrada do tipo de método de organização usado
    scanf("%d",&T);

    //Entrada dos parâmetros de seleção de alunos (quantidade de inscritos e de vagas)
    scanf("%d %d",&N,&M);

    if(T==1){
        //Forma array de possíveis candidatos
        L=make_data_array(N);
        //Assim forma uma array de candidatos, somente com os candidatos válidos (com 10 ou menos reprovações)
        C=return_valid_array(L,N);
        int Nc=len_valid_array(L,N);
        //Ordena a array de candidatos com selection sort
        selection_sort(C,Nc);
        int aprov=return_aprov(C,Nc,M);
        //Forma uma array de candidatos aprovados
        A = return_invert_array(C, Nc, aprov);
        printf("%d\n", aprov);
        print_data_array(A, aprov);

       
    }
    if(T==2){
        //Forma array de possíveis candidatos
        L=make_data_array(N);
        //Assim forma uma array de candidatos, somente com os candidatos válidos (com 10 ou menos reprovações)
        C=return_valid_array(L,N);
        int Nc=len_valid_array(L,N);
        //Ordena a array de candidatos com merge sort
        merge_sort(C,Nc);
        int aprov=return_aprov(C,Nc,M);
        //Forma uma array de candidatos aprovados
        A = return_invert_array(C, Nc, aprov);
        printf("%d\n", aprov);
        print_data_array(A, aprov);
    }
    return 0;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 




//////////////// Funções auxiliares ////////////////////////////////////////////////////////////

/*Função auxiliar que verifica se o dado da esquerda (de uma dada array passada por parâmetro) 
tem menos prioridade (é menor) que o da direita (de outra ou da mesma array). Para isso,
compara-se (em ordem de prioridade):
-No primeiro nível de if-else: as notas ponderadas (menor nota ->menos prioridade)
-No Segundo nível: o número de reprovações (mais reprovações -> menos prioridade)
-No terceiro nível: a ordem alfabética dos nomes
Possibilidades:
    um ->dado da esquerda menor que o direito
    zero ->dado da direita menor ou igual que o esquerdo
*/
bool left_smaller_than(const data* A1, const data*A2, int a, int b){
    bool B;

    int na=A1[a].nota*1000;
    int nb=A2[b].nota*1000;

    if(na<nb) B=1;

    else if(na==nb){
        
        if(A1[a].reprov>A2[b].reprov) B=1;
        
        else if(A1[a].reprov==A2[b].reprov){
            B=(strcmp(A1[a].nome,A2[b].nome)>0);
        }
        else B=0;
    }
    
    else B=0;
    
    return B;
}

/*Função que faz a array de datas com base em entradas do usuário e o tamanho de vetor
passado como parâmetro, sendo que a ordem de entrada é "nota->reprovacoes->nome" */
data* make_data_array(int size){
    data* A=calloc(size,sizeof(data));
    for(int i=0;i<size;i++){
        fflush(stdin);
        scanf("%f %d %s",&A[i].nota,&A[i].reprov,A[i].nome);
    }
    return A;
}

//Função que imprime array de traz para frente (do indice size-1 ate 0)
void print_data_array(const data* A,int size){
    for(int i=0;i<size;i++){
        printf("%s\n",A[i].nome);
    }
}


//Função auxiliar que troca dois elementos da lista/vetor de lugar 
void change_space(data* A, int a, int b){
    data aux;
    aux=A[b];
    A[b]=A[a];
    A[a]=aux;
}

/*Função responsável por retornar uma array de dados com ordem inversa em relação à
array passada por parâmetro*/
data* return_invert_array(const data* A, int size, int size_invert){

    data* invert=calloc(size_invert,(sizeof(data)));
    int j=size-1;
    for(int i=0;i<size_invert;i++){
        invert[i]=A[j];
        j--;
    }
    return invert;
}

/*Função que retorna o número de alunos aprovados, levando em conta que:
1- Se N<=M há mais bolsas (ou a mesma quantidade) que candidatos. Logo todos estão aprovados 
(aprov=N)
2- Caso contrário:
    2.a- Número de aprovados é igual a M (número de bolsas) e não tem candidatos que possuem
    a mesma nota ponderada e número de reprovações entre o final da lista de aprovados e o final
    da lista de candidatos ordenada
    2.b- A condição anterior não é satisfeita, assim será necessário criar um for para contar a
    quantidade de candidatos ue possuem a mesma nota ponderada e número de reprovações entre o 
    final da lista de aprovados e o final da lista de candidatos ordenada*/
int return_aprov(const data* A, int N, int M){
    int aprov=(N <= M) ? N:M;
    /*Começa em N-M para corresponder ao último elemento que entraria caso o número de aprovados
    fosse M */
    for(int i=N-M;i>=0;i--){
        //Se A[i] e A[i-1] tiverem em mesmas notas e numero de reprovações, aprov aumenta em 1
        if( A[i].nota*1000 == A[i-1].nota*1000 && A[i].reprov==A[i-1].reprov ) aprov++;
        else break; //Break para sair do laço caso não haja mais elementos iguais a A[N-M]
    }
    return aprov;
}

//Função que retorna somente os dados válidos de uma array com base nos critérios fornecidos
data* return_valid_array(const data* A, int size){
    int cont=0;
    int i=0;
    data* valid;
    //Conta a quantidade de elementos válidos em A(que tem 10 ou menos reprovações)
    while(i<size){
        if(A[i].reprov<=10) cont++;
        i++;
    }
    //Cria um veto com a mesma quantidade de elementos válidos
    valid=(data*)calloc(cont,sizeof(data));
    //Adiciona somente os elementos válidos nesse vetor
    i=0;
    for(int j=0;j<cont;j++){
        if(A[i].reprov<=10) valid[j]=A[i];
        else j--;
        i++;
    }
    return valid;
}
//Função que retorna o tamanho da array válida com base em parâmetros da array não válida de origem
int len_valid_array(const data* A, int size){
    int cont=0;
    int i=0;
    data* valid;
    //Conta a quantidade de elementos válidos em A(que tem 10 ou menos reprovações)
    while(i<size){
        if(A[i].reprov<=10) cont++;
        i++;
    }
    return cont;
}
////////////////////////////////////////////////////////////////////////////////////////////////




//////////////// Função de uso do selection-sort ////////////////////////////////////////////////////
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




//////////////// Funções do merge-sort ////////////////////////////////////////////////////////////////////////
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
    
    //Tamanho de subvetores da esquerda e direita
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
    /*Ordena os elementos do vetor A, com base em uma comparação entre elementos do vetor da direita 
    e da esqueda*/
    int i=0,j=0,k;

    for(k=l;k<=r;k++){
        /*Se o elemento do vetor da esqueda é menor (tem menos prioridade) que o da direita, esse elemento 
        vai para A[k] e o indice i vai para o proximo elemento do vetor da esquerda.
        obs: isso também ocorre se todos os elementos do vetor da direita ja foram colocados em seus devidos
        lugares do vetor A*/
        if((i<left_size) && (j>=right_size || left_smaller_than(left_array,right_array,i,j))){
            A[k]=left_array[i];
            i++;
        }
        /*Se o elemento do vetor da direita é menor (tem menos prioridade) que o da esquerda, esse elemento vai para 
        A[k] e o indice j vai para o proximo elemento do vetor da direita.
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
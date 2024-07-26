#include "aux_functions.h"

///////////////Struct de dados/////////////////////////////////////////////////////////////

typedef struct type_data {
    char nome[10]; //nome do aluno
    float nota; //nota ponderada
    int reprov; //reprovações
}data;

/////////////////////////////////////////////////////////////////////////////////////////////////

////////////////Funções auxiliares/////////////////////////////////////////////////////////////

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


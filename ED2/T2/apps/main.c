
#include "selection_sort.h"
#include "merge_sort.h"
#include "aux_functions.h"

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
#include "AVL.h"
#include "ABB.h"
#include <ctype.h>

void separation_text(char* txt, int* cmd, char* tag){
    int i=2;
    *cmd=atoi(&txt[0]);
    while(i<11 && txt[i]!='\n' && txt[i]!='\r'){
        tag[i-2]=txt[i];
        i++;
    }
    tag[i-2]='\0';
}

int main(){
    ABB_node* ABB_raiz=NULL;
    ABB_node* ABB_node=NULL;
    AVL_node* AVL_raiz=NULL;
    AVL_node* AVL_node=NULL;
    //Variaveis de entrada
    int comando;
    char string[10];
    char text[12];
    //Variaveis de leitura do arquivo
    char TAG[10]; 
    char aux[100];
    int status;

    FILE* arq=fopen("./file/arq.txt", "rt");
    if(arq==NULL){
        printf("\tARQUIVO NAO ENCONTRADO!\n");
    }
    for(;;){
        fscanf(arq,"%s",TAG);
        if(TAG[0]=='x' && TAG[1]=='\0') break;
        fscanf(arq,"%d",&status);
        ABB_add_node_v3(&ABB_raiz,ABB_define_data(TAG,status));
        AVL_raiz=AVL_add_node_v1(AVL_raiz,AVL_define_data(TAG,status));
    }
    fclose(arq);
    
    fflush(stdin);
    fgets(text,12,stdin);
   
    separation_text(text,&comando,string);
    
    if(comando==0){
        printf("NA:%d NB:%d\n",ABB_number_nodes(ABB_raiz),AVL_number_nodes(AVL_raiz));
    }
    if(comando==1){
        //obs: o 0 não importa na busca, mas somente a string que serve para procurar a TAG correspondente
        ABB_node=ABB_search_node_v2(ABB_raiz,ABB_define_data(string,0));
        AVL_node=AVL_search_node_v1(AVL_raiz,AVL_define_data(string,0)); 
        if(ABB_node!=NULL && AVL_node!=NULL){
            printf("S:%d NA:%d NB:%d\n",ABB_return_status(ABB_node), ABB_nodes_read_until( ABB_raiz, ABB_define_data(string,100) ), AVL_nodes_read_until( AVL_raiz, AVL_define_data(string,100)));
        }
        else{
            printf("S:-1 NA:%d NB:%d\n",ABB_nodes_read_until( ABB_raiz, ABB_define_data(string,100) ), AVL_nodes_read_until( AVL_raiz, AVL_define_data(string,100)));
        }
    }
    if(comando==2){
        ABB_print_notorder(ABB_raiz);
    }
    if(comando==3){
        AVL_print_notorder(AVL_raiz);
    }
    return 0;
}
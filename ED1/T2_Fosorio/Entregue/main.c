#include "list.h"
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
    List* L=List_create();
    list_node* node_list=NULL;;
    tree_node* raiz=NULL;
    tree_node* node_tree=NULL;;
    //Variaveis de entrada
    int comando;
    char string[10];
    char text[12];
    //Variaveis de leitura do arquivo
    char TAG[10]; 
    char aux[100];
    int status;

    FILE* arq=fopen("arq.txt", "rt");
    if(arq==NULL){
        printf("\tARQUIVO NAO ENCONTRADO!\n");
    }
    for(;;){
        fscanf(arq,"%s",TAG);
        if(TAG[0]=='x' && TAG[1]=='\0') break;
        fscanf(arq,"%d",&status);
        List_add_wage(L,define_data_list(TAG,status));
        add_node_v3(&raiz,define_data_tree(TAG,status));
    }
    fclose(arq);
    
    fflush(stdin);
    fgets(text,12,stdin);
   
    separation_text(text,&comando,string);
    
    if(comando==0){
        printf("NL:%d NA:%d\n",List_size(L),number_nodes(raiz));
    }
    if(comando==1){
        node_list=Search_orderlistnode(L,define_data_list(string,0));      //obs: o 0 não importa na busca!
        node_tree=search_node_v2(raiz,define_data_tree(string,0));    // mas somente a string que serve para procurar a TAG correspondente
        if(node_list!=NULL && node_tree!=NULL){
            printf("S:%d NL:%d NA:%d\n",return_status_tree(node_tree), Listnodes_read_ultil( L, define_data_list(string,100) ) , nodes_read_until( raiz, define_data_tree(string,100) ) );
        }
        else{
            printf("S:-1 NL:%d NA:%d\n",Listnodes_read_ultil( L, define_data_list(string,100) ) , nodes_read_until( raiz, define_data_tree(string,100) ) );
        }
    }
    if(comando==2){
        List_print(L);
    }
    if(comando==3){
        print_notorder(raiz);
    }
    return 0;
}
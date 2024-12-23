//Aluno:Vitor Alexandre Garcia Vaz//
//Nº USP:14611432//

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void separation_comands(char *w,char *c,char *str){
    *c=str[0];
    int i=2;
    for(i;i<12 && str[i]!='\n' && str[i]!='\r';i++){
        w[i-2]=str[i];
    }
    w[i-2]='\0';
}


int main()
{
    char ent[12]; //entrada de texto de cada linha
    char C; //variável  caractere usada  para o comando
    char wrd[10]; //variável string usada para a palavra escrita

    Node *G=NULL; //ponteiro correspondente  ao cursor
    List *L=List_create(); //ponteiro para a lista

    int flag=1;  //flag para o continuamento/término do programa

    while(flag){
        fgets(ent,12,stdin);
        separation_comands(wrd,&C,ent);
        if(C=='I'){
            List_add_first(L,wrd);
            if(List_print_size(L)==1){
                G=cursor_for_begin(L);
            }
        }
        if(C=='F'){
            List_add_last(L,wrd);
            G=cursor_for_end(L);
        }
        if(C=='A'){
            List_add_before_cursor(L,G,wrd);
            G=cursor_for_prevnode(G);
        }
        if(C=='D'){
            List_add_after_cursor(L,G,wrd);
            G=cursor_for_nextnode(G);
        }
        if(C=='P'){
            G=cursor_for_word(G,wrd);
        }
        if(C=='R'){
            if(identical_strings(wrd,"atual")){
                cursor_remove_word(L,G);
            }
        }
        if(C=='G'){
            if(identical_strings(wrd,"inicio")){
                G=cursor_for_begin(L);
            }
            if(identical_strings(wrd,"fim")){
                G=cursor_for_end(L);
            }
            if(identical_strings(wrd,"prox")){
                G=cursor_for_nextnode(G);
            }
            if(identical_strings(wrd,"ant")){
                G=cursor_for_prevnode(G);
            }
        }
        if(C=='L'){
            if(identical_strings(wrd,"texto")){
                List_print(L);
            }
            if(identical_strings(wrd,"palavra")){
                cursor_print_node(G);
            }
       }
        if(C=='X'){
            if(identical_strings(wrd,"editor")) flag=0;
        }

    }
}

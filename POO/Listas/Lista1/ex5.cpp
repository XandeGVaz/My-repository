/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>

#define MAX 1000000
typedef struct{
    int* list;
    int qnt;  //quantidade de elementos da lista
}lista;

int atualiza_lista(lista * l, int num){                    // adiciona um elemento na lista e marca elementos repetidos
    int i=0, r=0, flag=1;
    int qnt = l->qnt;

    if(qnt < MAX){

        while( i < qnt ){

            if(l->list[i] == num){                          // se elemento é igual ao que pode ser adicionado, exclui
                l->list[i] = -1;
                flag = 0;
            }

            if(l->list[i] != -1){                           // retorno recebe elemento único
                r=l->list[i];
            }

            i++;
        }

        if(flag){                                           // se não é repetido, adiciona na lista
            l->list[qnt]=num;                              
            l->qnt++;
            r = num;                                        // elemento único é igual ao elemento adicionado
        }
    }

    return r ;
}

int main(){
    int i=0, r=0;
    int aux;

    lista*l=(lista*)calloc(1,sizeof(lista));
    l->qnt = 0;
    l->list =(int*) malloc(sizeof(int)*MAX);

    while(i<MAX){                                           // define -2 como valor de espaços ainda não integrantes da lista
        l->list[i]=-2;
        i++;
    }
    
    i=0;

    while(scanf("%d",&aux)!=EOF && i < MAX){
        r = atualiza_lista(l, aux);
        i++;
    }
   
    printf("%d",r);                              // imprime valor não repetido

    free(l->list);
    free(l);

    return 0;

}
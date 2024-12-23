#include "ABB.h"

int menu(){
    int comando;
    printf("\tMenu selecao ABB\n1-Adicionar dado\n2-Buscar dado\n3-Imprimir arvore ordenada\n4-Imprimir arvore nao ordenada\n5-Altura arvore\n6-Numero de nos\n7-Numero de folhas\n8-Remover elemento\n");
    printf("\tComando:"); scanf("%d",&comando);
    return comando;
}

int main(){
    int flag=1;
    int comando;
    tree_node*raiz=NULL;
    while(flag){
        comando=menu();
        switch(comando){
            case 1:
                raiz=add_node_v1(raiz,define_data());
                break;
            case 2:
                tree_node*node=NULL;
                node=search_node_v1(raiz,define_data());
                if(node==NULL)
                    printf("Valor nao encontrado!\n");
                else
                    printf("Valor %d encontrado\n",return_node_valor(node));
                break;
            
            case 3:
                print_order(raiz);
                printf("\n");
                break;
            
            case 4:
                print_notorder(raiz);
                printf("\n");
                break;

            case 5:
                printf("\tAltura:%d\n",height_tree(raiz));
                break;
            case 6:
                printf("\tNodos:%d\n",number_nodes(raiz));
                break;
            case 7:
                printf("\tFolhas:%d\n",number_sheets(raiz));
                break;
            case 8:
                raiz=remotion_node(raiz,define_data());
                break;
        }
    }
    return 0;
}

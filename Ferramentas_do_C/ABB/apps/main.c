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
    ABB_node*raiz=NULL;
    while(flag){
        comando=menu();
        switch(comando){
            case 1:
                raiz=ABB_add_node_v1(raiz,ABB_define_data());
                break;
            case 2:
                ABB_node*node=NULL;
                node=ABB_search_node_v2(raiz,ABB_define_data());
                if(node==NULL)
                    printf("Valor nao encontrado!\n");
                else
                    printf("Valor %d encontrado\n",ABB_return_node_valor(node));
                break;
            
            case 3:
                ABB_print_order(raiz);
                printf("\n");
                break;
            
            case 4:
                ABB_print_notorder(raiz);
                printf("\n");
                break;

            case 5:
                printf("\tAltura:%d\n",ABB_height_tree(raiz));
                break;
            case 6:
                printf("\tNodos:%d\n",ABB_number_nodes(raiz));
                break;
            case 7:
                printf("\tFolhas:%d\n",ABB_number_sheets(raiz));
                break;
            case 8:
                raiz=ABB_remotion_node(raiz,ABB_define_data());
                break;
        }
    }
    return 0;
}

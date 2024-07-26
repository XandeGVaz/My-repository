#include "AVL.h"

int menu(){
    int comando;
    printf("\tMenu selecao AVL\n1-Adicionar dado\n2-Buscar dado\n3-Imprimir arvore ordenada\n4-Imprimir arvore nao ordenada\n5-Imprimir formato AVL\n6-Altura arvore\n7-Numero de nos\n8-Numero de folhas\n9-Remover elemento\n");
    printf("\tComando:"); scanf("%d",&comando);
    return comando;
}

int main(){
    int flag=1;
    int comando;
    AVL_node*raiz=NULL;
    while(flag){
        comando=menu();
        switch(comando){
            case 1:
                raiz=AVL_add_node_v1(raiz,AVL_define_data());
                break;
            case 2:
                AVL_node*node=NULL;
                node=AVL_search_node_v1(raiz,AVL_define_data());
                if(node==NULL)
                    printf("Valor nao encontrado!\n");
                else
                    printf("Valor %d encontrado\n",AVL_return_node_valor(node));
                break;
            
            case 3:
                AVL_print_order(raiz,0);
                printf("\n");
                break;
            
            case 4:
                AVL_print_notorder(raiz);
                printf("\n");
                break;

            case 5 :
                AVL_print(raiz,0);
                printf("\n");
                break;
            case 6:
                printf("\tAltura:%d\n",AVL_height_tree(raiz));
                break;
            case 7:
                printf("\tNodos:%d\n",AVL_number_nodes(raiz));
                break;
            case 8:
                printf("\tFolhas:%d\n",AVL_number_sheets(raiz));
                break;
            
            case 9:
                raiz=AVL_remotion_node(raiz,AVL_define_data());
                break;
        }
    }
    return 0;
}

#include "estatic_hash.h"


int menu(){
    int comando;
    printf("\n\t****Menu da tabela hash****\n1-Adicionar dado\n2-Remover dado\n3-Buscar dado\n4-Retornar quantas vezes um dado foia adicionado\n5-Imprimir dados\n6-Sair\n\tComando:");
    scanf("%d",&comando);
    return comando;
}

int main(){
    int len;
    int comando;
    t_key key;
    int pos;
    printf("Digite o número da tabela hash a ser criada:"); scanf("%d",&len);
    thash* hash=make_thash(len);
    while(1){
        comando=menu();
        switch(comando){
            case 1:
                printf("\n\tdado:");scanf("%d",&key);
                pos=add_thash_data(hash,key);
                break;

            case 2:
                printf("\n\tdado:");scanf("%d",&key);
                pos=remotion_thash_data(hash,key);
                break;

            case 3:
                printf("\n\tdado:");scanf("%d",&key);
                pos=search_thash_data(hash,key);
                if(pos!=-1){
                    printf("\n Chave %d encontrada na posicao%d",key,pos);
                }
                else  printf("\nChave %d não encontrada",key);
                break;

            case 4:
                printf("\n\tdado:");scanf("%d",&key);
                pos=search_thash_data(hash,key);
                if(pos!=-1){
                    printf("\n Chave %d adicionado %d vezes",key,return_data_added(hash,pos));
                }
                else  printf("\nChave %d não encontrada",key);
                break;

            case 5:
                print_thash_datas(hash);
                break;

            case 6:
                return 0;   
        }
    } 
}
#include "ABB.h"
#include <stdbool.h>

//Structs///////////////////////////////////////////////////////////////////////
typedef struct Data{
    int val;
}ABB_data;

typedef struct Node{
    ABB_data *dt;
    ABB_node* left;
    ABB_node* right;
}ABB_node;


//Intermediary functios//////////////////////////////////////////////////////////
bool node_is_empty(ABB_node* raiz){
    bool b;
    b=(raiz==NULL);
    return b;
}

//Definition of fundamental functions ////////////////////////////////////////////
ABB_data* ABB_define_data(){
    ABB_data* d=calloc(1,sizeof(ABB_data));
    printf("\tDigite o valor do dado:"); 
    scanf("%d",&d->val);
    return d;
}

ABB_node* ABB_create_node(ABB_data* d){
    ABB_node* node=calloc(1,sizeof(ABB_node));
    node->dt=d;
    return node;
}

int ABB_return_node_valor(ABB_node* node){
    return node->dt->val;
}

ABB_node* ABB_add_node_v1(ABB_node* raiz, ABB_data* d){
    if(node_is_empty(raiz)){
        ABB_node* aux=ABB_create_node(d);
        aux->dt=d;
        aux->left=NULL;
        aux->right=NULL;
        return aux;
    }
    else{
        if(d->val < raiz->dt->val){
            raiz->left=ABB_add_node_v1(raiz->left,d);
        }
        else{
            raiz->right=ABB_add_node_v1(raiz->right,d);
        }
        return raiz;
    }
}

void ABB_add_node_v2(ABB_node**raiz, ABB_data* d){
    if(node_is_empty(*raiz)){
        *raiz=calloc(1,sizeof(ABB_node));
        (*raiz)->dt=d;
        (*raiz)->left=NULL;
        (*raiz)->right=NULL;
    }
    else{
        if(d->val < (*raiz)->dt->val){
            ABB_add_node_v2(&(*raiz)->left,d);
        }
        if(d->val > (*raiz)->dt->val){
            ABB_add_node_v2(&(*raiz)->right,d);
        }
    }
}

void ABB_add_node_v3(ABB_node**raiz, ABB_data* d){
    ABB_node*aux=*raiz;
    while(!node_is_empty(aux)){
        if(d->val < aux->dt->val){
            raiz=&aux->left;
        }
        else{
            raiz=&aux->right;
        }
        aux=*raiz;
    }
    aux=calloc(1,sizeof(ABB_node));
    aux->dt->val=d->val;
    aux->left=NULL;
    aux->right=NULL;
    *raiz=aux;
}

void ABB_print_notorder(ABB_node* raiz){
    if(!node_is_empty(raiz)){
        printf("%d ",raiz->dt->val);
        ABB_print_notorder(raiz->left);
        ABB_print_notorder(raiz->right);
    }
}

void ABB_print_order(ABB_node* raiz){
    if(!node_is_empty(raiz)){
        ABB_print_order(raiz->left);
        printf("%d ",raiz->dt->val);
        ABB_print_order(raiz->right);
    }
}

ABB_node* ABB_search_node_v1(ABB_node*raiz,ABB_data*d){
    if(!node_is_empty(raiz)){
        if(raiz->dt->val==d->val){
            return raiz;
        }
        else if(d->val < raiz->dt->val){
            return ABB_search_node_v1(raiz->left,d);
        }
        else{
            return ABB_search_node_v1(raiz->right,d);
        }
    }
    return NULL;
}

ABB_node* ABB_search_node_v2(ABB_node*raiz,ABB_data*d){
    printf("\n%d nodos lidos\n",ABB_nodes_read_until(raiz,d->val));
    while(!node_is_empty(raiz)){
        if(d->val < raiz->dt->val){
            raiz=raiz->left;
        }
        else if(d->val > raiz->dt->val){
            raiz=raiz->right;
        }
        else return raiz;
    }
    return NULL;
}

int ABB_nodes_read_until(ABB_node*raiz, int val){
    int cont=0;
    while(!node_is_empty(raiz)){
        if(val<raiz->dt->val){
            raiz=raiz->left;
            cont++;
        }
        else if(val>raiz->dt->val){
            raiz=raiz->right;
            cont++;
        }
        else{
            cont++;
            break;
        }
    }
    return cont;
}

int ABB_height_tree(ABB_node*raiz){
    if(node_is_empty(raiz)){
        return -1;
    }
    else{
        int left = ABB_height_tree(raiz->left);
        int right = ABB_height_tree(raiz->right);
        if(left>right){
            return(left+1);
        }
        else{
            return(right+1);
        }
    }
}

int ABB_number_nodes(ABB_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else{
        return(1+ABB_number_nodes(raiz->left)+ABB_number_nodes(raiz->right));
    }
}

int ABB_number_sheets(ABB_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else if(node_is_empty(raiz->left) && node_is_empty(raiz->right)){
        return 1;
    }
    else{
        return(ABB_number_sheets(raiz->left)+ABB_number_sheets(raiz->right));
    }
}

ABB_node* ABB_remotion_node(ABB_node* raiz,ABB_data*d){
    if(node_is_empty(raiz)){
        printf("Valor não encontrado\n");
        return NULL;
    }
    else{
        if(raiz->dt->val==d->val){
            if( node_is_empty(raiz->left) && node_is_empty(raiz->right)){
                free(raiz);
                return NULL;
            }
            else{
                if((!node_is_empty(raiz)) && (!node_is_empty(raiz))){
                    ABB_node*aux=raiz->left;
                    while(!node_is_empty(aux->right)){
                        aux=aux->right;
                    }
                    ABB_data* data_aux=raiz->dt;
                    raiz->dt=aux->dt;
                    aux->dt=data_aux;
                    raiz->left=ABB_remotion_node(raiz->left,d);
                    return raiz;
                }
                else{
                    ABB_node* aux;
                    if(!node_is_empty(raiz->left)){
                        aux=raiz->left;
                    }
                    else{
                        aux=raiz->right;
                    }
                    free(raiz);
                    return aux;
                }
            }
        }
        else{
            if(d->val<raiz->dt->val){
                raiz->left=ABB_remotion_node(raiz->left,d);
            }
            else{
                raiz->right=ABB_remotion_node(raiz->right,d);
            }
            return raiz;
        }
    }
}
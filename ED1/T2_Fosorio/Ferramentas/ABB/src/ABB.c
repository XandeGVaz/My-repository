#include "ABB.h"
#include <stdbool.h>

//Structs///////////////////////////////////////////////////////////////////////
typedef struct Data{
    int val;
}data;

typedef struct Node{
    data dt;
    tree_node* left;
    tree_node* right;
}tree_node;


//Intermediary functios//////////////////////////////////////////////////////////
bool node_is_empty(tree_node* raiz){
    bool b;
    b=(raiz==NULL);
    return b;
}

//Definition of fundamental functions ////////////////////////////////////////////
data* define_data(){
    data* d=calloc(1,sizeof(data));
    printf("\tDigite o valor do dado:"); 
    scanf("%d",&d->val);
    return d;
}

tree_node* create_node(data* d){
    tree_node* node=calloc(1,sizeof(tree_node));
    node->dt=*d;
    return node;
}

int return_node_valor(tree_node* node){
    return node->dt.val;
}

tree_node* add_node_v1(tree_node* raiz, data* d){
    if(node_is_empty(raiz)){
        tree_node* aux=create_node(d);
        aux->dt=*d;
        aux->left=NULL;
        aux->right=NULL;
        return aux;
    }
    else{
        if(d->val < raiz->dt.val){
            raiz->left=add_node_v1(raiz->left,d);
        }
        else{
            raiz->right=add_node_v1(raiz->right,d);
        }
        return raiz;
    }
}

void add_node_v2(tree_node**raiz, data* d){
    if(node_is_empty(*raiz)){
        *raiz=calloc(1,sizeof(tree_node));
        (*raiz)->dt=*d;
        (*raiz)->left=NULL;
        (*raiz)->right=NULL;
    }
    else{
        if(d->val < (*raiz)->dt.val){
            add_node_v2(&(*raiz)->left,d);
        }
        if(d->val > (*raiz)->dt.val){
            add_node_v2(&(*raiz)->right,d);
        }
    }
}

void add_node_v3(tree_node**raiz, data* d){
    tree_node*aux=*raiz;
    while(!node_is_empty(aux)){
        if(d->val < aux->dt.val){
            raiz=&aux->left;
        }
        else{
            raiz=&aux->right;
        }
        aux=*raiz;
    }
    aux=calloc(1,sizeof(tree_node));
    aux->dt.val=d->val;
    aux->left=NULL;
    aux->right=NULL;
    *raiz=aux;
}

void print_notorder(tree_node* raiz){
    if(!node_is_empty(raiz)){
        printf("%d ",raiz->dt.val);
        print_notorder(raiz->left);
        print_notorder(raiz->right);
    }
}

void print_order(tree_node* raiz){
    if(!node_is_empty(raiz)){
        print_order(raiz->left);
        printf("%d ",raiz->dt.val);
        print_order(raiz->right);
    }
}

tree_node* search_node_v1(tree_node*raiz,data*d){
    if(!node_is_empty(raiz)){
        if(raiz->dt.val==d->val){
            return raiz;
        }
        else if(d->val < raiz->dt.val){
            return search_node_v1(raiz->left,d);
        }
        else{
            return search_node_v1(raiz->right,d);
        }
    }
    return NULL;
}

tree_node* search_node_v2(tree_node*raiz,data*d){
    while(!node_is_empty(raiz)){
        if(d->val < raiz->dt.val){
            raiz=raiz->left;
        }
        else if(d->val > raiz->dt.val){
            raiz=raiz->right;
        }
        else return raiz;
    }
    return NULL;
}

int height_tree(tree_node*raiz){
    if(node_is_empty(raiz)){
        return -1;
    }
    else{
        int left = height_tree(raiz->left);
        int right = height_tree(raiz->right);
        if(left>right){
            return(left+1);
        }
        else{
            return(right+1);
        }
    }
}

int number_nodes(tree_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else{
        return(1+number_nodes(raiz->left)+number_nodes(raiz->right));
    }
}

int number_sheets(tree_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else if(node_is_empty(raiz->left) && node_is_empty(raiz->right)){
        return 1;
    }
    else{
        return(number_sheets(raiz->left)+number_sheets(raiz->right));
    }
}

tree_node* remotion_node(tree_node* raiz,data*d){
    if(node_is_empty(raiz)){
        printf("Valor não encontrado\n");
        return NULL;
    }
    else{
        if(raiz->dt.val==d->val){
            if( node_is_empty(raiz->left) && node_is_empty(raiz->right)){
                free(raiz);
                return NULL;
            }
            else{
                if((!node_is_empty(raiz)) && (!node_is_empty(raiz))){
                    tree_node*aux=raiz->left;
                    while(!node_is_empty(aux->right)){
                        aux=aux->right;
                    }
                    data data_aux=raiz->dt;
                    raiz->dt=aux->dt;
                    aux->dt=data_aux;
                    raiz->left=remotion_node(raiz->left,d);
                    return raiz;
                }
                else{
                    tree_node* aux;
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
            if(d->val<raiz->dt.val){
                raiz->left=remotion_node(raiz->left,d);
            }
            else{
                raiz->right=remotion_node(raiz->right,d);
            }
            return raiz;
        }
    }
}
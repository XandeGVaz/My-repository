#include "ABB.h"

//Structs///////////////////////////////////////////////////////////////////////
typedef struct Data{
    char TAG[10];
    int status;
}data;

typedef struct Node{
    data dt;
    struct Node *left;
    struct Node *right;
}tree_node;


//Funcoes intermediarias/////////////////////////////////////////////////////////
bool node_is_empty(tree_node* raiz){
    bool b;
    b=(raiz==NULL);
    return b;
}

//Implementacao das funcoes principais ////////////////////////////////////////////
data* define_data_tree(char* TAG,int status){
    data* d=calloc(1,sizeof(data)); 
    strcpy(d->TAG,TAG);
    d->status=status;
    return d;
}

tree_node* create_node(data* d){
    tree_node* node=calloc(1,sizeof(tree_node));
    node->dt=*d;
    node->left==NULL;
    node->right==NULL;
    return node;
}

char* return_TAG_tree(tree_node* node){
    return node->dt.TAG; 
}
int return_status_tree(tree_node* node){
    return node->dt.status; 
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
        if(strcmp(d->TAG,raiz->dt.TAG)<0){
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
        if(strcmp(d->TAG,(*raiz)->dt.TAG)<0){
            add_node_v2(&(*raiz)->left,d);
        }
        if(strcmp(d->TAG,(*raiz)->dt.TAG)>0){
            add_node_v2(&(*raiz)->right,d);
        }
    }
}

void add_node_v3(tree_node**raiz, data* d){
    tree_node*aux=*raiz;
    while(!node_is_empty(aux)){
        if(strcmp(d->TAG,(*raiz)->dt.TAG)<0){
            raiz=&aux->left;
        }
        else{
            raiz=&aux->right;
        }
        aux=*raiz;
    }
    aux=create_node(d);
    *raiz=aux;
}

void print_notorder(tree_node* raiz){ //esta em pre-ordem
    if(!node_is_empty(raiz)){
        printf("%s %d\n",raiz->dt.TAG,raiz->dt.status);
        print_notorder(raiz->left);
        print_notorder(raiz->right);
    }
}

void print_order(tree_node* raiz){ //esta em ordem
    if(!node_is_empty(raiz)){
        print_order(raiz->left);
        printf("%s ",raiz->dt.TAG);
        print_order(raiz->right);
    }
}

tree_node* search_node_v1(tree_node*raiz,data*d){
    if(!node_is_empty(raiz)){
        if(strcmp(d->TAG,raiz->dt.TAG)==0){
            return raiz;
        }
        else if(strcmp(d->TAG,raiz->dt.TAG)<0){
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
        if(strcmp(d->TAG,raiz->dt.TAG)<0){
            raiz=raiz->left;
        }
        else if(strcmp(d->TAG,raiz->dt.TAG)>0){
            raiz=raiz->right;
        }
        else return raiz;
    }
    return NULL;
}
int nodes_read_until(tree_node*raiz, data*d){
    int cont=0;
    while(!node_is_empty(raiz)){
        if(strcmp(d->TAG,raiz->dt.TAG)<0){
            raiz=raiz->left;
            cont++;
        }
        else if(strcmp(d->TAG,raiz->dt.TAG)>0){
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
        if(strcmp(d->TAG,raiz->dt.TAG)==0){
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
            if((strcmp(d->TAG,raiz->dt.TAG)<0)){
                raiz->left=remotion_node(raiz->left,d);
            }
            else{
                raiz->right=remotion_node(raiz->right,d);
            }
            return raiz;
        }
    }
}
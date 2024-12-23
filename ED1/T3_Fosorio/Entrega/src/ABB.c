#include "ABB.h"

//Structs///////////////////////////////////////////////////////////////////////
typedef struct ABB_data{
    char TAG[10];
    int status;
}ABB_data;

typedef struct Node{
    ABB_data *dt;
    struct Node *left;
    struct Node *right;
}ABB_node;


//Funcoes intermediarias/////////////////////////////////////////////////////////
bool ABB_node_is_empty(ABB_node* raiz){
    bool b;
    b=(raiz==NULL);
    return b;
}

//Implementacao das funcoes principais ////////////////////////////////////////////
ABB_data* ABB_define_data(char* TAG,int status){
    ABB_data* d=calloc(1,sizeof(ABB_data)); 
    strcpy(d->TAG,TAG);
    d->status=status;
    return d;
}

ABB_node* ABB_create_node(ABB_data* d){
    ABB_node* node=calloc(1,sizeof(ABB_node));
    node->dt=d;
    node->left==NULL;
    node->right==NULL;
    return node;
}

char* ABB_return_TAG(ABB_node* node){
    return node->dt->TAG; 
}
int ABB_return_status(ABB_node* node){
    return node->dt->status; 
}


ABB_node* ABB_add_node_v1(ABB_node* raiz, ABB_data* d){
    if(ABB_node_is_empty(raiz)){
        ABB_node* aux=ABB_create_node(d);
        aux->dt=d;
        aux->left=NULL;
        aux->right=NULL;
        return aux;
    }
    else{
        if(strcmp(d->TAG,raiz->dt->TAG)<0){
            raiz->left=ABB_add_node_v1(raiz->left,d);
        }
        else{
            raiz->right=ABB_add_node_v1(raiz->right,d);
        }
        return raiz;
    }
}

void ABB_add_node_v2(ABB_node**raiz, ABB_data* d){
    if(ABB_node_is_empty(*raiz)){
        *raiz=calloc(1,sizeof(ABB_node));
        (*raiz)->dt=d;
        (*raiz)->left=NULL;
        (*raiz)->right=NULL;
    }
    else{
        if(strcmp(d->TAG,(*raiz)->dt->TAG)<0){
            ABB_add_node_v2(&(*raiz)->left,d);
        }
        if(strcmp(d->TAG,(*raiz)->dt->TAG)>0){
            ABB_add_node_v2(&(*raiz)->right,d);
        }
    }
}

void ABB_add_node_v3(ABB_node**raiz, ABB_data* d){
    ABB_node*aux=*raiz;
    while(!ABB_node_is_empty(aux)){
        if(strcmp(d->TAG,(*raiz)->dt->TAG)<0){
            raiz=&aux->left;
        }
        else{
            raiz=&aux->right;
        }
        aux=*raiz;
    }
    aux=ABB_create_node(d);
    *raiz=aux;
}

void ABB_print_notorder(ABB_node* raiz){ //esta em pre-ordem
    if(!ABB_node_is_empty(raiz)){
        printf("%s %d\n",raiz->dt->TAG,raiz->dt->status);
        ABB_print_notorder(raiz->left);
        ABB_print_notorder(raiz->right);
    }
}

void ABB_print_order(ABB_node* raiz){ //esta em ordem
    if(!ABB_node_is_empty(raiz)){
        ABB_print_order(raiz->left);
        printf("%s ",raiz->dt->TAG);
        ABB_print_order(raiz->right);
    }
}

ABB_node* ABB_search_node_v1(ABB_node*raiz,ABB_data*d){
    if(!ABB_node_is_empty(raiz)){
        if(strcmp(d->TAG,raiz->dt->TAG)==0){
            return raiz;
        }
        else if(strcmp(d->TAG,raiz->dt->TAG)<0){
            return ABB_search_node_v1(raiz->left,d);
        }
        else{
            return ABB_search_node_v1(raiz->right,d);
        }
    }
    return NULL;
}

ABB_node* ABB_search_node_v2(ABB_node*raiz,ABB_data*d){
    while(!ABB_node_is_empty(raiz)){
        if(strcmp(d->TAG,raiz->dt->TAG)<0){
            raiz=raiz->left;
        }
        else if(strcmp(d->TAG,raiz->dt->TAG)>0){
            raiz=raiz->right;
        }
        else return raiz;
    }
    return NULL;
}
int ABB_nodes_read_until(ABB_node*raiz, ABB_data*d){
    int cont=0;
    while(!ABB_node_is_empty(raiz)){
        if(strcmp(d->TAG,raiz->dt->TAG)<0){
            raiz=raiz->left;
            cont++;
        }
        else if(strcmp(d->TAG,raiz->dt->TAG)>0){
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
    if(ABB_node_is_empty(raiz)){
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
    if(ABB_node_is_empty(raiz)){
        return 0;
    }
    else{
        return(1+ABB_number_nodes(raiz->left)+ABB_number_nodes(raiz->right));
    }
}

int ABB_number_sheets(ABB_node*raiz){
    if(ABB_node_is_empty(raiz)){
        return 0;
    }
    else if(ABB_node_is_empty(raiz->left) && ABB_node_is_empty(raiz->right)){
        return 1;
    }
    else{
        return(ABB_number_sheets(raiz->left)+ABB_number_sheets(raiz->right));
    }
}

ABB_node* ABB_remotion_node(ABB_node* raiz,ABB_data*d){
    if(ABB_node_is_empty(raiz)){
        printf("Valor não encontrado\n");
        return NULL;
    }
    else{
        if(strcmp(d->TAG,raiz->dt->TAG)==0){
            if( ABB_node_is_empty(raiz->left) && ABB_node_is_empty(raiz->right)){
                free(raiz);
                return NULL;
            }
            else{
                if((!ABB_node_is_empty(raiz)) && (!ABB_node_is_empty(raiz))){
                    ABB_node*aux=raiz->left;
                    while(!ABB_node_is_empty(aux->right)){
                        aux=aux->right;
                    }
                    ABB_data *ABB_data_aux=raiz->dt;
                    raiz->dt=aux->dt;
                    aux->dt=ABB_data_aux;
                    raiz->left=ABB_remotion_node(raiz->left,d);
                    return raiz;
                }
                else{
                    ABB_node* aux;
                    if(!ABB_node_is_empty(raiz->left)){
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
            if((strcmp(d->TAG,raiz->dt->TAG)<0)){
                raiz->left=ABB_remotion_node(raiz->left,d);
            }
            else{
                raiz->right=ABB_remotion_node(raiz->right,d);
            }
            return raiz;
        }
    }
}
#include "AVL.h"
#include <stdbool.h>

//Structs///////////////////////////////////////////////////////////////////////
typedef struct Data{
    int val;
}AVL_data;

typedef struct Node{
    AVL_data* dt;
    AVL_node* left;
    AVL_node* right;
    short height;
}AVL_node;

//Intermediary functios//////////////////////////////////////////////////////////

bool node_is_empty(AVL_node* raiz){
    bool b;
    b=(raiz==NULL);
    return b;
}

short bigger(short a, short b){
    return(a>b)?a:b;
}

short height_node(AVL_node* node){
    if(node_is_empty(node)) return(-1);
    else return node->height;
}

//Rotations//////////////////////////////////////////////////////////

AVL_node* left_rotation(AVL_node* r){
    AVL_node *y, *f;
    y=r->right;
    f=y->left;

    y->left=r;
    r->right=f;

    r->height=bigger(height_node(r->left),height_node(r->right))+1;
    y->height=bigger(height_node(y->left),height_node(y->right))+1;

    return y;
}

AVL_node* right_rotation(AVL_node* r){
    AVL_node *y, *f;
    y=r->left;
    f=y->right;

    y->right=r;
    r->left=f;

    r->height=bigger(height_node(r->left),height_node(r->right))+1;
    y->height=bigger(height_node(y->left),height_node(y->right))+1;

    return y;
}

AVL_node* right_left_rotation(AVL_node* r){
    r->right=right_rotation(r->right);
    return left_rotation(r);
}

AVL_node* left_right_rotation(AVL_node* r){
    r->left=left_rotation(r->left);
    return right_rotation(r);
}

//Intermediary functios AVL//////////////////////////////////////////////////////////

short balance_factor(AVL_node* node){
    if(!node_is_empty(node)){
        return(height_node(node->left)-height_node(node->right));
    }
    else return 0;
}

AVL_node* balancing(AVL_node* raiz){
    short fb=balance_factor(raiz);

    if(fb<-1 && balance_factor(raiz->right)<=0)
        raiz=left_rotation(raiz);

    if(fb>1 && balance_factor(raiz->left)>=0)
        raiz=right_rotation(raiz);

    if(fb>1 && balance_factor(raiz->left)<0)
        raiz=left_right_rotation(raiz);

    if(fb<-1 && balance_factor(raiz->right)>0)
        raiz=right_left_rotation(raiz);

    return raiz;  
}

//Definition of fundamental functions ////////////////////////////////////////////
AVL_data* AVL_define_data(){
    AVL_data* d=calloc(1,sizeof(AVL_data));
    printf("\tDigite o valor do dado:"); 
    scanf("%d",&d->val);
    return d;
}

AVL_node* AVL_create_node(AVL_data* d){
    AVL_node* node=calloc(1,sizeof(AVL_node));
    node->dt=d;
    node->left=NULL;
    node->right=NULL;
    node->height=0;
    return node;
}

int AVL_return_node_valor(AVL_node* node){
    return node->dt->val;
}

AVL_node* AVL_add_node_v1(AVL_node* raiz, AVL_data* d){
    if(node_is_empty(raiz)){
        return AVL_create_node(d);
    }
    else{
        if(d->val < raiz->dt->val){
            raiz->left=AVL_add_node_v1(raiz->left,d);
        }
        else if (d->val > raiz->dt->val){
            raiz->right=AVL_add_node_v1(raiz->right,d);
        }
        else printf("\nTal elemento ja existe!");
    }

    raiz->height=bigger(height_node(raiz->left),height_node(raiz->right))+1;
    raiz=balancing(raiz);

    return raiz;
}


void AVL_print_notorder(AVL_node* raiz){
    if(!node_is_empty(raiz)){
        printf("%d ",raiz->dt->val);
        AVL_print_notorder(raiz->left);
        AVL_print_notorder(raiz->right);
    }
}

void AVL_print_order(AVL_node* raiz, int level){
    if(!node_is_empty(raiz)){
        AVL_print_order(raiz->left,level+1);
        printf("%d[%d]",raiz->dt->val,level);
        AVL_print_order(raiz->right,level+1);
    }
}

void AVL_print(AVL_node* raiz, int level){
    int i;
    if(!node_is_empty(raiz)){
        AVL_print(raiz->right,level+1);
        printf("\n\n");

        for(i=0;i<level;i++){
            printf("\t");
        }
        printf("%d",raiz->dt->val);
        AVL_print(raiz->left,level+1);
    }
}

AVL_node* AVL_search_node_v1(AVL_node*raiz,AVL_data*d){
    if(!node_is_empty(raiz)){
        if(raiz->dt->val==d->val){
            return raiz;
        }
        else if(d->val < raiz->dt->val){
            return AVL_search_node_v1(raiz->left,d);
        }
        else{
            return AVL_search_node_v1(raiz->right,d);
        }
    }
    return NULL;
}

int AVL_nodes_read_until(AVL_node*raiz, int val){
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

int AVL_height_tree(AVL_node*raiz){
    if(node_is_empty(raiz)){
        return -1;
    }
    else{
        int left = AVL_height_tree(raiz->left);
        int right = AVL_height_tree(raiz->right);
        if(left>right){
            return(left+1);
        }
        else{
            return(right+1);
        }
    }
}

int AVL_number_nodes(AVL_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else{
        return(1+AVL_number_nodes(raiz->left)+AVL_number_nodes(raiz->right));
    }
}

int AVL_number_sheets(AVL_node*raiz){
    if(node_is_empty(raiz)){
        return 0;
    }
    else if(node_is_empty(raiz->left) && node_is_empty(raiz->right)){
        return 1;
    }
    else{
        return(AVL_number_sheets(raiz->left)+AVL_number_sheets(raiz->right));
    }
}

AVL_node* AVL_remotion_node(AVL_node* raiz,AVL_data*d){
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
                    AVL_node*aux=raiz->left;
                    while(!node_is_empty(aux->right)){
                        aux=aux->right;
                    }
                    AVL_data* AVL_data_aux=raiz->dt;
                    raiz->dt=aux->dt;
                    aux->dt=AVL_data_aux;
                    raiz->left=AVL_remotion_node(raiz->left,d);
                    return raiz;
                }
                else{
                    AVL_node* aux;
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
                raiz->left=AVL_remotion_node(raiz->left,d);
            }
            else{
                raiz->right=AVL_remotion_node(raiz->right,d);
            }
            raiz->height=bigger(height_node(raiz->left),height_node(raiz->right))+1;
            raiz=balancing(raiz);
            return raiz;
        }
    }
}
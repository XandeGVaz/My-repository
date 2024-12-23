#include "list.h"

//Structs//////////////////////////////////////////////////////////////////////////
typedef struct Data{
    char TAG[10];
    int status;
}data;

typedef struct _doubly_node{
    data dt;
    struct _doubly_node *prev;
    struct _doubly_node *next;
}
list_node;

typedef struct _doubly_linked_list {
    list_node *begin;
    list_node *end;
    size_t size;
}List;

//Intermediary functios//////////////////////////////////////////////////////////////
bool List_is_empty(const List *L) {
    return L->size == 0;
}

//Implementation of fundamental functions ////////////////////////////////////////////
data* define_data_list(char* TAG,int status){
    data* d=calloc(1,sizeof(data)); 
    strcpy(d->TAG,TAG);
    d->status=status;
    return d;
}

list_node* Listnode_create(data*d) {
    list_node*node = (list_node*) calloc(1, sizeof(list_node));
    node->prev = NULL;
    node->next = NULL;
    node->dt = *d;

    return node;
}

List* List_create() {
    List *L = (List*) calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}


void List_destroy(List **L_ref) {
    List *L = *L_ref;

    list_node *p = L->begin;
    list_node *aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

void List_add_first(List *L, data*d) {
    list_node *p = Listnode_create(d);
    p->next = L->begin;

    if (List_is_empty(L)) {
        L->end = p;
    }
    else {
        L->begin->prev = p;
    }

    L->begin = p;
    L->size++;
}

void List_add_last(List *L, data*d) {
    list_node *p = Listnode_create(d);
    p->prev = L->end;

    if (List_is_empty(L)) {
        L->begin = p;
    }
    else {
        L->end->next = p;
    }

    L->end = p;
    L->size++;
}



void List_print(const List *L) {
    list_node *p = L->begin;

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%s %d\n", p->dt.TAG,p->dt.status);
        p = p->next;
    }
}

void List_inverted_print(const List *L) {
    list_node *p = L->end;

    printf("L->end -> ");

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%s -> ", p->dt.TAG);
        p = p->prev;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L->begin = NULL\n");
    }
    else {
        printf("L->begin = %.s\n", L->begin->dt.TAG);
    }

    printf("Size: %lu\n", L->size);
    puts("");
}

void List_remove(List *L, data*d) {
    if (!List_is_empty(L)) {
        list_node *p = L->begin;

        // caso 1: o elemento está na cabeça da lista
        if (strcmp(d->TAG,L->begin->dt.TAG)==0) {
            L->begin = p->next;

            // a lista possui apenas um único elemento
            if (L->end == p) {
                L->end = NULL;
            }
            // a lista possui mais de um elemento
            else {
                L->begin->prev = NULL;
            }

            free(p);
            L->size--;
        }
        // caso 2: o elemento está no meio da lista
        // caso 3: o elemento está no final da lista
        else {
            p = p->next;

            while (p != NULL) {
                if (strcmp(d->TAG,p->dt.TAG)==0) {
                    p->prev->next = p->next;

                    // caso 3
                    if (L->end == p) {
                        L->end = p->prev;
                    }
                    // caso 2
                    else {
                        p->next->prev = p->prev;
                    }

                    free(p);
                    p = NULL;
                    L->size--;
                }
                else {
                    p = p->next;
                }
            }
        }
    }
}
void List_add_wage(List *L, data*d){
    list_node *p=Listnode_create(d);
    list_node *a=L->begin;
    if(!List_is_empty(L)){
        while(a!=NULL && strcmp(a->dt.TAG,d->TAG)<=0){
            a=a->next;
        }
        if(a==NULL){
            List_add_last(L,d);
        }
        else if(a==L->begin){
            List_add_first(L,d);
        }
        else{
            p->next=a;
            a->prev->next=p;
            p->prev=a->prev;
            a->prev=p;
            L->size++;
        }
    }
    else{
        List_add_first(L,d);
    }
}

data* Return_last_val(const List *L){
    if(L->end==NULL){
        return NULL;
    }
    else{
        return(define_data_list(L->end->dt.TAG,L->end->dt.status));
    }
}

list_node* Search_listnode(List*L, data*d){
    list_node*p=L->begin;
    while(strcmp(p->dt.TAG,d->TAG)!=0 && p!=NULL){
        p=p->next;
    }
    return p;
}

list_node* Search_orderlistnode(List*L, data*d){
    list_node*p=L->begin;
    while(p!=NULL){
        if(strcmp(d->TAG,p->dt.TAG)<=0) break; //Mal otimizado pois caso p=NULL entre no strcmp
        p=p->next;                             // haverá erro de Segmentation fault !
    }
    if(p!=NULL){
        if(strcmp(p->dt.TAG,d->TAG)==0){
            return p;
        }
    }
    else return NULL;
}

int Listnodes_read_ultil(List*L, data*d){
    int cont=0;
    list_node*p=L->begin;
    while(p!=NULL){
        if(strcmp(d->TAG,p->dt.TAG)<=0) break; //Mal otimizado pois caso p=NULL entre no strcmp
        p=p->next;                             // haverá erro de Segmentation fault !
        cont++;
    }
    if(p!=NULL){
        if(strcmp(d->TAG,p->dt.TAG)<0 || strcmp(d->TAG,p->dt.TAG)==0){
            cont++;
        }
    }
    return cont;
}

int List_size(List*L){
    list_node* p=L->begin;
    int cont=0;
    while(p!=NULL){
        p=p->next;
        cont++;
    }
    return cont;
}


List* Return_inverted_list(List* L){
    List*l=List_create();
    list_node* a=L->end;
    if(!List_is_empty(L)){
        while(a!=NULL){
            List_add_last(l,define_data_list(a->dt.TAG,a->dt.status));
            a=a->prev;
        }
        return l;
    }
    else{
        return L;
    }
}

List* ReturnList_whitout_repetitive_nodes(List* L){
    list_node*a=NULL;
    a=L->begin->next;
    List *l=List_create();
    List_add_first(l,define_data_list(L->begin->dt.TAG,L->begin->dt.status));
    while(a!=NULL){
        if(!Repetitive_node(L,a)){
            List_add_last(l,define_data_list(a->dt.TAG,a->dt.status));
        }
        a=a->next;
    }

    return l;
}

bool Repetitive_node(List*L,list_node* p){
    if(strcmp(p->dt.TAG,p->prev->dt.TAG)==0){
        return 1;
    }
    else return 0;
}

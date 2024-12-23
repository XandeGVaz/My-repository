#include "list.h"

typedef struct _doubly_node{
    char  wrd[10];
    struct _doubly_node *prev;
    struct _doubly_node *next;
}Node ;

typedef struct _doubly_linked_list{
    Node *begin;
    Node *end;
    size_t size;
}List;


Node *Node_create(const char *wrd) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    strcpy(node->wrd,wrd);

    return node;
}

List *List_create() {
    List *L = (List*) calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}


void List_destroy(List **L_ref) {
    List *L = *L_ref;

    Node *p = L->begin;
    Node *aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool List_is_empty(const List *L) {
    return L->size == 0;
}


void List_add_first(List *L,const char *wrd) {
    Node *p = Node_create(wrd);
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

void List_add_last(List *L, const char *wrd) {
    Node *p = Node_create(wrd);
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
    Node *p = L->begin;
    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%s ", p->wrd);
        p = p->next;
    }
    printf("\n");
}

void List_inverted_print(const List *L) {
    Node *p = L->end;

    printf("L->end -> ");

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%s -> ", p->wrd);
        p = p->prev;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L->begin = NULL\n");
    }
    else {
        printf("L->begin = %s\n", L->begin->wrd);
    }
    
    printf("Size: %lu\n", L->size);
    puts("");
}

size_t List_print_size(List *L){
    return(L->size);
}

void List_remove(List *L, const char *wrd) {
    if (!List_is_empty(L)) {
        Node *p = L->begin;

        // caso 1: o elemento está na cabeça da lista
        if (identical_strings(L->begin->wrd,wrd)) {
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
                if (identical_strings(p->wrd,wrd)) {
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

//Funções adicionais para a o funcionamento do projeto//
bool identical_strings(const char *s1,const char *s2){
    int b=strcmp(s1,s2);
    return b==0;
}

void List_add_after_cursor(List *L,Node* G,const char *wrd){
    if(G!=NULL){
        Node *p=Node_create(wrd);
        p->next=G->next;
        if(G->next!=NULL){
            G->next->prev=p;
        }
        else{
            L->end=p;
        }
        G->next=p;
        p->prev=G; 
    }
}

void List_add_before_cursor(List *L,Node* G,const char *wrd){
    if(G!=NULL){
        Node *p=Node_create(wrd);
        p->next=G;
        if(G->prev!=NULL){
            G->prev->next=p;
        }
        else{
            L->begin=p;
        }
        p->prev=G->prev;
        G->prev=p;
    }
}

//Funções adicionais para o cursor//
Node* cursor_for_begin(List *L){
    return(L->begin);
}

Node* cursor_for_end(List *L){
    return(L->end);
}

Node* cursor_for_nextnode(Node *G){
    if(G!=NULL){
        return(G->next);
    }
}

Node* cursor_for_prevnode(Node *G){
    if(G!=NULL){
        return(G->prev);
    }
}

Node* cursor_for_word(Node *G,const char* wrd){
    if(G!=NULL){
        Node*p=G;
        while(p!=NULL && identical_strings(p->wrd,wrd)==0){
            p=p->next;
        }
        if(p!=NULL){
            return(p);
        }
        else{
            return(G);
        }
    }
}

void cursor_print_node(Node *G){
    if(G!=NULL){
        printf("%s\n",G->wrd);
    }
}

char* cursor_return_word(Node *G){
    return(G->wrd);
}

void cursor_remove_word(List* L,Node *G){
    Node* p=G;
    if(G!=NULL){
        if(G->prev==NULL){
            L->begin=G->next;
            if(G->next==NULL){
            L->end=G->prev;
            }
            else{
                G->next->prev=G->prev;
            }
            G=NULL;
        }
        else if(G->next==NULL){
            L->end=G->prev;
            G->prev->next=G->next;
            G=cursor_for_prevnode(G);
        }
        else{
            G->next->prev=G->prev;
            G->prev->next=G->next;
            G=cursor_for_prevnode(G);
        }
        free(p);
    }

}







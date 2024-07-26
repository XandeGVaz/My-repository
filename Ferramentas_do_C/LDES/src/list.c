#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


typedef struct _doubly_node {
    float val;
    struct _doubly_node *prev;
    struct _doubly_node *next;
} DoublyNode, Node;

typedef struct _doubly_linked_list {
    Node *begin;
    Node *end;
    size_t size;
} DoublyLinkedList, List;


Node *Node_create(float val) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->val = val;

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


void List_add_first(List *L, float val) {
    Node *p = Node_create(val);
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

void List_add_last(List *L, float val) {
    Node *p = Node_create(val);
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
        printf("%.2f\n", p->val);
        p = p->next;
    }
}

void List_inverted_print(const List *L) {
    Node *p = L->end;

    printf("L->end -> ");

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%.2f -> ", p->val);
        p = p->prev;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L->begin = NULL\n");
    }
    else {
        printf("L->begin = %.2f\n", L->begin->val);
    }

    printf("Size: %lu\n", L->size);
    puts("");
}

void List_remove(List *L, float val) {
    if (!List_is_empty(L)) {
        Node *p = L->begin;

        // caso 1: o elemento está na cabeça da lista
        if (L->begin->val == val) {
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
                if (p->val == val) {
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
void List_add_wage(List *L,float val){
    Node *p=Node_create(val);
    Node *a=L->begin;
    if(!List_is_empty(L)){
        while(a!=NULL && (a->val)<=val){
            a=a->next;
        }
        if(a==NULL){
            List_add_last(L,val);
        }
        else if(a==L->begin){
            List_add_first(L,val);
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
        List_add_first(L,val);
    }
}

float Return_last_val(const List *L){
    if(L->end==NULL){
        return(0);
    }
    else{
        return(L->end->val);
    }
}

List* Return_inverted_list(List* L){
    List*l=List_create();
    Node* a=L->end;
    if(!List_is_empty(L)){
        while(a!=NULL){
            List_add_last(l,a->val);
            a=a->prev;
        }
        return l;
    }
    else{
        return L;
    }
}

List* ReturnList_whitout_repetitive_nodes(List* L){
    Node*a=NULL;
    a=L->begin->next;
    List *l=List_create();
    List_add_first(l,L->begin->val);
    while(a!=NULL){
        if(!Repetitive_node(L,a)){
            List_add_last(l,a->val);
        }
        a=a->next;
    }

    return l;
}

bool Repetitive_node(List*L,Node* p){
    if(p->val>=(p->prev->val-0.005) && p->val<=(p->prev->val+0.005)){
        return 1;
    }
    else return 0;
}

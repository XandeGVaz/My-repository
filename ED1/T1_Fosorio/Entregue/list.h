#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef struct _doubly_node Node;
typedef struct _doubly_linked_list List;

Node *Node_create(const char *wrd);

List *List_create();
void List_destroy(List **L_ref);
bool List_is_empty(const List *L);
void List_add_first(List *L,const char *wrd);
void List_add_last(List *L,const  char *wrd);
void List_print(const List *L);
void List_inverted_print(const List *L);
size_t List_print_size(List *L);

//ADD Para a Lista//
Node *List_return_node(const List *L); 
void List_add_after_cursor(List *L,Node* G,const char *wrd); 
void List_add_before_cursor(List *L,Node* G,const char *wrd); 
bool identical_strings(const char*s1,const char*s2); 
//ADD Para o cursor//
Node* cursor_for_begin(List *L);
Node* cursor_for_end(List *L);
Node* cursor_for_nextnode(Node *G);
Node* cursor_for_prevnode(Node *G);
Node* cursor_for_word(Node *G,const char* wrd);
void cursor_print_node(Node *G);
char* cursor_return_word(Node *G);
void cursor_remove_word(List* L,Node *G);



void List_remove(List *L,const char *wrd);

#endif

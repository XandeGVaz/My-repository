#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

//Structs////////////////////////////////////////////////////////////////
typedef struct Data data;
typedef struct _doubly_node list_node;
typedef struct _doubly_linked_list List;

//Dados///////////////////////////////////////////////////////////////////
data* define_data_list(char*TAG, int status); // cria dado e do retorna ponteiro para ele

//Nodos///////////////////////////////////////////////////////////////////
list_node* Listnode_create(data*d); //cria um no contendo um dado
bool Repetitive_node(List*L, list_node*p);


//Alteracao lista/////////////////////////////////////////////////////////
List* List_create();
void List_destroy(List**L_ref);
void List_add_first(List*L, data*d);
void List_add_last(List*L, data*d);
void List_add_wage(List*L, data*d);
void List_print(const List*L);
void List_remove(List *L, data*d);
void List_inverted_print(const List*L);
List* Return_inverted_list(List*L);
List* ReturnList_whitout_repetitive_nodes(List*L);

//Retorno de nodos específicos//////////////////////////////////////////////
data* Return_last_val(const List*L);
list_node* Search_listnode(List*L, data*d);
list_node* Search_orderlistnode(List*L, data*d);
int Listnodes_read_ultil(List*L, data*d);
int List_size(List*L);


#endif

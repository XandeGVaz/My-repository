#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>



typedef struct Node ABB_node;
typedef struct ABB_data ABB_data;

//Dados///////////////////////////////////////////////////////////////////
ABB_data* ABB_define_data(char*, int); // cria dado e do retorna ponteiro para ele
ABB_node* ABB_create_node(ABB_data*); //cria um no e retorna ponteiro para ele

//Nodos///////////////////////////////////////////////////////////////////
char* ABB_return_TAG(ABB_node*);
int ABB_return_status(ABB_node*); //retorna os status do dado de um no

//Adicao de nodos//////////////////////////////////////////////////////////
ABB_node* ABB_add_node_v1(ABB_node*, ABB_data*);// com retorno e recursao
void ABB_add_node_v2(ABB_node**, ABB_data*);// com recursao
void ABB_add_node_v3(ABB_node**, ABB_data*);//sem retorno e recursao (+rapida)

//Impressao da arvore//////////////////////////////////////////////////////
void ABB_print_notorder(ABB_node*); //pre-ordem
void ABB_print_order(ABB_node*);// em ordem

//Retorno de nodos especificos/////////////////////////////////////////////
ABB_node* ABB_search_node_v1(ABB_node*, ABB_data*); // com recursao e mais custosa
ABB_node* ABB_search_node_v2(ABB_node*, ABB_data*); // sem recursao e +rapida
int ABB_nodes_read_until(ABB_node*, ABB_data*); // nodos lidos ate achar um nodo especifico

//Informacao da arvore//////////////////////////////////////////////////////
int ABB_height_tree(ABB_node*);
int ABB_number_nodes(ABB_node*);
int ABB_number_sheets(ABB_node*);

//Remocao///////////////////////////////////////////////////////////////////
ABB_node* ABB_remotion_node(ABB_node*, ABB_data*);



#endif

#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>



typedef struct Node tree_node;
typedef struct Data data;

//Dados///////////////////////////////////////////////////////////////////
data* define_data_tree(char*, int); // cria dado e do retorna ponteiro para ele
tree_node* create_node(data*); //cria um no e retorna ponteiro para ele

//Nodos///////////////////////////////////////////////////////////////////
char* return_(tree_node*);
int return_status_tree(tree_node*); //retorna os status do dado de um no

//Adicao de nodos//////////////////////////////////////////////////////////
tree_node* add_node_v1(tree_node*, data*);// com retorno e recursao
void add_node_v2(tree_node**, data*);// com recursao
void add_node_v3(tree_node**, data*);//sem retorno e recursao (+rapida)

//Impressao da arvore//////////////////////////////////////////////////////
void print_notorder(tree_node*); //pre-ordem
void print_order(tree_node*);// em ordem

//Retorno de nodos especificos/////////////////////////////////////////////
tree_node* search_node_v1(tree_node*, data*); // com recursao e mais custosa
tree_node* search_node_v2(tree_node*, data*); // sem recursao e +rapida
int nodes_read_until(tree_node*, data*); // nodos lidos ate achar um nodo especifico

//Informacao da arvore//////////////////////////////////////////////////////
int height_tree(tree_node*);
int number_nodes(tree_node*);
int number_sheets(tree_node*);

//Remocao///////////////////////////////////////////////////////////////////
tree_node* remotion_node(tree_node*, data*);



#endif

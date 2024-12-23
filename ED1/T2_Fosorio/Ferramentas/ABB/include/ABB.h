#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>



typedef struct Node tree_node;
typedef struct Data data;

//Remocao///////////////////////////////////////////////////////////////////
data* define_data(void); // cria dado e do retorna ponteiro para ele
tree_node* create_node(data*); //cria um no
int return_node_valor(tree_node*);//1-retorna o valor de um no especifico
                                  //2-precisa ser do tipo do valor do tipo data 
                                  //que deseja ser retornado

//Adicao de nodos//////////////////////////////////////////////////////////
tree_node* add_node_v1(tree_node*,data*);// com retorno e recursao
void add_node_v2(tree_node**,data*);// com recursao
void add_node_v3(tree_node**,data*);//sem retorno e recursao (+rapida)

//Impressao da arvore//////////////////////////////////////////////////////
void print_notorder(tree_node*);
void print_order(tree_node*);

//Retorno de nodos especificos/////////////////////////////////////////////
tree_node* search_node_v1(tree_node*,data*); // com recursao e mais custosa
tree_node* search_node_v2(tree_node*,data*); // sem recursao e +rapida

//Informacao da arvore//////////////////////////////////////////////////////
int height_tree(tree_node*);
int number_nodes(tree_node*);
int number_sheets(tree_node*);

//Remocao///////////////////////////////////////////////////////////////////
tree_node* remotion_node(tree_node*,data*);



#endif

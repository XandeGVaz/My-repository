#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>



typedef struct Node AVL_node;
typedef struct Data AVL_data;

//Remocao///////////////////////////////////////////////////////////////////
AVL_data* AVL_define_data(void); // cria dado e do retorna ponteiro para ele
AVL_node* AVL_create_node(AVL_data*); //cria um no
int AVL_return_node_valor(AVL_node*);//1-retorna o valor de um no especifico
                                  //2-precisa ser do tipo do valor do tipo AVL_data 
                                  //que deseja ser retornado

//Adicao de nodos//////////////////////////////////////////////////////////
AVL_node* AVL_add_node_v1(AVL_node*,AVL_data*);// com retorno e recursao

//Impressao da arvore//////////////////////////////////////////////////////
void AVL_print_notorder(AVL_node*);
void AVL_print_order(AVL_node*,int);
void AVL_print(AVL_node*,int);

//Retorno de nodos especificos/////////////////////////////////////////////
AVL_node* AVL_search_node_v1(AVL_node*,AVL_data*); // com recursao e mais custosa
int AVL_nodes_read_until(AVL_node*, int); //nosdos lidos até achar um específico

//Informacao da arvore//////////////////////////////////////////////////////
int AVL_height_tree(AVL_node*);
int AVL_number_nodes(AVL_node*);
int AVL_number_sheets(AVL_node*);

//Remocao///////////////////////////////////////////////////////////////////
AVL_node* AVL_remotion_node(AVL_node*,AVL_data*);



#endif

#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>



typedef struct Node ABB_node;
typedef struct Data ABB_data;

//Remocao///////////////////////////////////////////////////////////////////
ABB_data* ABB_define_data(void); // cria dado e do retorna ponteiro para ele
ABB_node* ABB_create_node(ABB_data*); //cria um no
int ABB_return_node_valor(ABB_node*);//1-retorna o valor de um no especifico
                                  //2-precisa ser do tipo do valor do tipo data 
                                  //que deseja ser retornado

//Adicao de nodos//////////////////////////////////////////////////////////
ABB_node* ABB_add_node_v1(ABB_node*,ABB_data*);// com retorno e recursao
void ABB_add_node_v2(ABB_node**,ABB_data*);// com recursao
void ABB_add_node_v3(ABB_node**,ABB_data*);//sem retorno e recursao (+rapida)

//Impressao da arvore//////////////////////////////////////////////////////
void ABB_print_notorder(ABB_node*);
void ABB_print_order(ABB_node*);

//Retorno de nodos especificos/////////////////////////////////////////////
ABB_node* ABB_search_node_v1(ABB_node*,ABB_data*); // com recursao e mais custosa
ABB_node* ABB_search_node_v2(ABB_node*,ABB_data*); // sem recursao e +rapida
int ABB_nodes_read_until(ABB_node*, int); //nosdos lidos até achar um específico

//Informacao da arvore//////////////////////////////////////////////////////
int ABB_height_tree(ABB_node*);
int ABB_number_nodes(ABB_node*);
int ABB_number_sheets(ABB_node*);

//Remocao///////////////////////////////////////////////////////////////////
ABB_node* ABB_remotion_node(ABB_node*,ABB_data*);



#endif

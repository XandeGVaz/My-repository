#ifndef IMPRESSAO_H
#define IMPRESSAO_H

#include "leitura.h"
#include "indice.h"

// mensagens de erro
void msg_erro_padrao();
void msg_reg_inexistente();
void msg_erro_insercao();
void msg_erro_remocao();

// impressao de dados
void imprime_registro_tela(registro reg_aux);
void imprime_cabecalho_tela(cabecalho cab_aux);
int imprime_bin(char* nome_bin);

// funções intermediárias para debug
void imprime_campo(campo camp);
void imprime_lista_campo(campo *lista);
void imprime_lista_RRN(int *RRN_lista, int tamLista);
void imprimeNodo(const indNodo * nodo);

#endif
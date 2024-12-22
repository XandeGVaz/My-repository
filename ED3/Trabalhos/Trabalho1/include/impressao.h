#ifndef IMPRESSAO_H
#define IMPRESSAO_H

#include "leitura.h"

// mensagens de erro
void msg_erro_padrao();
void msg_reg_inexistente();
void msg_erro_insercao();
void msg_erro_remocao();

// impressao de dados
void imprime_registro_tela(registro reg_aux);
void imprime_cabecalho_tela(cabecalho cab_aux);
int imprime_bin(char* nome_bin);

#endif
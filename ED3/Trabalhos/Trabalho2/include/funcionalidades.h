#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "leitura.h"
#include "entrada.h"
#include "impressao.h"
#include "busca.h"
#include "manipCab.h"
#include "manipBin.h"
#include "manipArvB.h"
#include "indice.h"

/*
* Recebe os dados de registros de um arquivo csv e cria o arquivo binário com esses dados e registros
*/
void funcionalidade1();

/*
* Imprime todos os registros do arquivo .bin e informações do cabeçalho
*/
void funcionalidade2();

/*
* Imprime registros procurados do arquivo .bin através de informações providas pelo usuário
*/
void funcionalidade3();

/*
* Remove logicamente registros do arquivo .bin com base em informações providas pelo usuário
*/
void funcionalidade4();

/*
*  Insere registros, com valores dos campos providos pelo usuário, no arquivo.bin seguindo a abordagem dinÂmica
*/
void funcionalidade5();

/*
* Realiza a compactação do arquivo .bin, removendo fisicamente os registros logicamente removidos
*/
void funcionalidade6();

/*
* Realiza a inserção das chaves dos registros de um arquivo de dados no arquivo de índice com uma àrvore B 
*/
void funcionalidade7();

/*
* Realiza a recuperacao de um registro com base no campo "nome", atraves do uso da estrutura de dados Arvore B
*/
void funcionalidade8();

/*
* Realiza a inserção de registros, com valores dos campos providos pelo usuário, nos arquivos de dados e indices
*/
void funcionalidade9();

#endif
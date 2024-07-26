#ifndef KNAP_SACK_H
#define KNAP_SACK_H

//Includes
#include "aux.h"

//////// Declaração de funções principais//////////////////////////////////////////////////////
/*
Entradas
    *   P: peso total suportado pela mochila
    *   Q: quantidade de itens que serão informados na array
    *   l: ponteiro para tipo lista com o vetor de dados e número total de itens nesse vetor
Saida
    *   Vetor de dados (itens) que correspondem ao valor máximo que pode ser levado na mochila
    *   ->Algoritmo dinâmico: itens em ordem crescente de índice (0,1,2,...,n-1)
    *   ->Algoritmo guloso: itens em ordem crescente de relação valor peso
*/
ldata* KNPS_dinamic(int P, int Q, ldata* l); //versão que usa programação dinâmica para a resolução do problema da mochila
ldata* KNPS_greedy(int P, int Q, ldata* l); //versão que usa algoritmo guloso para a resolução do problema da mochila
///////////////////////////////////////////////////////////////////////////////////////////////





























#endif 
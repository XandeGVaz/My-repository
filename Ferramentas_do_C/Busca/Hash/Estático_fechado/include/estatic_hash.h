#ifndef ESTATICHASH_H
#define ESTATICHASH_H

#define C1 1 
#define C2 0
#define h(k,i) (k +(C1*i)+(C2*i*i))%S //Define da função hash usada, critério do usuário desde que tenha: k(número inteiro da chave), i(índice) e S(tamanho da tabela hash)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int t_key; //Aqui declara-se o tipo de chave usada para procura dos dados
typedef struct type_data data; //Declaração sem definição da estrutura de um dado
typedef struct type_thash thash; //Declaração sem definição da estrutura de uma tabela hash

thash* make_thash(const int size);//Cria a tabela hash

int add_thash_data( thash* hash, const t_key key);//Adiciona dado com uma chave key, informando a posição onde o dado foi adicionado

int remotion_thash_data( thash* hash, const t_key key);//Remove um dado com base na sua chave e retorna a posição onde o dado removido estava

int search_thash_data( const thash* hash, const t_key key);//Retorna posiçãoo de um dado com base em sua chave (0,1,2,...,n-1)

int return_data_added(const thash* hash, const int pos);//Retorna quantidade de vezes que um dado foi adicionado na tabela com base em sua posição

void print_thash_datas(thash* hash); //Print das chaves da tabela hash e suas respectivas posições

#endif
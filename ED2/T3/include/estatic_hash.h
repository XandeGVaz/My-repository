#ifndef ESTATICHASH_H
#define ESTATICHASH_H


#define h(k,i) (k +(hash->C1*i)+(hash->C2*i*i))%S //Define da função hash usada, critério do usuário desde que tenha: k(número inteiro da chave), i(índice) e S(tamanho da tabela hash)
#define size_word 30 //Definição do tamanho das palavras que serão adicionadas na tabela

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char t_key; //Aqui declara-se o tipo de chave usada para procura dos dados
typedef struct type_data data; //Declaração sem definição da estrutura de um dado
typedef struct type_thash thash; //Declaração sem definição da estrutura de uma tabela hash

thash* make_thash(int size, int C1, int C2);//Cria a tabela hash

int add_thash_data(thash* hash,  t_key* key);//Adiciona dado com uma chave key, informando a posição onde o dado foi adicionado

int remotion_thash_data(thash* hash,  t_key* key);//Remove um dado com base na sua chave e retorna a posição onde o dado removido estava

int search_thash_data( const thash* hash,  t_key* key);//Retorna posição (0,1,2,...,n-1) de um dado na tabela hash, com base em sua chave

void print_data_info( const thash* hash, t_key* key);//Print de informações de um dado da tabela hash com base em uma chave

void print_thash_datas(const thash* hash); //Print das chaves da tabela hash

void print_thash_info(const thash* hash); //Print da quantidade de chaves diferenttes presentes na tabela e da chave que mais foi adicionada (juntamente com essa quantidade de adições dessa mesma chave)

#endif
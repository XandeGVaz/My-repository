#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

// Bibliotecas gerais necessárias
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <locale.h>

// Bibliotecas feitas pelo grupo
#include <funcoes_fornecidas.h>
#include <leitura.h>
#include <impressao.h>

// Defines de cores para busca em largura ou em profundidade
#define BRANCO 0
#define CINZA 1
#define PRETO 2

// Máximo inteiro definido para comparações de distância entre vértices
#define INT_MAX 2000000000

namespace elementos{

    class Elemento{

        private:

            std::string _nome;
            std::string _especie;
            std::string _habitat;
            std::string _tipo;
            std::string _dieta;
            std::string _alimento;
            int _populacao;

        public:

            // Construtores
            Elemento();                                                                                             // construtor padrão
            Elemento(const std::string &nome , const std::string &especie , const std::string &habitat ,            // construtor por parâmetros
            const std::string &tipo , const std::string &dieta , const std::string &alimento , int populacao );
            Elemento(registro reg);                                                                                 // construtor por registro
            Elemento(const std::string &nome);                                                                      // construtor por nome
            Elemento(const Elemento &elemento);                                                                     // construtor por cópia

            // Métodos de acesso
            std::string getNome() const;
            std::string getEspecie() const;
            std::string getHabitat() const;
            std::string getTipo() const;
            std::string getDieta() const;
            std::string getAlimento() const;
            int getPopulacao() const;

        };
}

#endif
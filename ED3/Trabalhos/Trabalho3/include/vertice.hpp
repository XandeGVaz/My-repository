#ifndef VERTICE_HPP
#define VERTICE_HPP

#include "elemento.hpp"

namespace vertices{

    using namespace elementos;

    class Vertice: public Elemento{

        std::list<Elemento> _adj;           // lista de adjacências
        std::list<int> _pesos;              // lista de pesos associados às adjacências

        int _grauSaida;                     // grau de saída do vértice
        int _grauEntrada;                   // grau de entrada do vértice

        int _cor;                           // cor do vértice para busca em largura ou profundidade

        // necessário para encontro do menor caminho
        int _distancia;                    // distância do vértice em relação a um vértice de origem

    
    public:

        // Construtores
        Vertice();                                                              // construtor padrão
        Vertice(const Elemento &elemento, int grauSaida , int grauEntrada);     // construtor por parâmetros
        Vertice(const Vertice &v);                                              // construtor por cópia

        // Métodos de acesso
        Elemento returnElemento() const;        // retorna o elemento associado ao vértice
        std::list<Elemento> returnAdj() const;  // retorna a lista de adjacências
        std::list<int> returnPesos() const;     // retorna a lista de pesos das adjacências
        int returnGrauSaida() const;            // retorna o grau de saída do vértice
        int returnGrauEntrada() const;          // retorna o grau de entrada do vértice
        int returnCor() const;                  // retorna a cor do vértice
        int returnDistancia() const;  // retorna a distância do vértice em relação a um vértice de origem
        int returnTempoDescoberta() const;      // retorna o tempo de descoberta do vértice
        int returnTempoFinalizacao() const;     // retorna o tempo de finalização do vértice

        // Métodos de modificação
        void incGrauSaida();                    // incrementa o grau de saída do vértice
        void incGrauEntrada();                  // incrementa o grau de entrada do vértice
        void addAdj(Elemento &elementoInsert, int peso);      //  adiciona um vértice a lista de vértices adjacentes da instância
        void setCor(int cor);                   // modifica a cor do vértice
        void setDistancia(long distancia);      // modifica a distância do vértice em relação a um vértice de origem
        void setTempoDescoberta(int tempo);     // modifica o tempo de descoberta do vértice
        void setTempoFinalizacao(int tempo);    // modifica o tempo de finalização do vértice

        // Métodos de busca
        std::list<Elemento>::iterator buscaAdj(const std::string &nome);  // busca um elemento na lista de adjacências

        // Métodos de impressão
        void imprimeVertice() const;            // imprime os dados do vértice e seus vértices adjacentes
        
    };
}

#endif
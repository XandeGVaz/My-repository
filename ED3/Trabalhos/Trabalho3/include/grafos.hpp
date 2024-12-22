#ifndef GRAFOS_HPP
#define GRAFOS_HPP

#include "elemento.hpp"
#include "vertice.hpp"

namespace grafos{

    // Namespace para os elementos do grafo
    using namespace elementos;
    using namespace vertices;

    class Grafo{

        std::list<Vertice> _vertices;       // lista de vértices
        
        long _numVertices;                  // número de vértices
        long _numArestas;                   // número de arestas

    
    public:   

        // Construtor
        Grafo(){
            _numVertices = 0;
            _numArestas = 0;
        }

        // Métodos de acesso
        std::list<Vertice> returnVertices() const;          // retorna a lista de vértices
        long returnNumVertices() const;                     // retorna o número de vértices
        long returnNumArestas() const;                      // retorna o número de arestas
        int returnIndiceVertice(const std::string &nome);   // retorna o índice i de um vértice na lista de vértices (se existir _vertices[i] == nome)

        // Métodos de modificação
        void atualizaVertice(Vertice &v);                   // verifica e trata o caso em que um vértice já foi adicionado na listas de adjacências de outro vértices
        void addVertice(const Vertice &v);                  // adiciona um vértice a lista de vértices do grafo

        // Métodos de busca
        std::list<Vertice>::iterator buscaVertice(const std::string &nome); // busca um vértice na lista de vértices
        std::list<Vertice>::iterator acessaVertice(int i);                  // acessa um vértice _vertices[i] na lista de vértices
        
        // Métodos de construção
        void addAresta(std::list<Vertice>::iterator itVerticeSaida, std::list<Vertice>::iterator itVerticeEntrada, registro regAux);    // adiciona uma aresta entre dois vértices

        // Métodos de impressão
        void imprimeGrafo();                                // imprime o grafo (vértices e adjacências)
        
        // Operador de atribuição
        Grafo& operator=(const Grafo &g);                   // cópia por atribuição
        
        // Métodos sobre a condição cíclica do grafo
        int numCiclosVertice(const std::string &nome, const std::string &nomeProcurado);        // número de ciclos em um vértice do grafo (parte recursiva)
        int numCiclosGrafo();                                                                   // número de ciclos do grafo (parte não recursiva)
        
        // Métodos de Djsktra
        int** matrizAdjacencias();                                                              // matriz de adjacências do grafo
        std::list<Vertice>::iterator menorDistancia(std::list<Vertice>::iterator itOrigem);     // retorna a menor distância exitente entre um vértice de origem e todos os outros vértices do grafo
        int menorCaminho(const std::string &nomeSaida, const std::string &nomeEntrada);         // menor caminho entre dois vértices do grafo

        // Métodos para avaliação da conectividade do grafo
        void DFS(const std::string &nomeOrigem, std::vector<std::string> &verticesPercorridos);     // busca em profundidade
        bool ehFortementeConexo();                                                                  // verifica se o grafo é fortemente conexo
       
        // Métodos de Kozaraju
        bool modDFS(const std::string &nomeOrigem);                                                 // busca em profundidade modificada
        Grafo retGrafoTransposto();                                                          // retorna o grafo transposto
        Grafo transpose();
        int numComponentes();                                                                       // retorna o número de componentes fortemente conexos

    };

}


// Funções auxiliares de interação com o usuário
grafos::Grafo criaGrafo(FILE* fp);                                      // função que cria um grafo a partir de um arquivo binário
void imprimeAdjacencias(grafos::Grafo &grafo, const std::string &nome); // função que imprime todos os vértices aos quais um vértice é adjacente
void msgFortementeConexo(bool fortementeConexo, int qntComponentes);    // função que imprime mensagem sobre conectividade do grafo
grafos::Grafo criaGrafo_sunlight(FILE* fp);


#endif 
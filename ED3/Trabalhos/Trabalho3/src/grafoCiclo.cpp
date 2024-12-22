#include "grafoCiclo.hpp"

using namespace grafos;


/*-----------------------------------Métodos sobre ciclos no grafo-----------------------------*/


/*Método tem como função retornar o núemro de ciclos simples envolvendo um vértice do grafo, utilizando busca em profundidade
    Este método não usa uma pilha em si, mas sim a recursão para realizar a busca em profundidade
        Parâmetros: nenhum
        Retorno: número de ciclos simples relacionados vértice
    OBS: vale ressaltar que na criação do grafo, todos os vértices são inicializados com a cor BRANCO(0)
*/
int Grafo::numCiclosVertice(const std::string &nome, const std::string &nomeProcurado){

    // Número de ciclos
    int ciclos = 0;

    // Iterator para vértico do grafo com nome igual ao passado como parâmetro
    std::list<Vertice>::iterator it = buscaVertice(nome);

    // Se o vértice não existe na lista, não há ciclos o envolvendo (como se fosse um vértice de borda)
    if(it == _vertices.end()){
        return 0;
    }

    // Se o vértice já foi visitado
    if(it->returnCor() == CINZA){
        
        // se o vértice é o procurado, incrementamos o número de ciclos
        if(it->getNome() == nomeProcurado) return 1;

        // caso contrário, backtracking
        else return 0;
    }

    // Se o vértice ainda não foi visitado, iniciamos a busca em profundidade e o pintamos de cinza
    it->setCor(CINZA);

    // Iterator para vértices adjacentes do vértice do iterator it
    std::list<Elemento>::iterator itAdj;

    // Lista de elementos adjacentes ao vértice do iterator it
    std::list<Elemento> adj =  it->returnAdj();

    // Iterator para percorrer a lista de adjacências , simulando o percurso de um possível ciclo
    for(itAdj = adj.begin(); itAdj != adj.end(); itAdj++){
        
        // Busca em vértice adjacente
        ciclos += numCiclosVertice(itAdj->getNome(), nomeProcurado);
    }

    // Após percorrer todos os caminhos possibilitados pelos vértices adjacentes, vértice volta a ser "não visitado"
    it->setCor(BRANCO);

    // Limpeza da lista de adjacências copiada
    adj.clear();

    // Retornamos o número de ciclos encontrados no caminho
    return ciclos;
}

/*Método tem como função retornar o núemro de ciclos simples de um grafo, utilizando busca em profundidade
    Este método basicamente usa o número de ciclos relacionados a cada vértice para calcular o número de ciclos do grafo
        Parâmetros: nenhum
        Retorno: número de ciclos simples do grafo
*/
int Grafo::numCiclosGrafo(){

    // Número de ciclos
    int ciclos = 0;

    // Iterator para percorrer a lista de vértices do grafo
    std::list<Vertice>::iterator it = _vertices.begin();

    // Iterator para percorrer a lista de vértices do grafo
    for( ; it != _vertices.end(); it++){
        ciclos += numCiclosVertice(it->getNome(), it->getNome());
    }

    // Retorno do número de ciclos do grafo
    return ciclos;
}
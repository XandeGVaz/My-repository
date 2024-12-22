#include "grafoMinCaminhos.hpp"

using namespace grafos;


/*-----------------------------------Métodos de mínimos caminhos do grafo-----------------------------*/

/*  Método que tem como função retornar vértice (não visitado <-> cor != CINZA) com a menor distância entre as distância de um vértice de origem e os demais 
    vértices do grafo
        Parâmetros: itOrigem - iterator para o vértice de origem
        Retorno: iterator para o vértice não visitado e com menor distância em relação a origem
    OBS: leva em consideração que todos os vértices são iniciados com distância infinita em relação a origem
*/
std::list<Vertice>::iterator Grafo::menorDistancia(std::list<Vertice>::iterator itOrigem){
    
    // Iterator para percorrer a lista de vértices do grafo
    std::list<Vertice>::iterator it = _vertices.begin();

    // Iterator para vértice com menor distância em relação a origem
    std::list<Vertice>::iterator itMenorDistancia;

    // itMenorDistância, a primeira vista, recebe primeiro vértice com cor == BRANCO
    for(; it != _vertices.end(); it++){
        if(it->returnCor() == BRANCO){
            break;
        } 
    }

    // Percorrimento do primeiro vértice branco até o final da lista
    itMenorDistancia = it;
    for(; it != _vertices.end(); it++){
        
        // Se o vértice indicado por it não foi visitado e sua distância em relação a origem é menor que a distância do vértice indicado por itMenor, itMenor a indicar o mesmo vértice que it
        if(it->returnCor() == BRANCO && it->returnDistancia() < itMenorDistancia->returnDistancia()) 
            itMenorDistancia = it;
        
    }

    /*  Retorna vértice com a menor distância em relação a origem 
    *caso nenhum vértice válido seja encontrado, retorna iterator para final da lista 
    */
    return itMenorDistancia;
}

/*Método que tem como função retornar o menor caminho entre dois vértices do grafo
    Este método utiliza a busca em largura para encontrar o menor caminho entre dois vértices
        Parâmetros: 
            ->nomeInicial: nome do vértice de origem
            ->nomeFinal: nome do último vértice do caminho
        Retorno: menor caminho entre os vértices de origem (inicial)  e vértice final
*/
int Grafo::menorCaminho(const std::string &nomeInicial, const std::string &nomeFinal){

    /*  Caso o nome final corresponda a um vértice de borda, torna-se necessário contabilizar sua distância
    *em relação ao vértice de origeram, para que possamos retornar a distância do menor caminho*/
    int distanciaBorda = INT_MAX; // Distância da borda do grafo em relação ao vértice de origem

    // Iterator para vértice de saída
    std::list<Vertice>::iterator itInicial = buscaVertice(nomeInicial);

    // Iterator para vértice de entrada
    std::list<Vertice>::iterator itFinal = buscaVertice(nomeFinal);

    // Se um dos vértices não existe, não há caminho entre eles
    if(itInicial == _vertices.end()) return -1;

    // Lista de elementos adjacentes a um vértice (evitar chamar a função returnAdj() muitas vezes)
    std::list<Elemento> adj;

    // Lista de pesos associados às adjacências de um vértice (evitar chamar a função returnPesos() muitas vezes)
    std::list<int> pesos;

    // iterator para vertice analisado e iterator para vertice adjacente
    std::list<Vertice>::iterator itVertice;
    std::list<Vertice>::iterator itVerticeAdj;


    //Inicialização de todos os vértices com _distancia = infinito e _cor = BRANCO 
    for(std::list<Vertice>::iterator it = _vertices.begin(); it != _vertices.end(); it++){
        it->setCor(BRANCO);         // vértice não visitado
        it->setDistancia(INT_MAX); // distância infinita em relação ao vértice de origem
    }
    
    // Inicialização da distância do vértice de origem em relação a ele mesmo
    itInicial->setDistancia(0);
    
    // Inicialmente, o vértice de análise corresponde ao vértice inicial
    itVertice = itInicial;

    // O processo de busca enquanto não determinar o menor caminho para todos os vértices
    for(int i = 0; i < _numVertices; i++){

        // Iterator para percorrer a lista de adjacências (elementos) do vértice associado ao elemento
        adj = itVertice->returnAdj();
        std::list<Elemento>::iterator itAdj = adj.begin();

        // Iterator para percorrer a lista de pesos associados às adjacências
        pesos = itVertice->returnPesos();
        std::list<int>::iterator itPesos = pesos.begin();

        // Vértice foi visitado
        itVertice->setCor(CINZA);

        // Preenchimento da fila com os vértices adjacentes ao vértice associado ao elemento
        for(; itAdj != adj.end(); itAdj++, itPesos++){
            
            // Busca vértice adjacente através de seu nome
            itVerticeAdj = buscaVertice(itAdj->getNome());

            // Caso o vértice adjacente não seja borda e não tenha sido visitado
            if(itVerticeAdj!=_vertices.end() && itVerticeAdj->returnCor() == BRANCO){
                
                // Atualiza a distância do vértice adjacente, caso a distância do vértice analisado + peso da aresta seja menor que a distância vigente do vértice adjacente vigente
                if(itVertice->returnDistancia() + *itPesos < itVerticeAdj->returnDistancia()){
                    itVerticeAdj->setDistancia(itVertice->returnDistancia() + *itPesos);
                }
                
            }

            // Caso o vértice adjacente seja borda
            else if( itVerticeAdj==_vertices.end() && itAdj->getNome() == nomeFinal){

                // Atualiza a distância do vértice adjacente de borda, caso a distância do vértice analisado + peso da aresta seja menor que a distância vigente do vértice adjacente 
                if(itVertice->returnDistancia() + *itPesos < distanciaBorda){
                    distanciaBorda = itVertice->returnDistancia() + *itPesos;
                }

            }
            
        }

        // limpa a lista de adjacências e de pesos
        adj.clear();
        pesos.clear();

        // Busca vértice com menor distância entre os vértices não visitados
        itVertice = menorDistancia(itInicial);
    }

    // Caso o vértice final seja borda
    if(itFinal==_vertices.end()){

        // Caso o vértice final não exista
        if (distanciaBorda == INT_MAX)
            return -1;

        // Se o vértice final e de borda existe
        else
            return distanciaBorda;
    }

    // Caso o vértice final não seja borda mas não existe caminho até ele
    if(itFinal->returnDistancia() == INT_MAX)
        return -1;
    
    // Caso o vértice final seja borda e possua um caminho válido 
    else
        return itFinal->returnDistancia();
}
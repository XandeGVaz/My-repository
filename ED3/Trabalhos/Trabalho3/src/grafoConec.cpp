#include "grafoConec.hpp"

using namespace grafos;

/*-----------------------------------Métodos sobre conectividade do grafo-----------------------------*/


/*Método que tem como função realizar a busca em profundida dentro do grafo
    Assim, através desse método setamos status (cor) dos vértices do grafo, bem como tempos de descoberta
    e finalização de cada vértice
        Parâmetros: 
            ->nomeOrigem: nome do vértice de origem
            ->tempo: tempo de descoberta do vértice de origem
        Retorno: nenhum
*/
void Grafo::DFS(const std::string &nomeOrigem, std::vector<std::string> &verticesPercorridos){
    
    // Iterator para vértico do grafo com nome igual ao passado como parâmetro
    std::list<Vertice>::iterator it = buscaVertice(nomeOrigem);

    // Se corresponde a um vértice de borda
    if(it == _vertices.end()){
        
        // Adiciona-se o vértice de borda ao vetor de vértices visitados
        verticesPercorridos.push_back(nomeOrigem);        
        return;     // backtracking
    }

    // Se o vértice já foi visitado
    if(it->returnCor() == CINZA || it->returnCor() == PRETO ){
        return;     // backtracking
    }

    // Se o vértice ainda não foi visitado, iniciamos a busca em profundidade e o pintamos de cinza
    it->setCor(CINZA);

    // Iterator para vértices adjacentes do vértice do iterator it
    std::list<Elemento>::iterator itAdj;

    // Lista de elementos adjacentes ao vértice do iterator it
    std::list<Elemento> adj =  it->returnAdj();

    // Iterator para percorrer a lista de adjacênciasz
    for(itAdj = adj.begin(); itAdj != adj.end(); itAdj++){
        
        // Busca em vértice adjacente
        DFS(itAdj->getNome(),  verticesPercorridos);
    }

    // Após percorrer todos os caminhos possibilitados pelos vértices adjacentes, vértice é tido como finalizado
    it->setCor(PRETO);

    // Adiciona-se o vértice ao vetor de vértices visitados e ao vetor de tempos de finalização
    verticesPercorridos.push_back(it->getNome());

    // Limpeza da lista de adjacências copiada
    adj.clear();

    // Retornamos para vértice precedente
    return;
}

/*Método que tem como função verificar se o grafo é fortemente conexo
    Assim, através desse método realizamos a busca em profundidade para um vértice e verificamos se todos os vértices
    foram visitados e finalizados após a DFS
        Parâmetros: nenhum
        Retorno: booleano que indica se o grafo é fortemente conexo
*/
bool Grafo::ehFortementeConexo(){

    // Booleano para verificar se o grafo é fortemente conexo
    bool fortementeConexo = true;

    // Iterator para percorrer a lista de vértices do grafo
    std::list<Vertice>::iterator it = _vertices.begin();

    // Vetor dos tempos de vertices visitados ordenados crescentemente por tempo de finalização
    std::vector<std::string> verticesVisitados;

    // Realiza a busca em profundidade para todos os vértices
    // Se for fortemente conexo, todos os vértices devem ter sido visitados e analisados após a DFS
    for(it = _vertices.begin(); it != _vertices.end() && fortementeConexo; it++){

        DFS(it->getNome(), verticesVisitados);

        // Se algum vértice não foi percorrido, o grafo não é fortemente conexo
        if(verticesVisitados.size() != returnNumVertices())
            fortementeConexo = false;

        verticesVisitados.clear();
    }

    return fortementeConexo;
}

/*Método que tem como função realizar a busca em profundida modificada para o método de Kosaraju
    Assim, através desse método teremos como prioridade vértices com maior tempo de finalização setado
    no processo de DFS normal
        Parâmetros: 
            ->nomeOrigem: nome do vértice de origem
            ->tempo: tempo de descoberta do vértice de origem
        Retorno: nenhum
*/
bool Grafo::modDFS(const std::string &nomeOrigem){

    // bolleano para verificar se parte é fortemente conexa
    bool parteConexa = true;

    // Iterator para vértico do grafo com nome igual ao passado como parâmetro
    std::list<Vertice>::iterator it = buscaVertice(nomeOrigem);

    // Se corresponde a um vértice de borda
    if(it == _vertices.end()){
        return true;     
    }

    // Se o vértice já foi visitado
    if(it->returnCor() == CINZA){
        return true;     // backtracking
    }

    // Se o vértice já foi analisado
    if(it->returnCor() == PRETO){
        return false;
    }

    // Se o vértice ainda não foi visitado, iniciamos a busca em profundidade e o pintamos de cinza
    it->setCor(CINZA);

    // Iterator para vértices adjacentes do vértice do iterator it
    std::list<Elemento>::iterator itAdj;

    // Lista de elementos adjacentes ao vértice do iterator it
    std::list<Elemento> adj =  it->returnAdj();

    // Iterator para percorrer a lista de adjacênciasz
    for(itAdj = adj.begin(); itAdj != adj.end(); itAdj++){
        
        // Busca em vértice adjacente
        parteConexa |= modDFS(itAdj->getNome());
    }

    // Após percorrer todos os caminhos possibilitados pelos vértices adjacentes, vértice é tido como finalizado
    it->setCor(PRETO);

    // Limpeza da lista de adjacências copiada
    adj.clear();

    // Retornamos para vértice precedente
    return parteConexa;
}

/*Método que tem como função retornar o grafo transposto de um grafo
    Assim, através desse método, invertemos as direções das arestas do grafo original
        Parâmetros: nenhum
        Retorno: grafo transposto
*/
Grafo Grafo::transpose(){

    // Grafo transposto
    Grafo grafoTransposto = Grafo();

    // registro auxiliar para adicionar arestas no grafo transposto
    registro regAux;
    regAux.removido = '0';
    regAux.encadeamento = -1;
    regAux.tamanho = -1;
    regAux.unidadeMedida = '0';
    regAux.velocidade = -1;
    strcpy(regAux.especie, "");
    strcpy(regAux.habitat, "");
    strcpy(regAux.tipo, "");
    strcpy(regAux.dieta, "");    
    

    // Iterator para percorrer a lista de vértices do grafo
    std::list<Vertice>::iterator itVertice = _vertices.begin();

    // Iterator para percorrer a lista de adjacências de cada vértice
    std::list<Elemento>::iterator itAdj;

    // Iterator para percorrer a lista de pesos associados às adjacências
    std::list<int>::iterator itPesos;
    
    // Preenchimento do grafo transposto
    for(; itVertice != _vertices.end(); itVertice++){
        
        // Obtém a lista de adjacências do vértice
        std::list<Elemento> adj = itVertice->returnAdj();

        // Obtém a lista de pesos associados às adjacências
        std::list<int> pesos = itVertice->returnPesos();

        // Obtem a lista de pesos associados às adjacências
        for(itAdj = adj.begin(), itPesos = pesos.begin(); itAdj != adj.end(); itAdj++, itPesos++){

            // Configuração do registro auxiliar para adicioanr aresta
            strcpy(regAux.nome, itAdj->getNome().data());
            regAux.populacao = *itPesos;
            strcpy(regAux.alimento , itVertice->getNome().data());

            // Adiciona aresta no grafo transposto
            grafoTransposto.addAresta(grafoTransposto.buscaVertice(itAdj->getNome()), grafoTransposto.buscaVertice(itVertice->getNome()), regAux);
        }
    }

    // Retorna o grafo transposto
    return grafoTransposto;
}

/*Método responsável por retornar um número de componentes fortemente conexas de um grafo
    Assim, através desse método, realizamos a busca em profundidade antes e após a transposição do grafo
    para verificar o número de componentes fortemente conexas
        Parâmetros: nenhum
        Retorno: número de componentes fortemente conexas
*/
int Grafo::numComponentes(){

    // Temporizador
    int tempo = 0;

    // Número de componentes fortemente conexos
    int numComponentes = 0;

    // Vetor de nomes dos vértices visitados na DFS -> corresponde a uma pilha de vértices visitados
    std::vector<std::string> verticesVisitados;

    // Inicialização de todos os vértices com _distancia = infinito e _cor = BRANCO
    for(std::list<Vertice>::iterator it = _vertices.begin(); it != _vertices.end(); it++){
        it->setCor(BRANCO);         // vértice não visitado
        it->setDistancia(INT_MAX);  // distância infinita em relação ao vértice de origem
    }

    // Realiza a busca em profundidade antes da transposição do grafo
    for(std::list<Vertice>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
        DFS(it->getNome(), verticesVisitados);

    // Grafo transposto
    Grafo grafoTransposto = transpose();
    
    // Realiza a busca em profundidade após a transposição do grafo partindo sempre do topo da pilha de vértices visitados
    while(verticesVisitados.size() > 0){
        
        // Realiza a busca em profundidade modificada, partindo do vértice do topo da pilha
        if(grafoTransposto.modDFS(verticesVisitados.back())){

            // Se a parte referente ao topo da pilha é fortemente conexa, incrementamos o número de componentes
            numComponentes++;
        }

        // Retira o vértice do topo da pilha
        verticesVisitados.pop_back();
    }
    
    // Retorna o número de componentes fortemente conexos
    return numComponentes;
}
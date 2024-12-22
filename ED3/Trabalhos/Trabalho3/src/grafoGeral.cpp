#include "grafoGeral.hpp"

using namespace grafos;


/*-----------------------------------Métodos gerais a respeito do grafo-----------------------------*/


// Método responsável por retornar lista de vértices do grafo
std::list<Vertice> Grafo::returnVertices() const{
    return _vertices;
}

// Método responsável por retornar número de vértices do grafo
long Grafo::returnNumVertices() const{
    return _numVertices;
}

// Método responsável por retornar número de arestas do grafo
long Grafo::returnNumArestas() const{
    return _numArestas;
}

/*Método responsável por retornar o índice i de um vértice (_vertices[i])*/
int Grafo::returnIndiceVertice(const std::string &nome){
    // índice a ser retornado
    int i = 0;

    // iterator para percorrer lista de vértices
    std::list<Vertice>::iterator it = _vertices.begin();
    
    for(; it!=_vertices.end(); it++){

        // Se o vértice _vertices[i] possui o nome igual ao nome passado como parâmetro, retornamos i
        if(it->getNome() == nome){
            return i;
        }

        i++;
    }

    // retorna -1 caso não encontre o vértice com nome passado por parâmetro
    return -1;

}   

/*Método responsável por atualizar um vértice antes de ser adicionado ao grafo
    Tal método verifica se o vértice a ser adicionado já possui arestas relacionadas a ele
        Parâmetros: Vertice v
        Retorno: nenhum
*/
void Grafo::atualizaVertice(Vertice &v){

    // iterator para percorrer a lista de vértices do grafo
    std::list<Vertice>::iterator itVertices = _vertices.begin();

    // iterator para percorrer a lista de adjacências de cada vértice do grafo
    std::list<Elemento>::iterator itAdj;
    std::list<Elemento> adj;
    
    // percurso da lista de vértices
    for( ; itVertices != _vertices.end(); itVertices++){

        // se a lista de adjacências do vértice não está vazia, limpamos a lista
        if(adj.size() != 0) adj.clear();

        // obtemos a lista de adjacências do vértice
        adj = itVertices->returnAdj();

        // percurso da lista de adjacências de cada vértice
        for(itAdj = adj.begin(); itAdj != adj.end(); itAdj++){
            
            // se o nome do vértice a ser adicionado é igual ao nome de um vértice adjacente, incrementamos o grau de entrada do vértice que está sendo atualizado
            if(itAdj->getNome() == v.getNome()){
                v.incGrauEntrada();
                break;
            }
        }
    }
}

/*Método responsável por adicionar um vértice ordenadamente à lista de vértices do grafo, com base no campo nome
    Lembrando que cada um dos vértices terá uma lista de vértices adjacentes
        Parâmetros: Vertice v
        Retorno: nenhum
*/  
void Grafo::addVertice(const Vertice &v){

    // nome do elemento relacionado ao vertice adjacente na aresta
    Elemento elementoInsert = v.returnElemento();
    std::string nomeInsert = v.getNome();
    
    // se a lista está vazia, somente adicionamos o elemento associado ao vértice adjacente
    if(_vertices.size() == 0){ 
        _vertices.insert(_vertices.begin(), v);
        _numVertices++; // atualiza o número de vértices
    }

    // se a lista não está vazia, percorremos a lista de vértices para inserir o novo vértice de forma ordenada
    else{
        // iterators para possibilitarem o percurso pela lista
        std::list<Vertice>::iterator it = _vertices.begin();
        std::list<Vertice>::iterator itProx = _vertices.begin();

        // se o vértice adicionado é o menor da lista, adicionamos ele no início da lista
        if(elementoInsert.getNome().compare(it->getNome()) <= 0){
            _vertices.insert(it, Vertice(v));
            _numVertices++; // atualiza o número de vértices
            return;
        }
        
        // nomes relacionados aos elementos indicados pelo iterator
        std::string nome, nomeProx;

        // itProx indica o próximo elemento após o indicado por it 
        itProx++;

        // Enquanto o iterator it não chega ao final da lista, percorremos a lista de adjacências
        while(it != _vertices.end()){
            
            // nome relacionado ao elemento indicado pelo iterator
            nome = it->getNome();

            // se o iterator itProx chegar ao final da lista, adicionamos o elemento de acordo com sua ordem alfabética
            if(itProx == _vertices.end()){
                
                // caso o nome do elemento a ser inserido seja maior ou igual ao nome do elemento indicado por it, inserimos o elemento ao final da lista
                if(nome.compare(nomeInsert) <= 0) 
                    _vertices.push_back(Vertice(v));

                // caso contrário, inserimos o elemento antes do elemento indicado por it
                else 
                    _vertices.insert(it, Vertice(v));

                break; // sai do loop, pois a inserção  está concluída
            }
            
            // nome relacionado ao próximo elemento
            nomeProx = itProx->getNome();

            // caso o elemento a ser inserido seja maior que o indicado por it e menor q o elemento indicado por itPox 
            if(nome.compare(nomeInsert) <= 0 && nomeProx.compare(nomeInsert) >= 0){
                
                // adicionamos novo elemento entre it e itPox
                _vertices.insert(itProx,Vertice(v));
                
                break; // sai do loop, pois a inserção concluída
            }

            it++;
            itProx++;
        }

        _numVertices++; // atualiza o número de vértices
    }
}

/*Método responsável por buscar um vértice entre os vértices já adicionados no grafo
    Essa função utiliza o campo nome do elemento referente ao vértice procurado para encontrá-lo
        Parâmetros: string nome 
        Retorno: iterator para o vértice procurado
*/
std::list<Vertice>::iterator Grafo::buscaVertice(const std::string &nome){

    // Iterator começa no primeiro elemento da lista
    std::list<Vertice>::iterator it = _vertices.begin();

    // Enquanto não chegar ao final da lista, procura vértice com nome igual ao passado como parâmetro
    for(it; it != _vertices.end(); it++){
        if(it->getNome() == nome){
            return it;
        }
    }

    // Caso não encontre o vértice, retorna um iterator para o final da lista
    return it;
}

/*Método responsável por acessar um vértice _vertices[i] da lista de vértices através do índice i
    Parâmetros: índice i
    Retorno: iterator para o vértice _vertices[i]
*/
std::list<Vertice>::iterator Grafo::acessaVertice(int i){
    
    // iterator para percorrer a lista de vértices
    std::list<Vertice>::iterator it = _vertices.begin();

    // percurso da lista de vértices até o índice i
    for(int j=0; j<i; j++){
        it++;
    }

    // retorna iterator para o vértice _vertices[i]
    return it;
}

/*Método responsável por adicionar uma aresta no grafo ligando o vértice v1 ao vértice v2
    Parâmetros:
        ->itVerticeSaida: iterator para vértice de saída
        ->itVerticeEntrada: iterator para vértice de entrada
        ->regAux: registro com informações do vértice de saída e vértice de entrada
    Retorno: nenhum
*/
void Grafo::addAresta(std::list<Vertice>::iterator itVerticeSaida, 
std::list<Vertice>::iterator itVerticeEntrada, registro regAux){

    // flag para verificar se há elemento adjacente de fato para que a aresta exista
    if(regAux.alimento == "" || regAux.populacao == -1){
        return; // não há elemento adjacente ou o peso da aresta é inválido, logo não há aresta
    }

    // Cria-se novo elemento adjacente com campo _nome igual ao campo alimento do registro
    Elemento elementoAdj(regAux.alimento);
    
    
    // se o vertice de saída não existe, criamos um novo vértice no grafo
    if(itVerticeSaida == _vertices.end())
    {
        // Cria-se novo vertice com base no registro e com grau = 0
        Vertice novoVertice(Elemento(regAux),0,0);

        // Atualiza vértice para que grau de entrada esteja correto
        atualizaVertice(novoVertice);

        // Elemento adjacente é adicionado na lista de adjacências
        novoVertice.addAdj(elementoAdj, regAux.populacao);
        novoVertice.incGrauSaida();

        // Verifica se vértices de Saída e Entrada são iguais
        if(novoVertice.getNome() == elementoAdj.getNome()){
            novoVertice.incGrauEntrada();
        }

        // Adiciona-se o novo vértice à lista de vértices do grafo
        addVertice(novoVertice);

    }

    // Se já existe um vértice de saída já existe, incrementamos o grau de saída desse vértice e adicionamos o adjacente a sua lista de adjacências
    else{   
        // Elemento adjacente é adicionado na lista de adjacências
        itVerticeSaida->addAdj(elementoAdj, regAux.populacao);
        itVerticeSaida->incGrauSaida();
        
    }
    
    // Se já existe um vértice no grafo relacionado ao elemento adjacente, incrementamos o grau de entrada desse vértice
    if(itVerticeEntrada != _vertices.end()){
        itVerticeEntrada->incGrauEntrada();
        _numArestas++; // reajuste do número de arestas
    }
}


/*Método de impressão do grafo (seus vértices e respectivas listas de adjacências)
        Parâmetros: nenhum
        Retorno: nenhum
*/
void Grafo::imprimeGrafo()                                 
{
    std::list<Vertice>::const_iterator it = _vertices.cbegin();
    for(it; it != _vertices.cend(); it++)
    {
        it->imprimeVertice();
    }
}

// Operador de atribuição do grafo
Grafo& Grafo::operator=(const Grafo &g){
    (*this)._vertices =  g.returnVertices();
    (*this)._numVertices = g.returnNumVertices();
    (*this)._numArestas = g.returnNumArestas();
    return *this;
}



/*-----------------------------------Funções auxiliares do grafo-------------------------------------   */

/*Funçaõ responsável por criar um grafo com base em um arquivo aberto
    Parâmetros: 
        ->FILE* fp: ponteiro para arquivo binário
    Retorno: Grafo criado
*/
Grafo criaGrafo(FILE* fp){

    int flag= 0;                                    // flag para verificar se houve erro na leitura do registro

    std::list<Vertice>::iterator itVerticeSaida;    // iterator para vértice de saída
    std::list<Vertice>::iterator itVerticeEntrada;  // iterator para vértice de entrada
    
    // Iniciação do grafo
    Grafo grafo = Grafo();                     
    
    // Leitura de registros do arquivo e adição de vértices ao grafo com base em dados dos registros
    fseek(fp, TAM_PAG, SEEK_SET);               // posicionamento do ponteiro para o primeiro registro
    registro regAux = le_reg_bin(fp, &flag);     // leitura do primeiro registro
    
    while(flag != ERRO){                       // enquanto houver registros

        if(regAux.removido == '0'){             // se o registro foi não removido logicamente, iniciamos a adição de vértices e arestas
            // Busca vértice de saída no grafo
            itVerticeSaida = grafo.buscaVertice(regAux.nome);

            // Busca vértice de entrada no grafo
            itVerticeEntrada = grafo.buscaVertice(regAux.alimento);

            // cria aresta que vai do vértico com campo nome igual ao campo nome do registro ao vértice com campo nome igual campo alimento do registro
            grafo.addAresta(itVerticeSaida, itVerticeEntrada, regAux);
        }

        // Leitura do próximo registro
        regAux = le_reg_bin(fp, &flag);
    }
    
    // Retorna o grafo criado
    return grafo;
}

/*Função responsável por imprimir o vértice de um grafo e os vértices aos quais ele é adjacente
    Parâmetros: 
        ->&grafo: grafo onde supostamente está o vértice
        ->&nome: nome do vértice 
    Retorno: nenhum
*/
void imprimeAdjacencias(grafos::Grafo &grafo, const std::string &nome){

    // booleano para indicar que foi encontrado algum vértice adjacente e que o elemento adjacente existe
    bool encontrado = false;
    
    // Lista de nomes dos vértices a serem impresos e iterator para essa lista
    std::list<std::string> nomesPrint;
    std::list<std::string>::iterator itNomesPrint;

    // Lista de vértices do grafo
    std::list<Vertice> vertices = grafo.returnVertices();
    
    // Lista de adjacências de um vértice
    std::list<Elemento> adj;

    //  Iterator para passar pelos vértices do grafo
    std::list<Vertice>::iterator itVertice = vertices.begin();

    //  Iterator para passar pelos elementos da lista de adjacências de um vértice
    std::list<Elemento>::iterator itAdj;

    while(itVertice != vertices.end()){

        // Obtem a lista de adjacências do vértice
        adj = itVertice->returnAdj();

        // Verifica se o vértice possui adjacências e se não possui, passa para o próximo vértice
        if(adj.size() <= 0){
            itVertice++;
            continue;
        }

        // Procura na lista de adjacências do vértice elemento com nome igual ao passado como parâmetro
        for(itAdj = adj.begin(); itAdj != adj.end(); itAdj++){
            
            if(itAdj->getNome() == nome){

                // Adiciona o nome do vértice adjacente à lista de nomes a serem impressos
                nomesPrint.push_back(itVertice->getNome());
                
                // Indica que foi encontrado um vértice ao qual o elemento é adjacente
                encontrado = true;
                
                // sai do laço
                break;
            }
        }

        // Passa para o próximo vértice
        itVertice++;
    }

    // Mensagem de erro caso não haja vértices adjacentes ao vértice com nome passado como parâmetro
    if(!encontrado){
        msg_reg_inexistente();
        std::cout << std::endl;
        return;
    }

    // Impressão do nome do vértice passado como parâmetro
    std::cout << nome << ":";
    

    // Impressão dos nomes associadosvértices encontrados
    for(itNomesPrint = nomesPrint.begin(); itNomesPrint != nomesPrint.end(); itNomesPrint++){
        
        // Iterator passa para o contânier da frente para verificar se o vértice é o último da lista de impressão
        itNomesPrint++;

        // Impressão dos vértices antes do último
        if(itNomesPrint != nomesPrint.end()){
            
            itNomesPrint--;
            std::cout << " " << *itNomesPrint << ",";
        }
        
        // Impressão do último vértice ao qual o elemento é adjacente
        else{
            
            itNomesPrint--;
            std::cout << " " << *itNomesPrint << std::endl << std::endl;
        }
    }

    // Limpeza da lista de vértices a serem impressos
    nomesPrint.clear();
}

/*Função responsável por imprimir a mensagem certa sobre a conectividade do grafo*/
void msgFortementeConexo(bool fortementeConexo, int qntComponentes){
    if(fortementeConexo){
        std::cout << "Sim, o grafo é fortemente conexo e possui " << qntComponentes << " componentes." <<std::endl;
    }
    else{
        std::cout << "Não, o grafo não é fortemente conexo e possui " << qntComponentes <<" componentes." <<std::endl;
    }
}

/*Funçaõ responsável por criar um grafo com base em um arquivo aberto
    Parâmetros: 
        ->FILE* fp: ponteiro para arquivo binário
    Retorno: Grafo criado
*/
Grafo criaGrafo_sunlight(FILE* fp){

    int flag= 0;                                    // flag para verificar se houve erro na leitura do registro

    std::list<Vertice>::iterator itVerticeSaida;    // iterator para vértice de saída
    std::list<Vertice>::iterator itVerticeEntrada;  // iterator para vértice de entrada
    
    // Iniciação do grafo
    Grafo grafo = Grafo();                     
    
    // Leitura de registros do arquivo e adição de vértices ao grafo com base em dados dos registros
    fseek(fp, TAM_PAG, SEEK_SET);               // posicionamento do ponteiro para o primeiro registro
    registro regAux = le_reg_bin(fp, &flag);     // leitura do primeiro registro
    
    bool primeira = true;                        // flag para criar sunlight apenas uma vez

    while(flag != ERRO){                       // enquanto houver registros

        if(regAux.removido == '0'){             // se o registro foi não removido logicamente, iniciamos a adição de vértices e arestas
            
            // Busca vértice de saída no grafo
            itVerticeSaida = grafo.buscaVertice(regAux.nome);

            // verifica o caso "sunlight"
            if(strcmp(regAux.alimento, "sunlight") == 0 && primeira)
            {
                primeira = false;

                // registro auxiliar para adicionar "sunlight" no grafo
                registro auxiliar_reg;
                auxiliar_reg.removido = '0';
                auxiliar_reg.encadeamento = -1;
                auxiliar_reg.tamanho = -1;
                auxiliar_reg.unidadeMedida = '0';
                auxiliar_reg.velocidade = -1;
                auxiliar_reg.populacao = INT_MAX;
                strcpy(auxiliar_reg.especie, "");
                strcpy(auxiliar_reg.habitat, "");
                strcpy(auxiliar_reg.tipo, "");
                strcpy(auxiliar_reg.dieta, "");

                // Cria-se novo vertice com base no registro e com grau = 0
                Vertice novoVertice(Elemento(auxiliar_reg),0,0);

                // Atualiza vértice para que grau de entrada esteja correto
                grafo.atualizaVertice(novoVertice);

                // Adiciona-se o novo vértice à lista de vértices do grafo
                auto iter = grafo.buscaVertice("");
                grafo.addAresta(iter, iter, auxiliar_reg);
            }


            // Busca vértice de entrada no grafo
            itVerticeEntrada = grafo.buscaVertice(regAux.alimento);

            // cria aresta que vai do vértico com campo nome igual ao campo nome do registro ao vértice com campo nome igual campo alimento do registro
            grafo.addAresta(itVerticeSaida, itVerticeEntrada, regAux);
        }

        // Leitura do próximo registro
        regAux = le_reg_bin(fp, &flag);
    }
    
    // Retorna o grafo criado
    return grafo;
}
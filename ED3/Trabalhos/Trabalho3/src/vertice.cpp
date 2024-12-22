#include "vertice.hpp"

using namespace vertices;


///////// Métodos da classe Vertice /////////

// Construtor padrão
Vertice::Vertice(): Elemento(), _grauEntrada(0), _grauSaida(0), _cor(BRANCO), _distancia(INT_MAX){}


// Construtor
Vertice::Vertice(const Elemento &elemento, int grauSaida, int grauEntrada): 
Elemento(elemento), _grauSaida(grauSaida), _grauEntrada(grauEntrada), _cor(BRANCO), 
_distancia(INT_MAX){}

// Construtor por cópia
Vertice::Vertice(const Vertice &v): Elemento(v.returnElemento()), _adj(v.returnAdj()), _pesos(v.returnPesos()),
_grauSaida(v.returnGrauSaida()), _grauEntrada(v.returnGrauEntrada()), _cor(v.returnCor()), _distancia(v.returnDistancia()) {}

/*Método responsável por retornar elemento associado ao vértice (dinossauro no caso dessa implementação)
        Parâmetros: nenhum
        Retorno: Elemento associado ao vértice
*/
Elemento Vertice::returnElemento() const{
    return Elemento(getNome(), getEspecie(), getHabitat(), getTipo(), getDieta(), getAlimento(), getPopulacao());
}

/*Método responsável por retornar a lista de adjacências de um vértice
        Parâmetros: nenhum
        Retorno: lista de adjacências do vértice
*/
std::list<Elemento> Vertice::returnAdj() const{
    return _adj;
}

/*Método responsável por retornar a lista de pesos das adjacências de um vértice
        Parâmetros: nenhum
        Retorno: lista de pesos adjacências do vértice
*/
std::list<int> Vertice::returnPesos() const{
    return _pesos;
}

/*Método responsável por retornar o grau de saída de um vértice
        Parâmetros: nenhum
        Retorno: grau de saída do vértice
*/
int Vertice::returnGrauSaida() const{
    return _grauSaida;
}

/*Método responsável por retornar o grau de entrada de um vértice
        Parâmetros: nenhum
        Retorno: grau de entrada do vértice
*/
int Vertice::returnGrauEntrada() const{
    return _grauEntrada;
}

/*Método responsável por retornar a cor de um vértice
        Parâmetros: nenhum
        Retorno: cor do vértice
*/
int Vertice::returnCor() const{
    return _cor;
}

/*Método responsável por retornar a distância de um vértice em relação a um vértice de origem
        Parâmetros: nenhum
        Retorno: distância do vértice em relação a um vértice de origem
*/
int Vertice::returnDistancia() const{
    return _distancia;
}


/*Método responsável por incrementar o grau de saída de um vértice
        Parâmetros: nenhum
        Retorno: nenhum
*/
void Vertice::incGrauSaida(){
    _grauSaida++;
}

/*Método responsável por incrementar o grau de entrada de um vértice
        Parâmetros: nenhum
        Retorno: nenhum
*/
void Vertice::incGrauEntrada(){
    _grauEntrada++;
}


/*Método responsável por adicionar um vértice v à lista de adjacências de um vértice
    No caso dessa implementação, na prática será inserido na lista o elemento associado ao vértice v
        Parâmetros: v - vértice a ser adicionado à lista de adjacências
        Retorno: nenhum
*/
void Vertice::addAdj(Elemento &elementoInsert, int peso){

    // nome do elemento relacionado ao vertice adjacente na aresta
    std::string nomeInsert = elementoInsert.getNome();
    if(DEBUG) std::cout << "Nome a ser inserido em _adj: " << nomeInsert << std::endl;
    
    // iterators para possibilitarem o percurso pela lista de adjacências
    std::list<Elemento>::iterator itAdj = _adj.begin();
    std::list<Elemento>::iterator itAdjProx = _adj.begin();

    // iterator ára percorrer a lista de pesos associados às adjacências
    std::list<int>::iterator itPesos = _pesos.begin();
    std::list<int>::iterator itPesosProx = _pesos.begin();
    
    // nomes relacionados aos elementos indicados pelo iterator
    std::string nome, nomeProx;

    // se a lista está vazia, somente adicionamos o elemento associado ao vértice adjacente
    if(_adj.size() == 0){ 
        _adj.insert(_adj.begin(),elementoInsert);
        _pesos.insert(_pesos.begin(),peso);
    }

    // se a lista não está vazia, percorremos a lista de adjacências para inserir o novo elemento de forma ordenada
    else{
        
        // se o elemento adicionado é o menor da lista de adjacências, adicionamos ele no início da lista
        if(nomeInsert.compare(itAdj->getNome()) <= 0){
            _adj.insert(itAdj, elementoInsert);
            _pesos.insert(itPesos, peso);
            return;
        }

        // itProx indica o próximo elemento após o indicado por it 
        itAdjProx++;

        // itPesosProx indica o próximo elemento após o indicado por itPesos
        itPesosProx++;

        // Enquanto o iterator it não chega ao final da lista, percorremos a lista de adjacências
        while(itAdj != _adj.end()){
            
            // nome relacionado ao elemento indicado pelo iterator
            nome = itAdj->getNome();

            // se o iterator itProx chegar ao final da lista, adicionamos o elemento de acordo com sua ordem alfabética
            if(itAdjProx == _adj.end()){
                
                // caso o nome do elemento a ser inserido seja maior ou igual ao nome do elemento indicado por it, inserimos o elemento ao final da lista
                if(nome.compare(nomeInsert) <= 0){ 
                    _adj.push_back(elementoInsert);
                    _pesos.push_back(peso);
                }

                // caso contrário, inserimos o elemento antes do elemento indicado por it
                else{ 
                    _adj.insert(itAdj, elementoInsert);
                    _pesos.insert(itPesos, peso);
                }

                break; // sai do loop, pois a inserção  está concluída
            }
            
            // nome relacionado ao próximo elemento
            nomeProx = itAdjProx->getNome();

            // caso o elemento a ser inserido seja maior que o indicado por it e menor q o elemento indicado por itPox 
            if(nome.compare(nomeInsert) <= 0 && nomeProx.compare(nomeInsert) >= 0){
                
                // adicionamos novo elemento entre it e itPox
                _adj.insert(itAdjProx,elementoInsert);
                _pesos.insert(itPesosProx, peso);
                
                break; // sai do loop, pois a inserção concluída
            }

            // Incremento dos iterators da lista de adjacências
            itAdj++;
            itAdjProx++;

            // Incremento dos iterators da lista de pesos
            itPesos++;
            itPesosProx++;
        }
    }
}

/*Método responsável por modificar a cor de um vértice
        Parâmetros: cor (inteiro que representa a cor do vértice) - BRANCO(0), CINZA(1) ou PRETO(2)
        Retorno: nenhum
*/
void Vertice::setCor(int cor){
    _cor = cor;
}

/*Método responsável por modificar a distância de um vértice em relação a um vértice de origem
        Parâmetros: distância (inteiro que representa a distância do vértice em relação a um vértice de origem)
        Retorno: nenhum
*/
void Vertice::setDistancia(long distancia){
    _distancia = distancia;
}


/*Método responsável por buscar um elemento na lista de adjacências de um vértice
    Essa função utiliza o campo nome do elemento referente ao vértice procurado para encontrá-lo
        Parâmetros: string nome 
        Retorno: elemento procurado
*/
std::list<Elemento>::iterator Vertice::buscaAdj(const std::string &nome){
    
    // Iterator começa no primeiro elemento da lista
    std::list<Elemento>::iterator it = _adj.begin();

    // Enquanto não chegar ao final da lista, procura vértice com nome igual ao passado como parâmetro
    for(it; it != _adj.end(); it++){
        if(it->getNome() == nome){
            return it;
        }
    }

    // Caso não encontre o elemento retorna iterator para final da lista de adjacências
    return it;
}

/*Método de impressão de um vértice*/
void Vertice::imprimeVertice() const{

    // iterators para percorrer a lista de adjacências e lista de pesos
    std::list<Elemento>::const_iterator it = _adj.cbegin();
    std::list<int>::const_iterator itPesos = _pesos.cbegin();

    // percurso da lista de adjacências e pesos fazendo as impressões
    for(; it != _adj.cend(); it++, itPesos++){
        
        // Impressão dos dados do vértice de saída
        std::cout << getNome() << " ";
        std::cout << getEspecie() << " ";
        std::cout << getHabitat() << " ";
        std::cout << getDieta() << " ";
        std::cout << getTipo() << " ";
        std::cout << returnGrauEntrada() << " ";
        std::cout << returnGrauSaida() << " ";
        std::cout << returnGrauEntrada() + returnGrauSaida() << " ";
        
        // Impressão dos dados do elemento adjacente (vértice de entrada)
        std::cout << it->getNome() << " " << *itPesos << std::endl;
    }

}
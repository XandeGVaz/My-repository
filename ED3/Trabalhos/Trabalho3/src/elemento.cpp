#include "elemento.hpp"

using namespace elementos;

///////// Métodos da classe Elemento ////////////////////////////////////////////////////////////////

// Construtor padrão
Elemento::Elemento(): _nome("NULO"), _especie("NULO"), _habitat("NULO"), 
_tipo("NULO"), _dieta("NULO"), _alimento("NULO"), _populacao(0){} 

// Construtor por parâmetos diretos
Elemento::Elemento(const std::string &nome, const std::string &especie, const std::string &habitat, const std::string &tipo, 
const std::string &dieta , const std::string &alimento , int populacao ){
    _nome = nome;
    _especie = especie;
    _habitat = habitat;
    _tipo = tipo;
    _dieta = dieta;
    _alimento = alimento;
    _populacao = populacao;
}

// Construtor por registro
Elemento::Elemento(registro reg){
    _nome = reg.nome;
    _especie = reg.especie;
    _habitat = reg.habitat;
    _tipo = reg.tipo;
    _dieta = reg.dieta;
    _alimento = reg.alimento;
    _populacao = reg.populacao;
}

// Construtor por nome
Elemento::Elemento(const std::string &Nome): _nome(Nome), _especie("NULO"), _habitat("NULO"), 
_tipo("NULO"), _dieta("NULO"), _alimento("NULO"), _populacao(0){} 

// Construtor por cópia
Elemento::Elemento(const Elemento &elemento){
    _nome = elemento.getNome();
    _especie = elemento.getEspecie();
    _habitat = elemento.getHabitat();
    _tipo = elemento.getTipo();
    _dieta = elemento.getDieta();
    _alimento = elemento.getAlimento();
    _populacao = elemento.getPopulacao();
}


std::string Elemento::getNome() const{
    return _nome;
}

std::string Elemento::getEspecie() const{
    return _especie;
}

std::string Elemento::getHabitat() const{
    return _habitat;
}

std::string Elemento::getDieta() const{
    return _dieta;
}

std::string Elemento::getTipo() const{
    return _tipo;
}

std::string Elemento::getAlimento() const{
    return _alimento;
}

int Elemento::getPopulacao() const{
    return _populacao;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <string>
#include <regex>

class Pessoa{

    std::string _nome;                      // nome da pessoa
    int _idade;                             // idade da pessoa
    std::string _cidade, _estado, _pais;    // localidade da pessoa

public:

    Pessoa(std::string entrada){

        // Definição dos padrões de regex para encontrar nome, idade e localidade na entrada
        std::regex nomePad(R"(([A-Za-zÀ-ÖØ-öø-ÿ\s.]+)\stem)"), // nome entre começo da string e " tem", contando acentos
        idadePad(R"((\d+)\sanos)"), // idade antes de " anos"
        cidadePad(R"(mora\sem\s([A-Za-zÀ-ÖØ-öø-ÿ\s]+)-)"),  // cidade entre "mora em " e " -" contando acentos
        estadoPad(R"(-([A-Z]{2}),)"), // estado entre " -" e ", ", só contando letras maiúsculas
        paisPad(R"(,\s([A-Za-zÀ-ÖØ-öø-ÿ\s]+))"); // país entre ", " e o final da string, contando acentos

        // Definição de variáveis para armazenar as strings encontradas com a função regex_search
        std::smatch nomeMatch, idadeMatch, cidadeMatch, estadoMatch, paisMatch;

        // Procura padrões de regex na entrada e atribui os valores encontrados aos atributos da classe
        std::regex_search(entrada.cbegin(), entrada.cend(), nomeMatch, nomePad);
        _nome = nomeMatch[1].str();
        
        std::regex_search(entrada.cbegin(), entrada.cend(), idadeMatch, idadePad);
        _idade = std::stoi(idadeMatch[1].str());
        
        std::regex_search(entrada.cbegin(), entrada.cend(), cidadeMatch, cidadePad);
        _cidade = cidadeMatch[1].str();
        
        std::regex_search(entrada.cbegin(), entrada.cend(), estadoMatch, estadoPad);
        _estado = estadoMatch[1].str();
        
        std::regex_search(entrada.cbegin(), entrada.cend(), paisMatch, paisPad);
        _pais = paisMatch[1].str();     
    }

    // Função amiga para impressão dos dados da pessoa
    friend std::ostream& operator<<(std::ostream &out, const Pessoa &p){

        // Impressão dos dados da pessoa
        out << p._nome << std::endl << p._idade << std::endl; 
        out << p._cidade << std::endl << p._estado << std::endl << p._pais << std::endl;

        // Retorn ostream& com os dados a serem impressos
        return out;
    }

};
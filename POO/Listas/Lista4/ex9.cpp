/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <vector>
#include <regex>
#include <string>

std::vector<double> notas(std::string s){

    // Vetor de notas
    std::vector<double> nota;

    // Cria um padrão regex para achar notas (double)
    std::regex padrao(R"(\d+(\.\d+)?)");

    // Cria um conjunto de matches para armaenar os valores encontrados
    std::smatch encontrados;

    // Iterator para percorrer string
    std::string::const_iterator it = s.cbegin();

    // Enquanto encontrar valores double de notas
    while(std::regex_search(it, s.cend(), encontrados, padrao)){
        
        // Adiciona elemento encontrado no vetor
        nota.push_back(std::stod(encontrados[0].str()));

        // Atualiza posição do iterator para pŕoximo encontrado
        it = encontrados.suffix().first;
    }

    // retorna vetor de notas
    return nota;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <vector>
#include <string>
#include <algorithm>
#include <regex>


// Função de comparação para possibilitar a ordenação das versões
bool func(std::string a, std::string b){

    // Variáveis para armazenar os números inteiros das versões entre os pontos
    int numA, numB;

    // Iteradores para as strings
    std::string::const_iterator itA = a.cbegin(), itB = b.cbegin();

    // Padrão para indentificar dígitos das verões entre os pontos
    std::regex padrao(R"(\d+)"); // nesse caso, somente o número que irá "escapar"

    // Conjunto de matches para armazenar os valores encontrados
    std::smatch encontA, encontB;

    // Enquanto o padrão for encontrado em ambas as strings
    while(std::regex_search(itA, a.cend(), encontA, padrao) 
     && std::regex_search(itB, b.cend(), encontB, padrao)){

        // Conversão de dígitos encontrados para inteiros
        numA = std::stoi(encontA[0].str());
        numB = std::stoi(encontB[0].str());

        // Verifica se números de versão são diferentes até então e se forem, verifica qual é o menor
        if(numA != numB) return numA < numB;

        // Atualização da posição dos iterators para permitiir continuação da busca do padrão
        itA = encontA.suffix().first;
        itB = encontB.suffix().first;
    }

    // Se as strings forem iguais até o final da menor, a menor é a que tem menor tamanho
    return a.size() < b.size();

}

// Função que ordena um vetor de strings de versões
void ordena_versoes(std::vector<std::string> &versoes){
    
    // Ordena o vetor de versões
    std::sort(versoes.begin(), versoes.end(), func);
}

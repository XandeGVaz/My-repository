/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// Função que compara duas strings
bool func(std::string str1, std::string str2){
    
    // Se as strings tiverem o mesmo tamanho, compara as strings (considerando o conteúdo)
    if(str1.size() == str2.size())
        return( str1.compare(str2) > 0);

    // Se as strings tiverem tamanhos diferentes, compara os tamanhos
    return(str1.size() < str2.size());

}

// Função que ordena um vetor de strings
void ordena_strings(std::vector<std::string>& vetor){
    
    // Ordena o vetor de strings de acordo com a função de comparação func
    std::sort(vetor.begin(), vetor.end(), func);
}
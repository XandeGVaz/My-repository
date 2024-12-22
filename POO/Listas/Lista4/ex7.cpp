/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <regex>

std::string retira(std::string texto, char c){

    // Cria um padrão regex para o caractere c a ser removido
    std::regex pattern(std::string(1, c));

    // Substitui o padrão criado por uma string vazia
    std::string result = std::regex_replace(texto, pattern, "");

    // Retorna a string resultado do regex
    return result;

}

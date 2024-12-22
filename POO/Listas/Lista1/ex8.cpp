/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>
#include <string>
#include <fstream>


std::string conteudo(std::string nome);

std::string conteudo(std::string nome){

    std::fstream file (nome.data());

    std::string conteudo, aux;

    while(getline(file,aux)){
        conteudo.append(aux);
        conteudo.append("\n");
    }

    file.close();

    return conteudo;
}
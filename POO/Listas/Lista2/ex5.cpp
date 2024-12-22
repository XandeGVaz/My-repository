/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <fstream>
#include <string>

class Arquivo{

    std::fstream _conteudo;

public:

    Arquivo(std::string arquivo): _conteudo(arquivo){}

    std::string proxima_linha(){
        std::string content;
        getline(_conteudo, content);
        return content;
    }

    ~Arquivo(){
        _conteudo.close();
    }

};

// estava dando erro de compilação após uma certa data
int main() {
    Arquivo a("/tmp/arquivo.txt");
    std::cout << a.proxima_linha() << std::endl;
    std::cout << a.proxima_linha() << std::endl;
    return 0;
}
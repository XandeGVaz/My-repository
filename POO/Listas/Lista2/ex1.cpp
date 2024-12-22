/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>

class Televisao {
    bool _ligada;
    int _canal;

public:
    
    /*Modo de inicialização que define (ao mesmo tempo):
        -> Uma inicialização padrão
        -> Uma inicialização com parâmetros escolhidos pelo usuário
    */
    Televisao (bool ligada = false, int canal =1){  
        _ligada = ligada; 
        _canal = canal; 
    }

    void liga(){
        _ligada = true;
    }

    void desliga(){
        _ligada = false;
    }

    void canal_cima(){
        if(_ligada){
            _canal++;
        }
    }

    void canal_baixo(){
        if(_ligada){
            _canal--;
        }
    }

    friend std::ostream& operator <<(std::ostream &out, const Televisao &TV){
        if(TV._ligada)
            out << "(" << "ligada, " << TV._canal << ")";
        else
            out << "(" << "desligada, " << TV._canal << ")";
        return out;
    }

};

int main(){
    Televisao tv;
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;
    tv.canal_baixo();
    std::cout << tv << std::endl;
    tv.liga();
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;
    tv.canal_baixo();
    std::cout << tv << std::endl;
    tv.desliga();
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;
    return 0;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>

float retorna_preco(int qnt, float preco){
    return (float) ( (qnt)  *  (preco) );
}

int main(){

    int balas, choc; //quantidade de balas e chocolates
    float val_balas, val_choc, total; //valor das balas e chocolates (1 unidade)

    std::cin >> balas >> val_balas >> choc >> val_choc; //leituras
    total = retorna_preco(balas, val_balas) + retorna_preco(choc, val_choc); //obtém resultado

    std::cout << total;
}
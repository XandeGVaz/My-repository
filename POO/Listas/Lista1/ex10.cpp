/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>
#include <iomanip>

const double unTroco [] = {200.00, 100.00, 50.00, 20.00, 10.00, 5.00, 2.00, 1.00, 0.50, 0.25, 0.10, 0.05, 0.01};

int encontra_maior(int *troco_rest, int unidadeTrocoAtual){
    int qnt = 0;
    int aux = *troco_rest;

    while(aux > 0){
        aux -= unidadeTrocoAtual;
        if(aux>=0) qnt++;
    }

    *troco_rest -= ( qnt * unidadeTrocoAtual); 

    return qnt;     
}

void troco_guloso(double preco, double recebido){
    int i = 0, j=0;
    int precoInt = 1000 * preco;
    int recebidoInt = 1000 * recebido;
    int trocoInt;
    int aux;

    int *qnt = (int*)calloc(13, sizeof(int));

    trocoInt = recebidoInt - precoInt;
 
    while(trocoInt > 0 && i < 13){
        aux = 1000 * unTroco[i];
        qnt[i] = encontra_maior(&trocoInt, aux);
        i++;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Troco: R$ " << recebido - preco << std::endl;

    for(j; j<13; j++){
        if(j < i){
            std::cout << qnt[j] << " de R$ " <<  unTroco[j] << std::endl;
        }
        else{
            std::cout << "0 de R$ " <<  unTroco[j] << std::endl;
        }
    }

    return;
}

int main(){
    double valor, recebido;
    
    std::cin >> valor;
    std:: cin >> recebido;

    troco_guloso(valor, recebido);
    
    return 0;
}

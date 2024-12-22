/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <stack>
#include <queue>
#include <stdio.h>

#define DEBUG 1

int main(){

    // Declaração das estruturas de dados
    std::stack<int> pilha;
    std::queue<int> fila;
    std::priority_queue<int> filaDePrioridade;

    // Declaração de variáveis para leitura
    char comando[4];
    std::string aux;
    int n = 0;

    // Declaração de variáveis para verificação
    bool pilhaR = true, filaR = true, filaDePrioridadeR = true; 
    int result = 0;

    // Enquanto houver leitura
    while(scanf("%s",comando)!=EOF){

        scanf("%d", &n);
        
        // Verifica se o comando é pop
        aux = comando;
        if(aux.compare("pop") == 0){

            // Verifica se o elemento retirado é igual ao topo da pilha, fila e fila de prioridade
            if(n != pilha.top()) pilhaR = false;
            if(n != fila.front()) filaR = false;
            if(n != filaDePrioridade.top()) filaDePrioridadeR = false;

            // Retira o elemento das estruturas
            pilha.pop(); fila.pop(); filaDePrioridade.pop();
        }

        // Se o comando for add, adiciona o elemento nas estruturas
        else { pilha.push(n); fila.push(n); filaDePrioridade.push(n); }
    }

    // Definição do resultado numericamente
    if(pilhaR) result += 1;
    if(filaR) result += 3;
    if(filaDePrioridadeR) result += 5;

    // Impressão do resultado
    if(result == 0) std::cout << "none" << std::endl;
    else if(result == 1) std::cout << "stack" << std::endl;
    else if(result == 3) std::cout << "queue" << std::endl;
    else if(result == 5) std::cout << "priority" << std::endl;
    else std::cout << "both" << std::endl;

}
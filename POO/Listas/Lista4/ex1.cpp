/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <stack>
#include <iostream>


int elementok(std::stack<int> pilhas, int k){

    // erro de passagem de k == 0
    if(k == 0) return -1;

    // Cópia da pilha
    std::stack<int> copia = pilhas;

    // Contador do número de números pares
    int cont = 0;

    while(!copia.empty()){
        
        // Se for par aumenta números de elementos pares
        if(copia.top() % 2 == 0) cont++;
        
        // Se o número de pares for igual a k 
        if(cont == k) return copia.top();
        
        // Retira elemento do topo da pilha
        copia.pop();
    }

    // Se o número de pares for menor que k, retorna-se -1
    return -1;

}
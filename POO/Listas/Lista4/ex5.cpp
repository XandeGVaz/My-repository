/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <map>

// Definição do tipo Matriz
typedef std::map<std::pair<int,int>, int> Matriz;

// Função que soma duas matrizes
Matriz soma(const Matriz& A, const Matriz& B){
    
    // Declaração de iterador auxiliar da matriz
    Matriz::iterator itAux;

    // Declaração da matriz resultante
    Matriz R;
    
    // Adiciona os elementos da matriz A na matriz resultante
    for(auto x: A){
        R[x.first] = x.second;
    }

    // Somando os elementos da matriz B na matriz resultante
    for(auto y: B){

        // Procura o elemento correspondente na matriz resultante
        itAux = R.find(y.first);

        // Se o elemento existir, soma os valores
        if(itAux != R.end() && itAux->first != std::pair(-1,-1))
            R[y.first] += y.second;
        
        // Se o elemento não existir, adiciona o elemento na matriz resultante
        else
            R[y.first] = y.second;
    }

    return R;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <vector>
#include <algorithm>

typedef std::vector< std::vector<int> > Matriz;

int num_pares(std::vector<int> v){
    
    // Contador de números pares
    int cont  = 0;
    
    // Percorre o vetor e incrementa o contador se o número for par
    for(auto x : v){ if(x % 2 == 0) cont++; }

    // Retorna a quantidade de números pares
    return cont;
}

bool func(std::vector<int> v1, std::vector<int> v2){

    // Se a quantidade de pares for igual, compara lexicograficamente os vetorers
    if(num_pares(v1) == num_pares(v2)){
        return std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
    }

    // Se a quantidade de pares for diferente, compara a quantidade de pares
    return num_pares(v1) < num_pares(v2);
}

void ordena_par(Matriz& M){

    // Ordena as linhas da matriz de acordo com a função de comparação criada
    std::sort(M.begin(), M.end(), func);
}
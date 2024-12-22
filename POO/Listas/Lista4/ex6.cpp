/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <vector>
#include <set>

// Função que retira um número de um vetor e retorna vetor crescente
std::vector<int> retira(std::vector<int> v, int n){
    
    // Vetorresultante
    std::vector<int> result;

    // set para introduzir os números ordenadamente e sem repetições
    std::set<int> st;

    // Insere as chaves do vetor no conjunto
    // obs: para um conjunto "set" a inserção já ocorre ordenada e sem repetições
    for(auto x : v){
        st.insert(x); 
    }
    
    // Retira o número n do conjunto
    st.erase(n);

    // Copia set para vetor resultante
    for(auto z : st){
        result.push_back(z);
    }

    // Retorna o vetor resultante
    return result;
}
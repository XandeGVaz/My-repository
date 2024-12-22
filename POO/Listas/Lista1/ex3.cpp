/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>

int main(){
    int N;
    int i=0;
    std::cin >> N;
    while(i<(2*N)){
        std::cout << i << ", ";
        i++;
    }
    std::cout << i;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>
#include <iomanip>
#include <math.h>

typedef struct{
    double x;
    double y;
} ponto;

double distance(ponto P1, ponto P2){
    return sqrt( pow( (P1.x-P2.x) , 2 ) + pow( (P1.y-P2.y) , 2) );
}

int main(){
    ponto P1, P2;
    std::cin >> P1.x >> P1.y >> P2.x >> P2.y;
    std::cout << std::fixed << std::setprecision(4) << distance(P1,P2);
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>
#define mmc 19635

int main(){
    int n;
    int num=mmc;
    std::cin >> n ;
    if(n>=mmc){
        while(num<=n){
            std::cout << num << std::endl;
            num+=(mmc);
        }
    }
}
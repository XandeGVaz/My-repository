
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>

int pow(int b, int e, int m){
    int val = b;

    for(int i=0; i < (e - 1); i++){
        val *= b;
    }

    return(val%m);
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <iostream>

int seq(int n, int k, int *ini);

int seq(int n, int k, int *ini){
    int result=0;
    if(n<k){
        result = ini[n];
    }
    else{
        for(int i=n-k; i<n; i++) result+=seq(i,k,ini)*seq(i,k,ini);
    }
    return result;
}
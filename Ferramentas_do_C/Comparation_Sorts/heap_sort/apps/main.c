#include <stdio.h>
#include <stdlib.h>
#include "heap_sort.h"



int main(){
    type_data A[]={9,8,3,4,5,1,0,7,2,6};
    heap_sort(A,10);
    for(int i=0;i<10;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    return(0);
}
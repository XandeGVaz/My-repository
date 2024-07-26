#include <stdio.h>
#include <stdlib.h>
#include "shell_sort.h"

int main(){
    type_data A[]={9,8,3,4,5,12,1,0,11,7,2,6,10};
    shell_sort(A,13);
    for(int i=0;i<13;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    return(0);
}
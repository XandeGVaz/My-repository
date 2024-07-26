#include "selection_sort.h"



int main(){
    int size=13;
    type_data A[]={9,8,3,10,4,5,1,11,0,13,7,2,6};
    selection_sort(A,size);
    for(int i=0;i<size;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    return(0);
}
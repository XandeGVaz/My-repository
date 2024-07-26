#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){

    int flag=1;
    List *L=List_create();
    float n;
    while(flag){
        scanf("%f",&n);
        if(n>-1000){
            List_add_wage(L,n);
        }
        else{
            flag=0;
            continue;
        }
    }
    List_print(L);
    L=Return_inverted_list(L);
    L=ReturnList_whitout_repetitive_nodes(L);
    List_print(L);
    return(0);
}

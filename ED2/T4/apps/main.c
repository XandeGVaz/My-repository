#include "aux.h"
#include "knap_sack.h"

int main(){

    int P,Q;
    int d_valt,g_valt;

    ldata* l=NULL;
    ldata* ld=NULL;
    ldata* lg=NULL;

    scanf("%d %d",&P,&Q);

    l=create_list(Q);
    inptdata_list(l,Q);

    ld=KNPS_dinamic(P,Q,l);
    lg=KNPS_greedy(P,Q,l);
    printdata_list(ld);
    invprintdata_list(lg);

    d_valt=totalval_list(ld);
    g_valt=totalval_list(lg);
    printf("%d %d\n",d_valt,g_valt);
    printf("%.2f\n",(float)100*g_valt/d_valt);
}

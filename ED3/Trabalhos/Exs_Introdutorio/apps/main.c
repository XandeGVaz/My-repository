// Primeiro Exercício Prático - main.c
/*Alunos:
 *Vitor Alexandre Garcia Vaz(14611432)
 *Vitor Pardini Saconi(14611800)
*/

#include "biblioteca.h"
#include "funcoesFornecidas.h"

FILE* arq;
int Comando;
char ArqNome[10];

int main(){
    setlocale(LC_ALL, "Portuguese"); //adição de acentos
    int n = 0;
    int RRN = 0;
    int ID = 0, qntInfo = 0;

    scanf("%d %s",&Comando, ArqNome);
    switch(Comando){
        case 1:
            scanf("%d",&n);
            adicionar_especies(arq,ArqNome,n);
            binarioNaTela(ArqNome);
            break;
        case 2:
            recuperar_especies(arq, ArqNome);
            break;
        case 3:
            scanf("%d", &RRN);
            RRN *= REG_TAM;     // o RRN recebe o byte offset do registro pedido
            recuperar_RRN(arq,ArqNome,RRN);
            break;
        case 4:
            scanf("%d %d",&ID, &qntInfo);
            completar_especie(arq, ArqNome, qntInfo, ID);
            binarioNaTela(ArqNome);
            break;
    }

    return 0;
}

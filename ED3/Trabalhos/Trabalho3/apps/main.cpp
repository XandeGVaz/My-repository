// Trabalho 3 de Estrutura de Dados
/*Alunos:
 *Vitor Alexandre Garcia Vaz(14611432) - 100%
 *Vitor Pardini Saconi(14611800) - 100%
*/

// Bibliotecas elaboradas pelo grupos testão em funcionalidades.hpp
#include "funcionalidades.hpp"

int main()
{
    // Configuração de localização e possibilidade de uso de acentos
    setlocale(LC_ALL, "Portuguese");

    int i;
    scanf("%d", &i);
    if(i == 10)
    {
        funcionalidade10();
    }
    else if(i == 11)
    {
        funcionalidade11();
    }
    else if(i == 12)
    {
        funcionalidade12();
    }
    else if(i == 13)
    {
        funcionalidade13();
    }
    else if(i == 14)
    {
        funcionalidade14();
    }

    return 0;

}

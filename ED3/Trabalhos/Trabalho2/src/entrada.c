#include "entrada.h"

//Função ue lê um dado inteiro, de um registro, passado por referência
void entrada_regInt(int *reg_int)
{
    char aux[40];
    scan_quote_string(aux);
    if( strcmp(aux, "") != 0)
        *reg_int = atoi(aux);
    else
        *reg_int = -1;
    return ;
}

//Funçãoq ue lê um dado float, de um registro, passado por referência
void entrada_regFloat(float *reg_float)
{
    char aux[40];
    scan_quote_string(aux);
    if( strcmp(aux, "") != 0)
        *reg_float = atof(aux);
    else
        *reg_float = -1.0;
        
    return ;
}

//Funçãoq ue lê uma string, de um registro, passada por referência
void entrada_regString(char* reg_str)
{
    scan_quote_string(reg_str);
    return ;
}

/*Função responsável pela entrada dos campos de um registro pelo usuário
    Retorno: um registro com os campos lidos na entrada
*/
registro entrada_reg()
{
    registro reg;
    char aux[12];

    //Definição de dados sobre a remoção
    reg.removido='0';
    reg.encadeamento = -1;

    // Entrada de dados
    entrada_regString(reg.nome);
    entrada_regString(reg.dieta);
    entrada_regString(reg.habitat);
    entrada_regInt(&reg.populacao);
    entrada_regString(reg.tipo);
    entrada_regInt(&reg.velocidade);
    scan_quote_string(aux);
    if(strcmp(aux, "") != 0)                        // Unidade de medida recebe '$' ao invés de ""
        reg.unidadeMedida = aux[0];
    else
        reg.unidadeMedida = '$';
                
    entrada_regFloat(&reg.tamanho);
    entrada_regString(reg.especie);
    entrada_regString(reg.alimento);

    return reg;                                     // Retorna registro lido
}


// -------------------------------------------------------- TRABALHO 2 ---------------------------------------------------------------------------------- //

/*Função responsável por receber do usuário o valor de um campo a ser procurado para insercao/impressao
    Parâmetros: nao tem
    Retorna: valor do campo nome 
*/
long entrada_chave_ind(){
    char campo[30];
    char valor[30];

    scanf("%s", campo);             // leitura de tipo de campo que será lido

    scan_quote_string(valor);       // leitura do campo nome (necessario para essa implementacao)

    if(strcmp(campo,"nome")!=0)        // verifica se tipo do campo a ser lido (!= nome)
        return -1; 

    return(converteNome(valor));    // retorno do inteiro (long) correspondente ao valor do campo
}
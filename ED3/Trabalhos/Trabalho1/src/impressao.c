#include "impressao.h"


void msg_erro_padrao()
{
    printf("Falha no processamento do arquivo.\n");
}

void msg_reg_inexistente()
{
    printf("Registro inexistente.\n");
}

void msg_erro_insercao()
{
    printf("Falha ao inserir registro(s)\n");
}

void msg_erro_remocao(){
    printf("Falha ao remover registro(s)\n");
}


/*  Funcao para imprimir os campos de um registro na tela*/
void imprime_registro_tela(registro reg_aux)
{
    char unit[5] = "";        // unidade de velocidade
    char t[5] = "m/h";

    printf("Nome: %s\n",reg_aux.nome);
    printf("Especie: %s\n",reg_aux.especie);
    if(strcmp(reg_aux.tipo,""))
        printf("Tipo: %s\n",reg_aux.tipo);
    printf("Dieta: %s\n",reg_aux.dieta);
    if(strcmp(reg_aux.habitat,""))
        printf("Lugar que habitava: %s\n",reg_aux.habitat);
    if(reg_aux.tamanho != -1.0)
        printf("Tamanho: %.1f m\n",reg_aux.tamanho);
    if(reg_aux.velocidade != -1 && reg_aux.unidadeMedida != '$'){
        unit[0] = reg_aux.unidadeMedida;
        strcat(unit,t);
        printf("Velocidade: %d %s\n",reg_aux.velocidade,unit);
    }
    printf("\n");
}

/*  Funcao para imprimir todos os campos de um cabecalho na tela*/
void imprime_cabecalho_tela(cabecalho cab_aux)
{
    printf("\n\n");
    printf("Status: %c\n", cab_aux.status);
    printf("Topo: %d\n", cab_aux.topo);
    printf("proxRRN: %d\n", cab_aux.proxRRN);
    printf("nroRegRem: %d\n", cab_aux.nroRegRem);
    printf("nroPagDisco: %d\n", cab_aux.nroPagDisco);
    printf("qttCompacta: %d\n", cab_aux.qttCompacta);
    printf("\n\n");
}

/*  Funcao que le um arquivo BIN e imprime os registros na tela
    > Parametros: nome_bin (nome do arquivo BIN a ser lido)
    > Retorno: 0 (foi possivel ler os dados e imprimi-los com exito)
               -1 (houve erro de leitura)
               -2 (nao ha registros no arquivo BIN)
*/
int imprime_bin(char* nome_bin)
{
    int f = OK;                                  // f: verificador de erro
    cabecalho cab_aux;
    registro reg_aux;
    FILE *fp = fopen(nome_bin,"rb");
    if(fp == NULL)
    {
        return (-1);
    }

    cab_aux = le_cab_bin(fp, &f);                                            // le o cabecalho
    if(f == ERRO)                                                            // erro na leitura do cabecalho
    {
        fclose(fp);
        return (-1);
    }
    if(cab_aux.status == '0')                                                // arquivo inconsistente
    {
        fclose(fp);
        return (-1);
    }

    if(feof(fp))                                                             // nao ha registros
    {
        fclose(fp);
        return (-2);
    }

    while(1)                                                                // le e imprime os registros
    {
        reg_aux = le_reg_bin(fp, &f);
        if(f == ERRO)                                                       // erro de leitura
            break;
        if(reg_aux.removido != '1')                                         // verificar se esta logicamente removido
            imprime_registro_tela(reg_aux);
    }
    printf("Numero de paginas de disco: %d\n",cab_aux.nroPagDisco);
    printf("\n");

    fclose(fp);
    return 0;
}
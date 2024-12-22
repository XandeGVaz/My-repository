#include "busca.h"

/*  Funcao que busca registros de um binario pelo valor de um campo do tipo string
    > Parametros: nome_bin (nome do arquivo BIN a ser lido)
                  nome_campo  (nome do campo de interesse)
                  valor_campo (valor do campo procurado)
                  mode (1 para imprimir registro e 0 para remover registro)
    > Retorno:  qtd (busca bem sucedida, retorna a quantidade de arquivos encontrados)
                -2(falha na abertura de arquivo)
*/
int busca_bin_string(char *nome_bin, char *nome_campo, char* valor_campo, int mode)
{
    int f = OK;                                 // f: verificador de erro
    FILE *fp = fopen(nome_bin,"rb+");
    if(fp == NULL)
        return -2;
    cabecalho cab_aux;
    registro reg_aux;
    int qtd = 0, aux;                           // qtd: quantos arquivos correspondem a busca

    cab_aux = le_cab_bin(fp, &f);
    if(f == ERRO)                               // erro na leitura do cabecalho
    {
        fclose(fp);
        return -1;
    }
    if(cab_aux.status == '0'){                    // o arquivo esta inconsistente
        fclose(fp);
        return -1;
    }
    if(feof(fp)){                               // nao ha registros no arquivo
        fclose(fp);
        return -1;
    }

    aux = 0;                                    // contador do RRN

    if(!strcmp(nome_campo,"nome"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.nome))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"especie"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.especie))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"habitat"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.habitat))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"tipo"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.tipo))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"dieta"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.dieta))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"alimento"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(!strcmp(valor_campo,reg_aux.alimento))
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }

    fclose(fp);
    return qtd;
}


/*  Funcao que busca registros de um binario pelo valor de um campo do tipo int
    > Parametros: nome_bin (nome do arquivo BIN a ser lido)
                  nome_campo  (nome do campo de interesse)
                  valor_campo (valor do campo procurado)
                  mode (1 para imprimir registro e 0 para remover registro)
    > Retorno: 0 (busca bem sucedida)
                -2(falha na abertura de arquivo)
*/
int busca_bin_int(char *nome_bin, char *nome_campo, int valor_campo, int mode)
{
    int f = OK;                                 // f: verificador de erro
    FILE *fp = fopen(nome_bin,"rb+");
    if(fp == NULL)
        return -2;
    cabecalho cab_aux;
    registro reg_aux;
    int qtd = 0, aux;                           // qtd: quantos arquivos correspondem a busca

    cab_aux = le_cab_bin(fp, &f);
    if(f == ERRO)                               // erro na leitura do cabecalho
    {
        fclose(fp);
        return -1;
    }
    if(cab_aux.status == '0'){                    // o arquivo esta inconsistente
        fclose(fp);
        return -1;
    }
    if(feof(fp)){                               // nao ha registros no arquivo
        fclose(fp);
        return -1;
    }

    aux = 0;                                    // contador do RRN

    if(!strcmp(nome_campo,"populacao"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(valor_campo == reg_aux.populacao)
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }
    else if(!strcmp(nome_campo,"velocidade"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(valor_campo == reg_aux.velocidade)
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }

    fclose(fp);

    return qtd;
}


/*  Funcao que busca registros de um binario pelo valor de um campo do tipo float
    > Parametros: nome_bin (nome do arquivo BIN a ser lido)
                  nome_campo  (nome do campo de interesse)
                  valor_campo (valor do campo procurado)
                  mode (1 para imprimir registro e 0 para remover registro)
    > Retorno: 0 (busca bem sucedida)
                -2(falha na abertura de arquivo)
*/
int busca_bin_float(char *nome_bin, char *nome_campo, float valor_campo, int mode)
{
    int f = OK;                                 // f: verificador de erro
    FILE *fp = fopen(nome_bin,"rb+");
    if(fp == NULL)
        return -2;
    cabecalho cab_aux;
    registro reg_aux;
    int qtd = 0, aux;                           // qtd: quantos arquivos correspondem a busca

    cab_aux = le_cab_bin(fp, &f);
    if(f == ERRO)                               // erro na leitura do cabecalho
    {
        fclose(fp);
        return -1;
    }
    if(cab_aux.status == '0'){                    // o arquivo esta inconsistente
        fclose(fp);
        return -1;
    }
    if(feof(fp)){                               // nao ha registros no arquivo
        fclose(fp);
        return -1;
    }

    aux = 0;                                    // contador do RRN

    if(!strcmp(nome_campo,"tamanho"))
    {
        while(1)
        {
            reg_aux = le_reg_bin(fp,&f);
            if(f == ERRO)                           // erro de leitura
                break;
            if(reg_aux.removido != '1')             // confere se nao foi removido
            {
                if(valor_campo == reg_aux.tamanho)
                {
                    if(mode)                               // imprime RRN quando mode == 1
                        imprime_registro_tela(reg_aux);
                    else                                   // remove quando RRN quando mode == 0
                        remove_reg_bin(fp, aux);
                    qtd++;
                }
            }
            aux++;
        }
    }

    fclose(fp);

    return qtd;
}
#include "funcionalidades.h"

void funcionalidade1()
{
    char in[50], out[50];
    scanf("%s",in);
    scanf("%s",out);
    if(cria_bin(in,out) == 0)
        binarioNaTela(out);
}

void funcionalidade2()
{
    char arq[50];
    int k;
    scanf("%s",arq);
    k = imprime_bin(arq);
    if(k == -1)
        msg_erro_padrao();
    else if(k == -2)
        msg_reg_inexistente();

}

void funcionalidade3()
{
    char arq[50], nome_campo[50], valor_str[50];
    int n, k, j = 1, mode = 1, valor_int;                  // mode == 1 (impressao dos registros)
    float valor_float;
    cabecalho cab_aux;
    scanf("%s %d",arq,&n);                                 // ler o nome do .bin e quantas vezes executar a busca
    FILE *fp = fopen(arq,"rb");
    if(fp == NULL)
    {
        msg_erro_padrao();
        n = 0;
    }
    cab_aux = le_cab_bin(fp,&k);
    if(k == ERRO)
    {
        msg_erro_padrao();
        n = 0;
    }
    fclose(fp);

    while(n!=0)
    {
        scanf("%s", nome_campo);
        // verificar se o campo tem valor int, float ou string
        if(!strcmp(nome_campo, "populacao") || !strcmp(nome_campo, "velocidade"))         // campo INT
        {
            entrada_regInt(&valor_int);
            printf("Busca %d\n", j);
            k = busca_bin_int(arq,nome_campo,valor_int,mode);
        }
        else if(!strcmp(nome_campo, "tamanho"))                                         // campo FLOAT
        {
            entrada_regFloat(&valor_float);
            printf("Busca %d\n", j);
            k = busca_bin_float(arq,nome_campo,valor_float,mode);
        }
        else                                                                            // campo STRING
        {
            entrada_regString(valor_str);
            printf("Busca %d\n", j);
            k = busca_bin_string(arq,nome_campo,valor_str,mode);
        }

        if(k == -2)                                                                     // caso haja algum erro
            msg_erro_padrao();

        if(k == 0)
        {
            msg_reg_inexistente();
            printf("\n");
        }
        j++;
        n--;
        printf("Numero de paginas de disco: %d\n\n",cab_aux.nroPagDisco);
    }
}

void funcionalidade4()
{
    char arq[50];
    int n, k;
    scanf("%s %d",arq, &n);
    k = remove_nreg_bin(arq, n);
    if(k==0)
        binarioNaTela(arq);
    if(k==-2)
        msg_erro_padrao();
}

void funcionalidade5()
{
    char arq[50];
    int n, k;
    scanf("%s %d",arq, &n);
    k = insere_nreg_bin(arq, n);
    if(k==0)
        binarioNaTela(arq);
    if(k==-2 || k==-1)
        msg_erro_padrao();

}

void funcionalidade6()
{
    char arq[50];
    int k;
    scanf("%s",arq);
    k = compacta_bin(arq);
    if(k==0)
        binarioNaTela(arq);
    if(k==-1 || k==-2)
        msg_erro_padrao();

}
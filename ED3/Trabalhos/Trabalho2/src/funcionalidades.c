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

void funcionalidade7()
{
    int k;
    char arq_in[50], arq_out[50];
    
    // leitura dos nomes dos arquivos de entrada(registros) e de saída (árvore B)
    scanf("%s",arq_in);
    scanf("%s", arq_out);

    k = cria_arquivo_ArvoreB(arq_in, arq_out);  // criação da árvore B com base no arquivo de registros

    if(k==0)                                    // sem ocorrência de erros
        binarioNaTela(arq_out);
    if(k==-1)                                   // com ocorrência de erros
        msg_erro_padrao();
        
}

void funcionalidade8()
{
    char arq_dados[50], arq_ind[50];   // strings para leitura dos nomes dos arquivos de dados e indice

    int flag;              // flag para verificar possiveis erros

    indCabecalho indCab;   // cabecalho do arquivo de indice para possibilitar busca
    long val;              // valor long que servira de chave para busca
    int indRRN;            // RRN do nodo do indice onde encontramos a chave com valor val
    long Pr;               // ponteiro de referencia para o arquivo original, do dado encontrado na busca

    registro reg;          // registro indexado que sera lido

    scanf("%s %s", arq_dados, arq_ind);     // entrada do nome dos arquivos

    // abertura dos arquivos de dados e de indice sobre esses dados
    FILE* arqDados = fopen(arq_dados, "rb");
    FILE* arqInd = fopen(arq_ind, "rb");

    val = entrada_chave_ind();              // usuario fornece o tipo de campo e o seu valor, que e transformado para long

    if(arqDados == NULL || arqInd == NULL){ // verificacao de possiveis erros na abertura dos arquivos
        msg_erro_padrao();
        return;
    }

    if(val != -1){
        
        indCab = le_cab_ind(arqInd, &flag);                         // leitura de cabecalho
        
        indRRN = busca_arvoreB(arqInd, indCab, val, NULL, NULL);    // busca de chave de valor "val" na arvore B

        Pr = busca_em_nodo(arqInd, indRRN, val);                    // busca de referencia (byte-offset) para registro, do arquivo de dados, indexado
        if(Pr == -2) 
            msg_erro_padrao();
        else if(Pr == -1) 
            msg_reg_inexistente();                                 
        
        else 
        {
            fseek(arqDados, Pr, SEEK_SET);                          // seta ponteiro nesse byte-offset
            reg = le_reg_bin(arqDados, &flag);                      // leitura de registro indexado

            if(reg.removido == '1')                                 // verificacao se foi logicamente removido
                msg_reg_inexistente();
            else
                imprime_registro_tela(reg);                         // impressao do registro encontrado
        }
    }

    // fechamennto dos arquivos abertos para busca
    fclose(arqInd);
    fclose(arqDados);
}

void funcionalidade9()
{
    char arq_dados[50], arq_arvore[50];
    int n, k;
    scanf("%s %s %d",arq_dados, arq_arvore, &n);
    k = insere_nreg_ambos(arq_dados, arq_arvore, n);
    if(k==0)
        binarioNaTela(arq_arvore);
    if(k==-2 || k==-1)
        msg_erro_padrao();

}
#include "leitura.h"

/*  Funcao que le o cabecalho de um arquivo BIN e retorna os dados lidos
    > Parametros: ptr_arq (ponteiro para o arquivo a ser lido)
                  f (verificador de exito)
    > Retorno: cab_aux (cabecalho com os dados lidos)
*/
cabecalho le_cab_bin(FILE *ptr_arq, int *f)
{
    fseek(ptr_arq,0,SEEK_SET);                                  // garantir que está no inicio (permite uso na compactação)

    cabecalho cab_aux;
    // LER OS CAMPOS
    if(fread(&cab_aux.status,sizeof(char),1,ptr_arq) <= 0)      // erro de leitura
    {
        *f = ERRO;
        return cab_aux;
    }
    fread(&cab_aux.topo,sizeof(int),1,ptr_arq);
    fread(&cab_aux.proxRRN,sizeof(int),1,ptr_arq);
    fread(&cab_aux.nroRegRem,sizeof(int),1,ptr_arq);
    fread(&cab_aux.nroPagDisco,sizeof(int),1,ptr_arq);
    fread(&cab_aux.qttCompacta,sizeof(int),1,ptr_arq);

    // IGNORAR O LIXO
    fseek(ptr_arq,1600,SEEK_SET);

    *f = 1;                                                     // flag indica êxito

    return cab_aux;
}

/*  Funcao que le um registro de um arquivo BIN e retorna os dados lidos
    > Parametros: ptr_arq (ponteiro para o arquivo a ser lido)
                  f (verificador de exito)
    > Retorno: reg_aux (registro com os dados lidos)
*/
registro le_reg_bin(FILE *ptr_arq, int *f)
{
    int n = 0;
    char str_aux[200], aux[100];
    registro reg_aux;
    // LER CAMPOS FIXOS
    if(fread(&reg_aux.removido,sizeof(char),1,ptr_arq) <= 0){   // erro, esta no fim do arquivo
        *f = ERRO;
        return reg_aux;
    }
    if(reg_aux.removido == '1'){                            // caso esteja logicamente removido

        // retorna registro com indicar de remoção e encadeamento
        fread(&reg_aux.encadeamento,sizeof(int),1,ptr_arq);

        fread(str_aux,sizeof(char),155,ptr_arq);            // ignora todos os demais campos
        return reg_aux;
    }

    fread(&reg_aux.encadeamento,sizeof(int),1,ptr_arq);
    fread(&reg_aux.populacao,sizeof(int),1,ptr_arq);
    fread(&reg_aux.tamanho,sizeof(float),1,ptr_arq);
    fread(&reg_aux.unidadeMedida,sizeof(char),1,ptr_arq);
    fread(&reg_aux.velocidade,sizeof(int),1,ptr_arq);

    // LER CAMPOS VARIAVEIS
    fread(str_aux,sizeof(char),142,ptr_arq);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo NOME
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.nome, aux);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo ESPECIE
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.especie, aux);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo HABITAT
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.habitat, aux);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo TIPO
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.tipo, aux);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo DIETA
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.dieta, aux);

    if(sscanf(&str_aux[n],"%[^#]",aux) == 0)          // ler o campo ALIMENTO
        strcpy(aux,"");
    if(!strcmp(aux,""))                         // campo vazio
        n++;
    else                                        // pula para o proximo campo
        n += (strlen(aux) + 1);
    strcpy(reg_aux.alimento, aux);

    *f = 1;                                                     // flag indica êxito

    return reg_aux;
}

/*Funcao que le um registro de um arquivo .bin, na posição indicada por um RRN, e o retorna
    Parametros: 
        -> ptr_arq (ponteiro para o arquivo a ser lido)
        -> *f (poneteiro para flag) : *f==1 (êxito), f*==ERRO (erro)
        ->RRN: posição relativa do registro que será escrito
    Retorno: reg_aux (registro com os dados lidos)
*/
registro le_reg_RRN(FILE *ptr_arq, int* f, int RRN)
{   
    int flag;                                              // flag
    registro reg_aux;

    // Seta ponteiro na posição correspondente ao RRN
    const int pos = TAM_PAG + RRN*TAM_REG; 
    fseek(ptr_arq, pos, SEEK_SET);

    reg_aux = le_reg_bin(ptr_arq, &flag);                   // lê registro da posição desejada 
    *f = flag;                                              // atualiza flag de confirmação de leitura

    return reg_aux;
}

/*  Funcao que le 10 campos (uma linha) do .csv e retorna um registro com os dados lidos
    > Parametros: ptr_arq  (ponteiro para o arquivo CSV de entrada)
                  first == (1 se a funcao vai ler a primeira linha do csv, 0 caso contrario)
    > Retorno: registro com os dados lidos
*/
registro le_campos_csv(FILE *ptr_arq, int first)
{
    char aux[160], p;
    int t = -1;
    registro reg_aux;

    for(int n = 0; n != 9; n++)
    {
        t = fscanf(ptr_arq,"%[^,]",aux);        // le um campo
        if(t <= 0)                              // o campo lido esta vazio
            strcpy(aux,"");
        fscanf(ptr_arq,"%c", &p);               // ignora a virgula de separacao

        if(!first)                              // caso estejamos lendo a primeira linha, nao salvamos...
        {
            if(n == 0){                         // nome ( string )
                strcpy(reg_aux.nome, aux);
            } else if(n == 1){                  // dieta ( string )
                strcpy(reg_aux.dieta, aux);
            } else if(n == 2){                  // habitat ( string )
                strcpy(reg_aux.habitat, aux);
            } else if(n == 3){                  // populacao ( int )
                if(!strcmp(aux,""))
                    reg_aux.populacao = -1;     // caso seja NULO
                else
                    reg_aux.populacao = atoi(aux);

            } else if(n == 4){                  // tipo ( string )
                strcpy(reg_aux.tipo, aux);
            } else if(n == 5){                  // velocidade ( int )
                if(!strcmp(aux,""))
                    reg_aux.velocidade = -1;    // caso seja NULO
                else
                    reg_aux.velocidade = atoi(aux);

            } else if(n == 6){                  // unidadeMedida ( char )
                if(!strcmp(aux,""))             // caso seja NULO
                    reg_aux.unidadeMedida = '$';
                else
                    reg_aux.unidadeMedida = aux[0];
            } else if(n == 7){                  // tamanho ( float )
                if(!strcmp(aux,""))
                    reg_aux.tamanho = -1.0;    // caso seja NULO
                else
                    reg_aux.tamanho = atof(aux);

            } else if(n == 8){                  // especie ( string )
                strcpy(reg_aux.especie, aux);
            }
        }
    }
    t = fscanf(ptr_arq,"%[^\n]",aux);           // le o ultimo campo de uma linha (terminado em \n)
    if(t <= 0)                                  // o campo lido esta vazio
        strcpy(aux,"");
    fscanf(ptr_arq,"%c", &p);                   // ignora o \n de separacao

    for(int k=0;k<strlen(aux)+1;k++)            // retirar "caracteres invisiveis"
    {
        if(aux[k] == '\n' || aux[k] == '\r')
        {
            aux[k] = '\0';
            break;
        }
    }

    if(!first)                                  // caso estejamos lendo a primeira linha, nao salvamos...
    {
        strcpy(reg_aux.alimento, aux);          // alimento
        reg_aux.encadeamento = -1;              // ainda nao ha um prox. logicamente removido
        reg_aux.removido = '0';                 // o registro nao esta removido
    }

    return reg_aux;
}
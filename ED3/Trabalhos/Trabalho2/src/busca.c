#include "busca.h"
#include "impressao.h"
#include "manipBin.h"
#include "indice.h"

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

/*Função responsável pela busca de uma chave na arvore binaria
    Tem como funcao retornar o RRN do nodo onde esta ou deveria estar a chave procurada
    Parametros:
        ->arq: ponteiro para arquivo da arvore binaria
        ->cab: cabecalho do arquivo da arvore binaria
        ->val: valor da chave a ser procurada na arvore bianria
        ->RRN_lista: lista de RRNs percorridos durante a busca
        ->tamLista: ponteiro para numero de elementos da lista de RRNs
    Retorna:
        --> RRN: numero relativo do nodo onde deveria estar a chave procurada
        -> -1: caso a arvore esteja vazia
        -> -2: caso tenha havido erro na leitura de um dos nos da arvore 
*/
int busca_arvoreB(FILE* arq, indCabecalho cab, long val, int *RRN_lista, int *tamLista){

    int flag = 1;                                   // flag usada para verificar leitura de nodos
    int RRN = 0;                                    // RRN do nodo onde esta ou deveria estar o nodo procurado
    int RRN_origem = 0;                             // referente nodo que contem o ponteiro para o RRN 
    int cont = 0;                                   // contador para lista de RRNs

    indNodo nodoAux;                                // nodo auxiliar para receber nodos lidos

    if(cab.noRaiz == -1){                           // verifica se arvore B esta vazia
        return -1;
    }

    RRN = cab.noRaiz;                               // no raiz sendo verificado como primeiro RRN

    while(1)
    {

        if(RRN == -1){                              // verifica se nao chegou ao final da arvore B
            return RRN_origem;                      // se sim retorna no folha lido anteriormente
        }

        fseek(arq, (RRN+1)*TAM_INDPAG, SEEK_SET);   // ponteiro recebe endereço do RRN atual de procura

        if(RRN_lista!=NULL) RRN_lista[cont] = RRN;  // atualiza lista de RRNs percorridos
        if(tamLista!=NULL) *tamLista = cont+1;      // atualiza tamanho da lista de RRNs a ser retornado por referência

        nodoAux = le_nodo_ind(arq, &flag);          // leitura de nodo do RRN atual
        if(flag == ERRO){                           // verificacao de erro na leitura
            return -2;
        }

        int k = nodoAux.nroChavesNo;                // salva numero de chaves no nodo

        // se valor procurado < C1
        if(val < nodoAux.C[0])
        {
            RRN_origem = RRN;              // atualizacao do RRN de origem
            RRN = nodoAux.P[0];            // RRN = P1 : atualizacao do RRN atual com o ponteiro onde podemos encontrar o valor buscado
            cont++;                        // atualiza contador de RRNs percorridos
            continue;
        }

        // se valor procurado == C1
        if(val == nodoAux.C[0]) return RRN;

        // se valor procurado > Ck
        if(val > nodoAux.C[k-1])
        {   
            RRN_origem = RRN;             // atualizacao do RRN de origem
            RRN = nodoAux.P[k];           // atualizacao do RRN atual com o último ponteiro posterior a ultima chave nao nula
            cont++;                       // atualiza contador de RRNs percorridos
            continue;
        }

        // se valor procurado estivesse entre C1 e Ck
        for(int i = 0; i<k-1; i++){

            // retorna RRN desse nodo se val == C[X] 
            if(val == nodoAux.C[i+1]) return RRN;

            if(val > nodoAux.C[i] && val < nodoAux.C[i+1])
            {  
                RRN_origem = RRN;          // atualizacao do RRN de origem
                RRN = nodoAux.P[i+1];      // atualizacao do RRN atual com o ponteiro onde podemos encontral o valor buscado
                cont++;                    // atualiza contador de RRNs percorridos
                break;
            }
        }

    }
}

/*Funçao responsável por buscar, em um nodo, uma chave especifica e retornar a referencia para registro indexado por essa chave
    Parametros:
        ->arq: ponteiro para arquivo arvore B(indice)
        ->noRRN: RRN do nodo onde procuraremos a chave
        ->val: valor da chave que sera procurada na arvore B
    Retorna:
        ->Pr_n: ponteiro de referência (byte-offset) do registro indexado  
        ->-2: caso aconteca erro na leitura do nodo
        ->-1: caso a chave nao seja encontrada no nodo
*/
long busca_em_nodo(FILE *arq, int noRRN, long val){
    int flag;                                           // flag para verificar possiveis erros na leitura
    indNodo nodoAux;

    fseek(arq, (noRRN+1)*TAM_INDPAG, SEEK_SET);         // setagem de ponteiro no byte-offset do nodo

    nodoAux = le_nodo_ind(arq, &flag);                  // leitura do nodo onde havera procura
    if(flag == ERRO){                                   // verifica erro em leitura
        return -2;
    }
    
    // loop de busca da chave
    for(int i = 0; i < nodoAux.nroChavesNo; i++){
        if(nodoAux.C[i] == val) return nodoAux.Pr[i];   // se encontrada retorna referencia para registro
    }

    return -1;                                          // se nao encontrada retorna -1
}
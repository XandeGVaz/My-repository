#include "manipBin.h"

/*  Funcao que escreve um registro no arquivo .bin
    > Parametros: fp (ponteiro para o .bin)
                  reg (registro a ser escrito)
    > Retorno: 0 (foi possivel escrever os dados no .bin com exito)
               -1 (houve erro de escrita)
*/
int escreve_reg_bin(FILE *fp, registro reg)
{
    int n = 18, k = 0;                              // n : tamanho do registro (inicio com 18, que sao os campos de tam. fixo)
    char delim = '#', lixo = '$';
    // TAM. FIXO
    if(fwrite(&reg.removido,sizeof(char),1,fp) <= 0) return (-1);        // removido
    if(fwrite(&reg.encadeamento,sizeof(int),1,fp) <= 0) return (-1);     // encadeamento
    if(fwrite(&reg.populacao,sizeof(int),1,fp) <= 0) return (-1);        // populacao
    if(fwrite(&reg.tamanho,sizeof(float),1,fp) <= 0) return (-1);        // tamanho
    if(fwrite(&reg.unidadeMedida,sizeof(char),1,fp) <= 0) return (-1);   // unidadeMedida
    if(fwrite(&reg.velocidade,sizeof(int),1,fp) <= 0) return (-1);       // velocidade

    // TAM. VARIAVEL
    k = strlen(reg.nome);                                                // nome : nao nulo
    if(fwrite(reg.nome,sizeof(char),k,fp) <= 0) return (-1);
    if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);               // delimitador
    n += ++k;

    if(!strcmp(reg.especie,"")){                                         // especie : não pode ser nulo (mas aconteceu nos casos teste)
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n++;
    }
    else{
        k = strlen(reg.especie);
        if(fwrite(reg.especie,sizeof(char),k,fp) <= 0) return (-1);
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n += ++k;
    }

    if(!strcmp(reg.habitat,"")){                                         // habitat : pode ser nulo
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n++;
    }
    else{
        k = strlen(reg.habitat);
        if(fwrite(reg.habitat,sizeof(char),k,fp) <= 0) return (-1);
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n += ++k;
    }

    if(!strcmp(reg.tipo,"")){                                            // tipo : pode ser nulo
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n++;
    }
    else{
        k = strlen(reg.tipo);
        if(fwrite(reg.tipo,sizeof(char),k,fp) <= 0) return (-1);
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n += ++k;
    }

    if(!strcmp(reg.tipo,"")){                                            // dieta : nao deveria ser nulo, MAS...
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n++;
    }
    else{
        k = strlen(reg.dieta);
        if(fwrite(reg.dieta,sizeof(char),k,fp) <= 0) return (-1);
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n += ++k;
    }

    if(!strcmp(reg.alimento,"")){                                        // alimento : pode ser nulo
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n++;
    }
    else{
        k = strlen(reg.alimento);
        if(fwrite(reg.alimento,sizeof(char),k,fp) <= 0) return (-1);
        if(fwrite(&delim,sizeof(char),1,fp) <= 0) return (-1);           // delimitador
        n += ++k;
    }

    n = TAM_REG - n;                                                     // espacos a serem preenchidos
    for(; n!=0; n--)
    {
        if(fwrite(&lixo,sizeof(char),1,fp) <= 0) return (-1);
    }

    return 0;
}

/*  Funcao que escreve um registro, em uma posição indicada por um RRN, no arquivo .bin
    Parametros: 
        ->fp: ponteiro para o .bin)
        ->reg: registro a ser escrito)
        ->RRN: posição relativa do registro que será escrito
    Retorno: 
            ->0 (foi possivel escrever os dados no .bin com exito)
            ->-1 (houve erro de escrita)
*/
int escreve_reg_RRN(FILE *fp, registro reg, int RRN)
{   
    // Seta ponteiro na posição correspondente ao RRN
    const int pos = TAM_PAG + RRN*TAM_REG; 
    fseek(fp, pos, SEEK_SET);

    return(escreve_reg_bin(fp, reg));                   // escreve registro na posição
}

/*Função responsável pela escrita de um registro removido no arquivo (removido + encademaento + lixo )
    Parâmetros:
        ->fp: ponteiro para arquivo
        ->encad: valor do encademento desse registro removido
        ->RRN: posição relativa do registro removido
    Retorno:
        ->0: escrita bem sucedida
        ->-1: erro na escrita
*/
int escreve_rem_RRN(FILE* fp, int encad, int RRN)
{
    char rem = '1';
    char lixo = '$';
    int k = encad;

    // Seta ponteiro na posição correspondente ao RRN
    const int pos = TAM_PAG + RRN*TAM_REG; 
    fseek(fp, pos, SEEK_SET);

    if(fwrite(&rem, sizeof(char), 1, fp) <=0) return -1;        // escreve status de remoção
    if(fwrite(&k, sizeof(int), 1, fp) <= 0) return -1;          // escreve o encadeamento

    for(int i=0; i < 155; i++)
    {
        if(fwrite(&lixo, sizeof(char), 1, fp) <= 0) return -1;  // adição de lixo ao registro
    }

    return 0;
}

/*  Funcao que le a entrada.csv e armazena os campos na saida.bin
    > Parametros: arq_in  (nome do arquivo CSV a ser lido)
                  arq_out (nome do arquivo BIN a ser gerado)
    > Retorno: 0 (foi possivel armazenar os dados e criar o .bin com exito)
               -1 (houve erro de leitura, armazenamento ou criacao do .bin)
*/
int cria_bin(char* arq_in, char* arq_out)
{
    long unsigned int contador = 0;
    int num_paginas = 0, prox_rrn = 0, aux;
    FILE *fp = fopen(arq_in,"rt");
    FILE *fout = fopen(arq_out, "wb");
    if(fp == NULL || fout == NULL){
        msg_erro_padrao();
        return (-1);
    }

    cabecalho cab_aux;
    cabecalho_inicia(&cab_aux);                             // incia o cabecalho
    registro reg_aux;

    if(escreve_cab_bin(fout,cab_aux) == -1)                 // escreve o cabecalho padrao
    {
        msg_erro_padrao();                                  // houve um erro na escrita do cabecalho
        fclose(fp);
        fclose(fout);
        return (-1);
    }

    reg_aux = le_campos_csv(fp, 1);                         // ignora a primeira linha do CSV

    while(!feof(fp)){
        reg_aux = le_campos_csv(fp, 0);                     // le uma linha do arquivo CSV
        if(escreve_reg_bin(fout,reg_aux) == -1)             // escreve os campos lidos no arquivo BIN de saida
        {
            msg_erro_padrao();                              // houve um erro na escrita dos dados
            fclose(fp);
            fclose(fout);
            return (-1);
        }
        contador += TAM_REG;
    }

    prox_rrn = (contador/TAM_REG);                          // qtd. de registros
    contador += TAM_PAG;                                    // cabecalho!

    aux = contador % TAM_PAG;
    num_paginas = ((aux == 0) ? (contador / TAM_PAG) : ((int)(contador / TAM_PAG) + 1));

    set_status(fout,'1');                 // indica que o arquivo esta atualizado corretamente
    set_proxRRN(fout,prox_rrn);           // atualiza o proximo RRN disponivel
    set_nroPagDisco(fout,num_paginas);    // atualiza o tamanho do arquivo

    fclose(fp);
    fclose(fout);
    return 0;
}

/*Função que remove um registro do arquivo com base em seu RRN
    Parâmetros:
        ->fp: ponteiro para arquivo
        ->RRN: RRN do registro a ser removido
    Retorno:
        ->0: êxito na remoção
        ->-1: erro na remoção
*/
int remove_reg_bin(FILE* fp, int RRN)
{  
    const int n = ftell(fp);                         // guarda posição de fp

    int flag;
    registro reg_aux;
    cabecalho cab_aux;

    reg_aux = le_reg_RRN(fp, &flag, RRN);           // le o registro do RRN e verifica erro
    if(flag == ERRO)
    {
        return -1;
    }

    cab_aux = le_cab_bin(fp, &flag);                // le cabeçalho do arquivo e verifica erro
    if(flag == ERRO)
    {
        return -1;
    }

    if(reg_aux.removido == '1')                     // se registro já foi removido, não faz nada
    {
        return 0;
    }

    // escreve na posição o registro só que removido (com lixo, encadeamento)
    if( escreve_rem_RRN(fp, cab_aux.topo, RRN) == -1) // encadeamento igual ao RRN do último removido
    {
        return -1;
    }

    cab_aux.nroRegRem += 1;                 // incrementa o número de registros removidos

    cab_aux.topo = RRN;                     // atualiza o topo da pilha de removidos com o RRN do atual removido

    if(escreve_cab_bin(fp, cab_aux) == -1)  // escreve cabeçalho com dados atualizados verificando possíveis erros
    {
        return -1;
    }

    fseek(fp, n, SEEK_SET);                // recupera posição inicial de fp

    return 0;
}

/*Função que entra no loop de remoções por busca
    Parâmetros:
        ->nome_bin: nome do arquivo .bin
        ->nome_campo: nome do campo por qual será procurado os registros
        ->mode: 0(busca campo inteiro), 1(busca campo float), 2(busca campo string)
    Retorno:
        ->0: remoção bem sucedida
        ->-2: falha na abertura de arquivo
*/
int loop_remocoes(char* nome_bin, char* nome_campo, int mode)
{
    int reg_int; float reg_float; 
    char reg_str[22];
    int k;

    if(mode==0){// Busca com remoção (mode=0) para campo inteiro
        scanf("%d", &reg_int);
        k = busca_bin_int(nome_bin,nome_campo,reg_int,0);
    }

    if(mode==1){// Busca com remoção (mode=0) para campo float
        scanf("%f", &reg_float);
        k = busca_bin_float(nome_bin,nome_campo,reg_float,0);
    }

    if(mode==2){// Busca com remoção (mode=0) para campo string
        scan_quote_string(reg_str);
        k = busca_bin_string(nome_bin,nome_campo,reg_str,0);
    }

    return k;
}

/*Função responsável pór remover uma quantidade n de registros
    Parâmetros:
        ->nome_bin: nome do arquivo binário
        ->n: quantidade de registros a serem removidos
    Retorno:
        ->0: remoção bem sucedida
        ->-2: falha na abertura de arquivo
*/
int remove_nreg_bin(char* nome_bin, int n)
{
    int k;
    char campo[22];

    for(int i=0; i<n; i++)
    {
        scanf("%s", campo);             // leitura do tipo de campo a ser removido
        
        //Possíveis remoções
        if(strcmp(campo, "populacao") == 0)     k = loop_remocoes(nome_bin, campo, 0);
        if(strcmp(campo, "tamanho") == 0)       k = loop_remocoes(nome_bin, campo, 1);
        if(strcmp(campo, "unidadeMedida") == 0) k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "velocidade") == 0)    k = loop_remocoes(nome_bin, campo, 0);
        if(strcmp(campo, "nome") == 0)          k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "especie") == 0)       k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "habitat") == 0)       k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "tipo") == 0)          k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "dieta") == 0)         k = loop_remocoes(nome_bin, campo, 2);
        if(strcmp(campo, "alimento") == 0)      k = loop_remocoes(nome_bin, campo, 2);

        if(k == -2 ) return k;                   // erro na abertura de arquivo
    }

    return 0;
}

/*Função que insere um registro no arquivo .bin seguindo a abordagem dinãmica
    Parâmetros:
        ->fp: ponteiro para arquivo.bin
        ->reg: registro a ser adicionado
        ->RRN_inserido: parametro para retornar o RRN em que o registro foi inserido
    Retorno:
        ->0: sucesso na inserção do registro
        ->-1: erro na inserção do registro
*/
int insere_reg_bin(FILE* fp, registro reg, int *RRN_inserido)
{
    int flag;

    registro reg_aux;
    cabecalho cab_aux;

    cab_aux = le_cab_bin(fp, &flag);                // le cabeçalho do arquivo e verifica erro
    if(flag == ERRO)
    {
        return -1;
    }

    int topo = cab_aux.topo;                        // recupera campo topo do cabeçalho

    if(topo == -1)                                  // se não houver registros removidos logicamente
    {   
        fseek(fp,0,SEEK_END);
        if(escreve_reg_bin(fp,reg) == -1)           // escreve registro no final do arquivo
        {
            return -1; // verifica se houve erro na escrita do registro
        }

        if(RRN_inserido != NULL) 
            *RRN_inserido = cab_aux.proxRRN;         // salva o RRN em que o registro foi inserido

        cab_aux.proxRRN += 1;                       // incrementa o prxRRN, pois não houve reuso de espaço                   

        cab_aux.nroPagDisco = atualiza_nroPag(cab_aux.proxRRN);    // atualiza número de páginas de disco
        
        if(escreve_cab_bin(fp, cab_aux) == -1)      // escreve cabeçalho com dados atualizados verificando possíveis erros
        {
            return -1; // verifica se houve erro na escrita do cabeçalho
        }

        return 0;
    }

    // caso contrário (topo != -1)
    reg_aux = le_reg_RRN(fp, &flag, topo);      // lê dados (status de removido e encademento) último registro removido
    if(flag == -1) return -1;                   // verifica se não houve erro na leitura de registro

    if(escreve_reg_RRN(fp, reg, topo) == -1)    // insere registro no RRN correspondente do topo da pilha
    {
        return -1; //verifica se houve erro de escrita de registro
    }

    if(RRN_inserido != NULL) 
        *RRN_inserido = topo;                    // salva o RRN em que o registro foi inserido

    cab_aux.nroRegRem -= 1;                     // decrementa número de registros removidos no cabeçalho
    cab_aux.topo = reg_aux.encadeamento;        // define o novo topo da pilha (igual ao encademento do registro correspondente ao topo antigo)
    
    if(escreve_cab_bin(fp, cab_aux) == -1)      // atualização de cabeçalho
    {
        return -1; // verifica se houve erro de escrita de cabeçalho
    }
    
    return 0;                                   
    
}

/*Função que com base insere n registros no arquivo seguindo a abordagem dinâmica
    Parâmetros:
        ->nome_bin: nome do arquivo .bin onde inserimos
        ->n: quantidade de inserções
    Retorna:
        ->-2: falha na abertura do arquivo
        ->-1: falha na inserção de um ou mais registros da entrada
        ->0: inserção ocorreu com sucesso

*/
int insere_nreg_bin(char* nome_bin, int n)
{
    registro *lreg;
    FILE* fp = fopen(nome_bin, "rb+");

    if(fp == NULL)                                  // retorna -2 se houver erro na abertura de arquivo
    {
        return -2;
    }

    lreg = calloc(n, sizeof(registro));                     // aloca lista de registros para inserção

    for( int i =0; i<n; i++)
    {
        lreg[i] = entrada_reg();                            // registro recebe entrada do usuaŕio
        if(insere_reg_bin(fp, lreg[i], NULL) == -1) return -1;    // registro é inserido no arquivo, seguindo lógica do reuso de espaço    
    }

    fclose(fp);
    free(lreg);
    
    return 0;
}

/*Função responsável pela compactação de um arquivo .bin (remoção física de registros)
    Esta função cria um arquivo auxiliar com os registros não removidos e cabeçalho atualizado e
    , após isso, copia todos os dados para o arquivo original
    Parâmetros:
        -> nome_bin: nome do arquivo original
    Retorna:
        -> 0 : processo de compactação teve êxito
        -> -2: caso tenha havido erro na abertura do arquivo
        -> -1: caso tenha havido erro ema alguma parte do processo de compactação
*/
int compacta_bin(char* nome_bin)
{
    int cont=0;
    int flag = 0;
    registro reg_aux;
    cabecalho cab_aux;
    
    //Atualização de arquivo em um arquivo auxiliar
    FILE* fp = fopen(nome_bin, "rb");
    FILE* fa = fopen("aux.bin","wb");

    if (fp == NULL || fa == NULL)                       // verifica se houve erro de abertura do .bin
    {
        return -2;
    }

    cab_aux = le_cab_bin(fp, &flag);                   // escrita de cabeçalho no arquivo auxiliar
    if(flag==ERRO) return -1;                          // verifica se não houve erro na leitura

    fseek(fa, TAM_PAG, SEEK_SET);                      // coloca ponteiro fa na posição certa para escrita de registros em aux.bin

    while(flag != ERRO){                               // enquanto não chega ao fim do arquivo principal
        reg_aux = le_reg_bin(fp, &flag);                    
        
        // Se o registro lido não foi logicamente removido
        if(reg_aux.removido != '1' && flag != ERRO)
        {
            escreve_reg_bin(fa, reg_aux);
            cont++;
        }                                             // incrementa número de registros
    }
    
    cab_aux.topo = -1;                                 // não há mais removidos logicamente

    cab_aux.proxRRN = cont;                            // seta o próximo RRN

    cab_aux.nroPagDisco = atualiza_nroPag(cont);       // atualiza número de páginas de disco

    cab_aux.nroRegRem = 0;                             // zera quantidade de registros removidos logicamente
    
    cab_aux.qttCompacta = cab_aux.qttCompacta + 1;     // incrementa quantidade de compactações feitas
    
    if(escreve_cab_bin(fa, cab_aux) == -1)             // escreve cabeçalho com dados atualizados verificando possíveis erros
    {
        return -1; // verifica se houve erro na escrita do cabeçalho
    }

    fclose(fp);
    fclose(fa);

    //Copia conteúdo do arquivo auxiliar para o arquivo principal
    fp = fopen(nome_bin, "wb");                          // abertura de arquivo pra reescrita
    fa = fopen("aux.bin", "rb");                         // abertura de arquivo auxiliar
    
    if (fp == NULL || fa == NULL)                         // verifica se houve erro de abertura do .bin
    {
        return -2;
    }

    escreve_cab_bin(fp, le_cab_bin(fa, &flag));         // copia cabeçalho do arquivo auxiliar para o arquivo compactado
    if(flag==ERRO) return -1;                           // verifica se não houve erro na escrita

    while(flag != ERRO)                                 // enquanto não chega ao fim do arquivo auxiliar
    {
        reg_aux = le_reg_bin(fa, &flag);                
        if(flag != ERRO)
            escreve_reg_bin(fp, reg_aux);               // copia-se registros do arquivo auxiliar para o arquivo compactado
    }

    fclose(fa);
    fclose(fp);

    remove("aux.bin");                                  // (função linux) remove arquivo auxiliar

    return 0;
}

#include "manipArvB.h"

// -------------------------------------------------------- TRABALHO 2 ---------------------------------------------------------------------------------- //

/*Funcao que inicia o cabecalho do indice com os valores inciais*/
void inicia_cab_ind(indCabecalho *cab_aux){
    cab_aux->status = '1';
    cab_aux->noRaiz = -1;
    cab_aux->RRNproxNo = 0;
}


/*Funcao que escreve cabecalho no inicio do arquivo de indice
    Parametros:
        ->arq: ponteiro para arquivo de indice
        ->cab: cabecalho que sera escrito
    Retorna:
        ->-1: se houve algum erro na escrita
        ->0: para sucesso na escrita
*/
int escreve_cab_ind(FILE* arq, indCabecalho cab){
    
    char lixo = '$';

    fseek(arq, 0, SEEK_SET);                    // garante escrita no comeco

    // escrita de campos do cabecalho com verificacao de possiveis erros
    if(fwrite(&cab.status, sizeof(char), 1, arq) <= 0) return -1;
    if(fwrite(&cab.noRaiz, sizeof(int), 1, arq) <= 0) return -1;
    if(fwrite(&cab.RRNproxNo, sizeof(int), 1, arq) <= 0 ) return -1;

    // adiciona lixo
    for(int i = 9; i < TAM_INDPAG; i++){
        if(fwrite(&lixo, sizeof(char), 1, arq) <= 0 ) return -1;
    }

    return 0;
}


/*Funcao que inicia um nodo criado com os valores necessarios
    Parametros:
        ->arq: ponteiro para arquivo de indice
        ->nodo_aux: ponteiro para no a ser iniciado
        ->folha: char que definira se o nodo e folha (=='1') ou nao (=='0') 
        ->RRNdoNo: RRN do no a ser iniciado
    Retorna: nada
*/
void inicia_nodo_ind(indNodo *nodo_aux, char folha, int RRNdoNo){

    nodo_aux->folha = folha;
    nodo_aux->nroChavesNo = 0;
    nodo_aux->RRNdoNo = RRNdoNo;

    // loop de iniciacao de ponteiros para nos filhos, chaves e referencias do nodo
    for(int i = 0; i < (ORDEM-1); i++){
        nodo_aux->P[i] = -1;
        nodo_aux->C[i] = -1;
        nodo_aux->Pr[i] = -1;
    }

    // iniciacao do ultimo ponteiro para nodo filho
    nodo_aux->P[ORDEM - 1] = -1; 
}


/*Função que escreve um nodo no arquivo indice
    Parametros:
        ->arq: ponteiro para arquivo de indice na posicao de escrita do nodo
        ->nodo: nodo a ser escrito com os dados necessarios
    Retorna:
        ->-1: se houve erro na escrita do nodo
        ->0: se houve sucesso na escrita
*/
int escreve_nodo_ind(FILE *arq, indNodo nodo){

    // escrita das informacoes sobre o nodo atual
    if( fwrite(&nodo.folha, sizeof(char), 1, arq) <= 0) return -1;
    if( fwrite(&nodo.nroChavesNo, sizeof(int), 1, arq) <= 0) return -1;
    if( fwrite(&nodo.RRNdoNo, sizeof(int), 1, arq) <= 0) return -1;

    // loop de escrita de ponteiros para nos filhos, chaves e referencias do nodo
    for(int i = 0; i < (ORDEM-1); i++){
        if( fwrite(&nodo.P[i], sizeof(int), 1, arq) <= 0) return -1;
        if( fwrite(&nodo.C[i], sizeof(long), 1, arq) <= 0) return -1;
        if( fwrite(&nodo.Pr[i], sizeof(long), 1, arq) <= 0) return -1;
    }

    // escrita do ultimo ponteiro para nodo filho
    if(fwrite(&nodo.P[ORDEM - 1], sizeof(int), 1, arq) <= 0) return -1; 

    return 0;
}

/*Função que atualiza um nodo no arquivo indice com base em seu RRN
    Essa atualização tem como foco seu uso no split, já que a escrita de todo o nó estava gerando erros
    Parametros:
        ->arq: ponteiro para arquivo de indice 
        ->nodo: nodo a ser atualizado com os dados necessarios
    Retorna:
        ->-1: se houve erro na escrita do nodo
        ->0: se houve sucesso na escrita
*/
int atualiza_nodo_ind(FILE* arq, indNodo nodo){
    // Atualiza nro de chaves
    fseek(arq, TAM_INDPAG*(nodo.RRNdoNo+1) + 1, SEEK_SET);
    if(fwrite(&nodo.nroChavesNo, sizeof(int), 1, arq) == -1) return -1;

    // Atualiza primeiro ponteiro para nó filo
    fseek(arq, TAM_INDPAG*(nodo.RRNdoNo+1) + 9, SEEK_SET);
    if(fwrite(&nodo.P[0], sizeof(int), 1, arq) == -1) return -1;


    //Atualiza campos
      for(int i=0; i<(ORDEM-1); i++)                              
    {  
        if(fwrite(&nodo.C[i], sizeof(long), 1, arq)  == -1) return -1 ; 
        if(fwrite(&nodo.Pr[i], sizeof(long), 1, arq) == -1) return -1 ;
        if(fwrite(&nodo.P[i+1], sizeof(int), 1, arq) == -1) return -1 ;
    }

    return 0;
}


/*Função que escreve um nodo numa posicao indicada (RRN) do arquivo indice
    Parametros:
        ->arq: ponteiro para arquivo de indice na posicao de escrita do nodo
        ->nodo: nodo a ser escrito com os dados necessarios
        ->RRN: posicao relativa do nodo a ser escrito 
    Retorna:
        ->-1: se houve erro an escrita do nodo
        ->0: se houve sucesso na escrita
*/
int escreve_indNodo_RRN(FILE *arq, indNodo nodo, int RRN){

    fseek(arq, TAM_INDPAG*(RRN+1), SEEK_SET);   // ponteiro adquire byte-offset onde o nodo sera escrito          

    if(escreve_nodo_ind(arq, nodo) == -1) return -1;     // escrita do nodo

    return 0;
}


/*Função que cria o arquivo indice a partir de um .bin dado
    Parametros:
        ->arq_in: nome do arquivo .bin de origem
        ->arq_out: nome do arquivo .bin de indices a ser criado
    Retorna:
        ->-1: se houve erro na montagem do índice
        ->0: se houve sucesso montagem do índice
*/
int cria_arquivo_ArvoreB(char* arq_in, char* arq_out)
{
    int flag;
    FILE *fin, *fout;                       // acessar / criar os arquivos envolvidos
    fin = fopen(arq_in, "rb");              // abertura para ler registros do arquivo de dados
    if(fin == NULL)
    {
        if(NDEBUG) printf("Erro aqui!\n");
        return -1;
    }
    fout = fopen(arq_out, "wb");           // abertura para escrever cabeçalho no arquivo índice
    if(fout == NULL)
    {
        if(NDEBUG) printf("Erro aqui!\n");
        return -1;
    }

    // cabeçalho para a árvore B
    indCabecalho cab_aux;                               // definir e inicializar um cabeçalho ind auxiliar  
    inicia_cab_ind(&cab_aux);
    if(escreve_cab_ind(fout, cab_aux) == -1) return -1; // escrever o cabeçalho ind no arquivo destino

    fclose(fout);                                       // fecha arquivo após sua criação

    // ler o cabeçalho do arquivo ORIGEM
    flag = 0;
    cabecalho cab_origem = le_cab_bin(fin, &flag);      // ler o cabeçalho ORIGEM
    if(flag != 1 || cab_origem.status == '0')           // erro de leitura ou arquivo inconsistente
    {
        if(NDEBUG) printf("Erro aqui 1!\n");

        fclose(fin);
        fclose(fout);
        return -1;
    }
    

    // ler os registros do arquivo ORIGEM e aramazená-los na árvore B    
    registro reg_origem;                                // definir um registro ORIGEM auxiliar
    indNodo nodo_aux;                                   // nodo auxiliar para a arvore B (arq_out)
    int loop = cab_origem.proxRRN;                      // quantidade de registros a serem lidos
    long valor;                                         // VALOR do registro a ser inserido na arvore B (arq_out)
    int RRN_inserido = 0;                               // RRN do registro a ser inserido na arvore B (arq_out)

    while(loop)
    {
        loop--;
        flag = 0;
        reg_origem = le_reg_bin(fin, &flag);            // ler um registro do arq_in
        if(flag != 1)                                   // erro na leitura!
        {
            if(NDEBUG) printf("Erro aqui 2!\n");
            fclose(fin);
            return -1;
        }

        if(reg_origem.removido == '1')                  // o registro está logicamente removido
        {
            RRN_inserido++;
            continue;
        }

        fout = fopen(arq_out, "rb+");                   // abertura de arquivo para inserção do índice
        if(fout == NULL)
        {
            if(NDEBUG) printf("Erro aqui!\n");
            fclose(fin);
            return -1;
        }

        valor = converteNome(reg_origem.nome);                  // pegar o valor do nome (em long int)
        if(insere_arvoreB(fout ,valor, RRN_inserido) == -1)     // inserir na arvore B (arq_out)
        {
            if(NDEBUG) printf("Erro aqui 3!\n");
            fclose(fin);
            fclose(fout);
            return -1;
        }
        RRN_inserido++;                                 //  atualiza o RRN do prox a ser inserido

        fclose(fout);                                   // fecha arquivo no término do inserção
    }
    
    fclose(fin);

    return 0;
}


/*Função que insere um registro no arquivo indice (arvore B)
    Parametros:
        ->valor: VALOR do registro a ser inserido na arvore B
        ->RRN  :   RRN do registro a ser inserido na arvore B
    Retorna:
        ->-1: se houve erro no inserimento
        ->0:  se houve sucesso no inserimento
*/
int insere_arvoreB(FILE* arq, long valor, int RRN)
{   
    int ret;
    int flag=0;

    campo campNovo;                                     // novo campo a ser adicionado na árvore B
    campNovo.C = valor;                                 // recebe chave do registro correspondente
    campNovo.Pr =  TAM_PAG + RRN*TAM_REG;               // recebe byte-offset do registro correspondente
    campNovo.P = -1;

    indCabecalho cab = le_cab_ind(arq, &flag);          // leitura de cabeçalho para verificar condições da árvore
    if(flag != 1){ 
        if(NDEBUG) printf("Erro aqui 3.1!\n");
        return -1;
    }
    
    // se árvore está vazia o primeiro nodo é criado com o novo campo a ser adicionado
    if(cab.noRaiz == -1)                                
    {
        indNodo noRaiz;                        

        // iniciação do primeiro nodo e adição do novo campo          
        inicia_nodo_ind(&noRaiz, '1', 0);
        noRaiz.C[0] = campNovo.C;
        noRaiz.Pr[0] = campNovo.Pr;
        noRaiz.P[1] = campNovo.P;
        noRaiz.nroChavesNo = 1;

        // nodo é escrito no local correspondente ao RRN = 0
        if( escreve_indNodo_RRN(arq, noRaiz, 0) == -1){ // tal nodo passa a ser o nó raíz da árvore 
            if(NDEBUG) printf("Erro aqui 3.2!\n");
            return -1;
        }

        // atualização de cabeçalho
        cab.RRNproxNo++;                                // pŕoximo RRN disponível no índice é RRN=1
        cab.noRaiz = 0;                                 // nó raíz corresponde ao nodo adicionado
        if( escreve_cab_ind(arq, cab) == -1){           // escrita do cabeçalho atualizado
            if(NDEBUG) printf("Erro aqui 3.3!\n");
            return -1;
        }
        return 0;
    }


    // lista e seu tamanho para recebimento do caminho de busca de uma chave
    int tamLista;
    int* RRN_lista =(int*)calloc(cab.RRNproxNo+2, sizeof(int));

    ret = busca_arvoreB(arq, cab, valor, RRN_lista, &tamLista);     // realização da busca
    
    if(NDEBUG)
    {
        printf("Valor aidicionado: %ld | Byte-offset registro: %ld |", campNovo.C, campNovo.Pr);
        printf("Posicao teorica: %d\n", RRN_lista[tamLista-1]);       
        imprime_lista_RRN(RRN_lista, tamLista);
    }

    if(ret == -2){                                                  // verificação de erro na busca
        if(NDEBUG) printf("Erro aqui 3.4!\n");
        return -1;
    }

    if(ret == -1){                                                  // verificação de árvore vazia
        if(NDEBUG) printf("Erro aqui 3.5!\n");
        return -1;
    }
    
    if( insere_em_nodo(arq, campNovo, RRN_lista, tamLista) == -1) { // inserção de novo campo  na árvore B, com base no caminho de RRNs obtidos na busca
        if(NDEBUG) printf("Erro aqui 3.6!\n");
        return -1;
    }

    free(RRN_lista);

    return 0;
}


/*Função que ordena insere ordenadamente um campo em um nodo passado por refência
    Parâmetros:
        ->nodo: ponteiro para nodo em que haverá adição de um campo (uma nova chave)
        ->valor: campo com novo valor(chave) a ser adicionado ao nodo
    Retorna: o nodo ordenado com o novo valor passado por parâmetro
*/
indNodo ordena_campos(indNodo *nodo, campo valor)
{   
    indNodo nodoAux = *nodo;
    int k = nodo->nroChavesNo;
    int j=0; int flag = 1;

    for(int i = 0; i <= k ; i++)
    {   
        if(flag == 0)         // caso o novo valor já tenha sido adicionado, adiciona-se demais valores do nodo
        {
            nodoAux.C[i] = nodo->C[j];
            nodoAux.Pr[i] = nodo->Pr[j];
            nodoAux.P[i+1] = nodo->P[j+1];
            j++;
        }
        else
        {
            if(nodo->C[j] < valor.C && nodo->C[j] != -1)    // comparação caso o valor das chaves do campo do nodo não seja nulo (-1 por convenção)
            {
                nodoAux.C[i] = nodo->C[j];
                nodoAux.Pr[i] = nodo->Pr[j];
                nodoAux.P[i+1] = nodo->P[j+1];
                j++;
            }
            else                                            // valores menores são adicionados primeiro no nodo (ordenação crescente)
            {
                nodoAux.C[i] = valor.C;
                nodoAux.Pr[i] = valor.Pr;
                nodoAux.P[i+1] = valor.P;
                flag = 0;
            }
        }
    }
    
    nodoAux.nroChavesNo += 1;

    return nodoAux;
}



/*Função responsável por inserir um dado campo em um nodo
    A inserção acontece com base na lista de RRNs percorridos na busca da chave do campo dentro da árvore B
    Parâmetros:
        -> fp: ponteiro para arquivo de índice
        -> campo: campo a ser adicionado no nodo (com chave e posição relativa do registro)
        -> RRN_lista: lista de RRNs percorridos no caminho da busca pela chave do campo
        -> tamLista: tamannho da lista, sendo RRN_lista[tamLista-1] igual ao RRN do nodo one haverá iserção
    Retorna:
        ->0: sucesso na inserção
        ->-1: erro na inserção
*/  
int insere_em_nodo(FILE *fp, campo valor, int *RRN_lista, int tamLista)
{
    int flag = 0;                                               // flag para verificação de escritas
    indNodo nodoAux;                                            // nodo auxiliar para inserções
    campo campoAux = valor;                                     // campo auxiliar para inserções, deve começar com o valor que desejamos inserir
    indCabecalho cab = le_cab_ind(fp, &flag);                   // leitura de cabeçalho para verificação de nó Raiz
    if(flag != 1)
    {
        if(NDEBUG) printf("Erro aqui 3.6.1\n");
        return -1;
    }


    for(int i = tamLista-1; i >= 0 ; i--)                        // loop de inserção, iniciando no RRN referente à busca do valor procurado ( RRN_lista[tamLista -1]) 
    {   
        // leitura de nodo referente a atual passagem da lista 
        nodoAux = le_indNodo_RRN(fp, &flag, RRN_lista[i]);
        if(flag != 1)
        {
            if(NDEBUG) printf("Erro aqui 3.6.2\n");
            return -1;
        }

        if(nodoAux.nroChavesNo < (ORDEM-1))                     // se nodo não está cheio, somente adicionamos novo campo
        {               
            nodoAux = ordena_campos(&nodoAux, campoAux);        // inserção de novo campo ordenadamente      

            // escrita do nodo referente a atual passagem da lista (já com o novo campo)
            if(escreve_indNodo_RRN(fp, nodoAux, RRN_lista[i]) == -1)
            {
                if(NDEBUG) printf("Erro aqui 3.6.3\n");
                return -1;
            }
            
            if(NDEBUG)
            {
                printf("INSERCAO EM NODO C/ ESPACO\n");             
                imprimeNodo(&nodoAux);                                 
            }

            return 0;                                           // inserção termina
        }
        
        else                                                    // se nodo está cheio, realiza-se o split
        {
            campoAux = split(fp, campoAux, &nodoAux);           // campo auxiliar recebe campo promovido no split
            
            if(NDEBUG)
            {
                printf("Campo promovido:\n");                      
                imprime_campo(campoAux);
            }

            // se houve o split em um nó raiz
            if( RRN_lista[i] == cab.noRaiz)
            {

                cab = le_cab_ind(fp, &flag);                    // leitura de cabeçalho atualizado pelo split
                if(flag != 1)
                {
                    if(NDEBUG) printf("Erro aqui 3.6.3\n");
                    return -1;
                }   

                inicia_nodo_ind(&nodoAux, '0', cab.RRNproxNo);  // iniciação do novo nó raiz
                nodoAux.nroChavesNo++;                          // novo nó terá uma chave (referennte ao campo promovido) no split
                nodoAux.P[0] = RRN_lista[i];                    // primeiro ponteiro do nó raiz recebe RRN do nodo que sofreu split
                
                // nodo recebe campo promovido
                nodoAux.C[0] = campoAux.C;                      
                nodoAux.Pr[0] = campoAux.Pr;
                nodoAux.P[1] = campoAux.P;
       

                // nodo é escrito no próximo RRN disponível no arquivo de índice
                if(escreve_indNodo_RRN(fp, nodoAux, nodoAux.RRNdoNo) == -1)
                {
                    if(NDEBUG) printf("Erro aqui 3.6.4\n");
                    return -1;
                }

                cab.noRaiz = nodoAux.RRNdoNo;                   // atualiza o RRN do nó raiz com RRN do novo nodo (que possui o campo promovido)
                cab.RRNproxNo++;                                // incrementa próximo RRN disponível para escrita no arquivo de ídice
                if(escreve_cab_ind(fp, cab) == -1)              // novos dados são inseridos no cabeçalho
                {
                   if(NDEBUG) printf("Erro aqui 3.6.5\n");
                   return -1;
                }

                return 0;                                       // término da inserção
            }

            // se não houve spĺit em nó raiz, campo promovido é inserido no nodo anteriormente percorrido (com RRN = RRN_lista[i-1])

        }
    }

    return 0;
}

/*Função para dar split em uma página da árvore
    Parametros:
        ->valor: VALOR do registro a ser inserido na arvore B
        ->nodo: nodo no qual ocorrerá o processo de split
    Retorna:
        ->promovido: campo que deve ser promovido
        ->promovido.C == ERRO: se houve erro no split (dentro do processo de leitura do Nodo)
*/
campo split(FILE *fp, campo valor, indNodo *nodo)
{
    int flag = 0;                                   // flag de verificacao da escrita
    campo promovido;                                // campo que será promovido
    indNodo aux1, aux2;                             // nodos que serão escritos no arquivo de indice

    indCabecalho cab = le_cab_ind(fp, &flag);       // leitura de cabeçalho
    if(flag != 1)                                   // verifica erro de leitura
    {
        if(NDEBUG) printf("Erro split aqui 1!\n");
        promovido.C = ERRO;
        return promovido;
    }

    int RRN_novo = cab.RRNproxNo;                   // RRN da próxima página a ser criada

    if(NDEBUG)
    {
        printf("Aux1 pre-split:\n");                    
        imprimeNodo(nodo);
    }     

    campo lista[ORDEM];                             // devolve os valores em ordem
    analisa_valores(nodo, valor, lista);            // ordena lista de valores, incluindo novo valor a ser adicionado
    
    promovido = lista[MEIO];                        // valor central, já que estão ordenados

    if(NDEBUG)
    {
        printf("SPLIT\n");                              
        imprime_lista_campo(lista);             
    }

    // escrever as informações do nodo atual
    inicia_nodo_ind(&aux1, nodo->folha, nodo->RRNdoNo);     // iniciação do nodo auxiliar 1
    aux1.nroChavesNo = MEIO;                                // também possui metade do número de chaves possíveis
    aux1.P[0] = nodo->P[0];
    for(int i=0; i<MEIO; i++)                               // inclusão de campos anteriores ao promovido
    {
        aux1.C[i] = lista[i].C;
        aux1.Pr[i] = lista[i].Pr;
        aux1.P[i+1] = lista[i].P;
    }
    for(int i=MEIO; i<(ORDEM-1); i++)                       // inclusão de campos nulos
    {
        aux1.C[i] = -1;
        aux1.Pr[i] = -1;
        aux1.P[i+1] = -1;
    }

    if(atualiza_nodo_ind(fp, aux1) == -1)                   // atualização do nodo
    {
        if(NDEBUG) printf("Erro split aqui 2!\n");
        promovido.C = ERRO;
        return promovido;
    }

    if(NDEBUG)
    {
        indNodo b = le_indNodo_RRN(fp, &flag, nodo->RRNdoNo);
        printf("aux1: \n");
        imprimeNodo(&b);
    }

    // escrever as informações do nodo novo
    inicia_nodo_ind(&aux2, nodo->folha, RRN_novo);   // RRN corresponde a novo pŕoximo RRN disponível do arquivo de índice
                                                    // se o nodo de inserção é folha, o novo nodo criado também é
    aux2.nroChavesNo = MEIO;                        // também possui metade do número de chaves possíveis
    aux2.P[0] = promovido.P;                        // mantém ponteiro para nodo filho a direita (do campo promovido) como primeiro ponteiro do novo nodo
    for(int i=0; i < MEIO; i++)                     // inclusão de campos posteriores ao promovido
    {
        aux2.C[i] = lista[i + MEIO + 1].C;
        aux2.Pr[i] = lista[i + MEIO + 1].Pr;
        aux2.P[i+1] = lista[i + MEIO + 1].P;
    }
    for(int i=MEIO; i<(ORDEM-1); i++)               // inclusao de valores nulos do nodo
    {
        aux2.C[i] = -1;
        aux2.Pr[i] = -1;
        aux2.P[i+1] = -1;                       
    }   

    if(escreve_indNodo_RRN(fp, aux2, RRN_novo)==-1)     // escreve novo nodo no arquivo
    {
        if(NDEBUG) printf("Erro split aqui 4!\n");
        promovido.C = ERRO;
        return promovido;
    }

    if(NDEBUG)
    {
        indNodo b = le_indNodo_RRN(fp, &flag, RRN_novo);
        printf("aux2: \n");
        imprimeNodo(&b);
    }

    promovido.P = RRN_novo;                             // ponteiro a direita do nodo promovido recebe endereço do nodo criado
    
    // atualiza cabeçalho após inclusão de novo nodo
    cab.RRNproxNo++;                            
    if(escreve_cab_ind(fp, cab)==-1){
        if(NDEBUG) printf("Erro split aqui 5!\n");
        promovido.C = ERRO;
        return promovido;
    }                   

    return promovido;                                   // retorna campo com a chave a ser promovida
}

/*Função que recebe um valor e uma página da arvore e devolve esses campos ordenados
    Parametros:
        ->valor: VALOR que deve ser ordenado com os campos da página lida
        ->nodo: nodo de referência
        ->vetor_aux: vetor a ser ordenado
*/
void analisa_valores(const indNodo* nodo, campo valor, campo* vetor_aux)
{
    int k;
    for(int i=0, j=0, modo = 1;j<ORDEM;j++)        // coloca em os valores lidos e o valor passado em um vetor ordenado
    {
        if(modo == 1)
        {
            if(nodo->C[i] < valor.C && j < ORDEM-1) // evita erro caso o valor adicionase seja maior que todos do nó de análise
            {
                vetor_aux[j].C = nodo->C[i];
                vetor_aux[j].Pr = nodo->Pr[i];
                vetor_aux[j].P = nodo->P[i+1];
                i++;
            }
            else
            {
                vetor_aux[j].C = valor.C;
                vetor_aux[j].Pr = valor.Pr;
                vetor_aux[j].P = valor.P;
                modo = 2;
                k = j;
            }
        }
        else if(modo == 2)  // novo valor já inserido na lista (inserir todos os demais valores do nodo)
        {
            vetor_aux[j].C = nodo->C[i];
            vetor_aux[j].Pr = nodo->Pr[i];
            vetor_aux[j].P = nodo->P[i+1];
            i++;
        }
    }

    return ;
}

/*Função que insere n registros nos arquivos binarios e dados e da arvore B
    Parâmetros:
        ->nome_dados:  nome do arquivo de dados onde inseriremos
        ->nome_arvore: nome do arquivo da arvore B onde inseriremos
        ->n: quantidade de inserções
    Retorna:
        ->-2: falha na abertura do arquivo
        ->-1: falha na inserção de um ou mais registros da entrada
        ->0: inserção ocorreu com sucesso

*/
int insere_nreg_ambos(char* nome_dados, char* nome_arvore, int n)
{
    long chave; int RRN;                                    // valores dos campos C e Pr a serem inseridos na arvore B

    registro *lreg;
    FILE* fp_dados = fopen(nome_dados, "rb+");
    FILE *fp_arvore = fopen(nome_arvore, "rb+");

    if(fp_dados == NULL || fp_arvore == NULL)               // retorna -2 se houver erro na abertura de arquivo
    {
        return -2;
    }

    lreg = calloc(n, sizeof(registro));                     // aloca lista de registros para inserção

    for( int i =0; i<n; i++)
    {
        lreg[i] = entrada_reg();                                          // registro recebe entrada do usuaŕio
        if(insere_reg_bin(fp_dados, lreg[i], &RRN) == -1) return -1;      // registro é inserido no arquivo, seguindo lógica do reuso de espaço    

        chave = converteNome(lreg[i].nome);
        if(insere_arvoreB(fp_arvore, chave, RRN) == -1) return -1;       // chave do registro é inserida na arvore B
    }

    fclose(fp_dados);
    fclose(fp_arvore);
    free(lreg);
    
    return 0;
}
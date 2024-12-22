// Primeiro Exercício Prático - arquivo source(.c) de funções do programa
/*Alunos:
 *Vitor Alexandre Garcia Vaz(14611432)
 *Vitor Pardini Saconi(14611800)
*/
#include "biblioteca.h"
#include "funcoesFornecidas.h"

//  STRUCTS
/*Definição da struct das coordenadas (localização)
    -> possui duas coordenadas (x e y) correspondentes a dois floats
*/
typedef struct t_coordenada{
    float x;
    float y;
}coordenada;

/*Definição da struct de registro
    ->Struct que corresponde a um registro de tamanho fixo
    ->Campos fixos,  são informaçõe sobre as espécies marinhas
    ->O total de espaço ocupado pelos campos corresponde a REG_TAM bytes
*/
typedef struct t_registro{
    int SPECIES_ID;             //Byte offset=0
    char NAME[41];              //Byte offset=4
    char SCIENTIFIC_NAME[61];   //Byte offset=45
    int POPULATION;             //Byte offset=106
    char STATUS[9];             //Byte offset=110
    coordenada LOCATION;        //Byte offset=119
    int HUMAN_INPACT;           //Byte offset=127
}registro; //possui REG_TAM bytes



// FUNCÕES AUXILIARES (somente no .c)
/*Função que verifica se um ID já existe no arquivo binário
    Parâmetros:
        -> Ponteiro para arquivo: arq
        -> Id da espécie: ID
    Retorna:
        -> A posição (byteoffset) do ID se for encontrado
        -> -1 se o ID não foi encontrado
    OBS:
        Para seu funcionamento, o arquivo ja deve estar aberto
*/
int posicao_id(FILE* arq, int ID){
    int i=0;
    int buffer;

    fseek(arq,0,SEEK_SET);

    while(fread(&buffer,sizeof(int),1,arq)!=0){
        if(buffer==ID){
            return (i*REG_TAM);
        }
        i++;
        fseek(arq, REG_TAM*i,SEEK_SET);
    }

    return -1;
}

/*Função que cria um registro cm base nas Parâmetros dadas pelo usuario
    Parâmetros:
        não possui
    Retorna:
        ->um registro da epecie informada pelo usuario
*/
registro scanf_registro(){
    char barra_n[2]; //variável usada para armazenar os '\n' após scanf, para não impactar as leituras com fgets
    registro reg;
    scanf("%d", &reg.SPECIES_ID);
    readline(reg.NAME);
    readline(reg.SCIENTIFIC_NAME);
    scanf("%d",&reg.POPULATION);
    readline(reg.STATUS); 
    scanf("%f %f", &reg.LOCATION.x, &reg.LOCATION.y);
    scanf("%d",&reg.HUMAN_INPACT);
    return reg;
}

/*Função que completa os campos de vetores de caracteres com $ (caracteres lixo)
    Parâmetros:
        ->endereço da string: str
        ->tamanho máximo do campo: tam_campo
*/
void adicionar_lixo(char *str, int tam_campo){
    int len=strlen(str);
    if(str[len]=='\0'){
        for(int i=len+1; i<(tam_campo);i++){
            str[i]='$';
        }
    }
}

/*Função que retira \n (ou caractere invisivel \r) da string lida via fgets
    Parâmetros:
    ->endereço da string: str
*/
void tirar_BarraN(char *str){
    for(int i=0; str[i]!='\0';i++){
        if(str[i]=='\n' || str[i]=='\r'){
            str[i]='\0';
            break;
        }
    }
}

/*Função para escrita da string e lixo (em conjunto) no arquivo
    Parâmetros:
        ->Endereço da string: str
        ->Tamanho máximo da string definido na estrutura de registro: tam_campo
        ->Ponteiro para arquivo: arq
    OBS:
        A string será armazenada até o '\n' e o espaço restante será preenchido com '$'
*/
void fwrite_string(char *str, int tam_campo, FILE *arq){
    adicionar_lixo(str, tam_campo);
    fwrite(str,sizeof(char),tam_campo,arq);
}

/*Função que adiciona registro no final do arquivo
    Parâmetros:
        ->Ponteiro para arquivo: arq
        ->Registro (struct) a ser adicionado: reg
    OBS:
        Para seu funcionamento, o arquivo ja deve estar aberto
*/
void adicionar_registro(FILE *arq, registro reg){
    fseek(arq,0,SEEK_END);
    fwrite(&(reg.SPECIES_ID),sizeof(int),1,arq);
    fwrite_string(reg.NAME,41,arq);
    fwrite_string(reg.SCIENTIFIC_NAME,61,arq);
    fwrite(&(reg.POPULATION),sizeof(int),1,arq);
    fwrite_string(reg.STATUS,9,arq);
    fwrite(&(reg.LOCATION.x),sizeof(float),1,arq);
    fwrite(&(reg.LOCATION.y),sizeof(float),1,arq);
    fwrite(&(reg.HUMAN_INPACT),sizeof(int),1,arq);
}

/*Função que adiciona informações da string de um campo pertencente à um registro existente com base em seu RRN
    Parâmetros:
        ->Ponteiro para o arquivo: arq
        ->Número relativo do registo em relaçao ao início do arquivo: RRN
        ->Byteoffset da informação a ser adicionada (em relaçao ao início do registro): ini
        ->Tamanho máximo da string do dado a ser adicionado no campo: tam
    OBS:
        Para seu funcionamento, é necessário que o arquivo já esteja aberto
*/
void adicionar_campoString(FILE* arq, int RRN, int ini, int tam){
    char info[tam];

    fseek(arq, (RRN+ini), SEEK_SET);
    fread(info,sizeof(char),tam,arq);

    if(strcmp(info,"NULO") == 0){
        scanf("%s",info);
        adicionar_lixo(info, tam);
        fseek(arq, (RRN+ini), SEEK_SET); //volta ponteiro para byteoffset do campo
        fwrite(info, sizeof(char), tam, arq);
    }
    else{
        scanf("%s",info);
        printf("Informação já inserida no arquivo\n");
    }
}

/*Função que adiciona informações do  número inteiro de um campo pertencente à um registro existente com base em seu RRN
    Parâmetros:
        ->Ponteiro para o arquivo: arq
        ->Número relativo do registo em relaçao ao início do arquivo: RRN
        ->Byteoffset da informação a ser adicionada (em relaçao ao início do registro): ini
    OBS:
        Para seu funcionamento, é necessário que o arquivo já esteja aberto
*/
void adicionar_campoInteiro(FILE* arq, int RRN, int ini){
    int info;

    fseek(arq, (RRN+ini), SEEK_SET);
    fread(&info,sizeof(int),1,arq);

    if(info == 0){
        scanf("%d",&info);
        fseek(arq, (RRN+ini), SEEK_SET); //volta ponteiro para byteoffset do campo
        fwrite(&info,sizeof(int),1,arq);
    }
    else{
        scanf("%d",&info);
        printf("Informação já inserida no arquivo\n");
    }
}

/*Função que imprime informações de um registro específico
    Parâmetros: registro a ser impresso
*/
void imprime_registro(registro reg){
    // confirmar se os campos não são nulos!
    if(reg.SPECIES_ID == 0) // espera-se que o ID não seja nulo...
        printf("ID: NULO\n");
    else
        printf("ID: %d\n", reg.SPECIES_ID);

    printf("Nome: %s\n", reg.NAME);
    printf("Nome Científico: %s\n", reg.SCIENTIFIC_NAME);

    if(reg.POPULATION == 0)
        printf("População: NULO\n");
    else
        printf("População: %d\n", reg.POPULATION);

    printf("Status: %s\n", reg.STATUS);
    printf("Localização: (%.2f, %.2f)\n", reg.LOCATION.x, reg.LOCATION.y);

    if(reg.HUMAN_INPACT == 0)
        printf("Impacto Humano: NULO\n\n");
    else
        printf("Impacto Humano: %d\n\n", reg.HUMAN_INPACT);
}

/*Função que lê um registro específico de um arquivo
    Parâmetros:
        ->Ponteiro para arquivo: arq
        ->Número que apenas determina se é para ler (1) ou não (0) o ID: n
    OBS:
        Para seu funcionamento é necessário que:
            ->O arquivo já esteja aberto
            ->O ponteiro do arquivo já esteja no RRN do registro que deve ser lido
    Retorno: o próprio registro (struct) que foi lido do arquivo
*/
registro leitura_registro(FILE* arq, int n){
    registro reg;
    if(n)
        fread(&reg.SPECIES_ID, sizeof(int), 1, arq);
    fread(reg.NAME, sizeof(char), 41, arq);
    fread(reg.SCIENTIFIC_NAME, sizeof(char), 61, arq);
    fread(&reg.POPULATION, sizeof(int), 1, arq);
    fread(reg.STATUS, sizeof(char), 9, arq);
    fread(&reg.LOCATION.x, sizeof(float), 1, arq);
    fread(&reg.LOCATION.y, sizeof(float), 1, arq);
    fread(&reg.HUMAN_INPACT, sizeof(int), 1, arq);
    return reg;
}



// FUNÇÕES PRINCIPAIS (usadas na main)
/*(Comando == 1)Função principal de adição de espécies
    Parâmetros:
        ->Ponteiro para arquivo: arq
        ->Nome do arquivo (ex: nome.bin): arqNome
        ->Quantidade de espécies a serem registradas: qntReg
*/
void adicionar_especies(FILE* arq, char* arqNome, int qntReg){
    registro reg;
    arq=fopen(arqNome, "wb");
    if(arq==NULL){
        printf("Falha no processamento do arquivo\n");
        return;
    }

    for(int i=0; i<qntReg; i++){
        reg = scanf_registro();
        adicionar_registro(arq, reg);
    }
    fclose(arq);
}

/*(Comando == 2) Função principal de relatório das espécies
    Printa as informações de todas as espécies contidas no arquivo
    Parâmetros:
        -> Ponteiro para arquivo: arq
        -> Nome do arquivo a ser lido: arqName
*/
int recuperar_especies(FILE* arq, char* arqName)
{
    int ID;
    int flag = 1;   //controle do laço (foi inserido pois o runcodes estava bugado :P )
    registro aux_reg;

    arq = fopen(arqName, "rb");
    if(arq == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return -1;
    }

    while(flag)
    {
        flag = fread(&ID, sizeof(int), 1, arq);

        if(!flag)   // se flag == 0, fim do arquivo!
            break;

        aux_reg = leitura_registro(arq,0);
        aux_reg.SPECIES_ID = ID;
        imprime_registro(aux_reg);
    }

    fclose(arq);

    return 0;
}


/*(Comando == 3) Função principal de busca de espéciee
    Printa as informações uma espécies desejada
    Parâmetros:
        -> Ponteiro para arquivo: arq
        -> Nome do arquivo a ser lido: arqName
        -> Número relativo do registro buscado: RRN
*/
void recuperar_RRN(FILE* arq, char* arqName, int RRN)
{
    registro aux_reg;
    arq = fopen(arqName, "rb");
    if(arq == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return;
    }
    fseek(arq, 0, SEEK_END);
    int max = ftell(arq);     // computar o tamanho do arquivo

    if((RRN % REG_TAM != 0) || (RRN >= max))    // verificar se o RRN é válido
    {
        printf("Espécie não encontrada\n");
    }
    else
    {
        fseek(arq,RRN,SEEK_SET);    // ir até o registro pedido

        aux_reg = leitura_registro(arq, 1);
        imprime_registro(aux_reg);
    }

    fclose(arq);
}



/*(Comando == 4)Função principal de completar as informações possivelmente nulas de um registro
    Parâmetros:
        ->Ponteiro para arquivo: arq
        ->Nome do arquivo onde está o registro: arqName
        ->Quantidade de informações(campos) a serem completadas pelo usuário: antInfo
        ->ID correspondente ao registro que terá informações completadas: ID
    OBS:
        ->Se o arquivo não existe (arq == NULL): informa que houve falha de processamento do arquivo
        ->Se informação, do ID mencionado, não é nula (info!=NULO ou info!=0): informa que a informação já foi inserida
        ->Se ID não foi encontrado (position == -1): informa que espécie desejada não foi encontrada
*/
void completar_especie(FILE* arq, char* arqName, int qntInfo, int ID){
    char info[15];
    int posicao;

    arq=fopen(arqName,"rb+");

    if(arq==NULL){
        printf("Falha no processamento do arquivo\n");
        return;
    }
    else{
        posicao=posicao_id(arq,ID);//obtem RRN do registro

        if(posicao!= -1){
            for(int i=0; i<qntInfo; i++){

                readline(info);

                if(strcmp(info,"STATUS")==0) adicionar_campoString(arq, posicao, 110 , 9);
                else if(strcmp(info,"POPULATION")==0) adicionar_campoInteiro(arq, posicao, 106);
                else if(strcmp(info,"HUMAN IMPACT")==0) adicionar_campoInteiro(arq, posicao, 127);
            }
        }
        else printf("Espécie não encontrada\n");
    }
    fclose(arq);
}

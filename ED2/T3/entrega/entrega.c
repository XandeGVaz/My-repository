/*
*Aluno: Vitor Alexandre Garcia Vaz
*No USP: 14611432
*/

/// Includes do programa //////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////



/// Defines do programa////////////////////////////////////////////////////////////////////////
#define h(k,i) (k +(hash->C1*i)+(hash->C2*i*i))%S //Define da função hash usada, critério do usuário desde que tenha: k(número inteiro da chave), i(índice) e S(tamanho da tabela hash)

#define size_word 30 //Define do tamanho das palavras que serão adicionadas na tabela

///////////////////////////////////////////////////////////////////////////////////////////////



/// Definição de structs///////////////////////////////////////////////////////////////////////
typedef char t_key; //Aqui declara-se o tipo de chave usada para procura dos dados
typedef struct type_data{
    t_key key[size_word];
    int added; //quantas vezes dado foi adicionado repetidamente na tabela
}data; //Struct de um dado que contém sua chave e outras informações adicionais

/* Struct da tabela hash que contém:
*1-vetor de dados
*2-tamanho máximo da tabela (correspondente ao número de espaços alocados no vetor de dados)
*3-número de adições de dados diferentes na tabela
*4-número de remoções de dados diferentes na tabela
*5-constantes C1 e C2 de dispersão da função hash
*/
typedef struct type_thash{
    data* datas;
    int len;
    int adds;
    int removes;
    int C1,C2;
}thash;

///////////////////////////////////////////////////////////////////////////////////////////////



/// Declaração de funções da tabela hash //////////////////////////////////////////////////////
thash* make_thash(int size, int C1, int C2);//Cria a tabela hash, com base em seu tamanho e nas constantes de dispersão da função hash

int add_thash_data(thash* hash,  t_key* key);//Adiciona dado com uma chave key, informando a posição onde o dado foi adicionado

int remotion_thash_data(thash* hash,  t_key* key);//Remove um dado com base na sua chave e retorna a posição onde o dado removido estava

int search_thash_data( const thash* hash,  t_key* key);//Retorna posição (0,1,2,...,n-1) de um dado na tabela hash, com base em sua chave

void print_data_info( const thash* hash, t_key* key);//Print de informações de um dado da tabela hash com base em uma chave

void print_thash_datas(const thash* hash); //Print das chaves da tabela hash

void print_thash_info(const thash* hash); //Print da quantidade de chaves diferenttes presentes na tabela e da chave que mais foi adicionada (juntamente com essa quantidade de adições dessa mesma chave)

///////////////////////////////////////////////////////////////////////////////////////////////



/// Declaração de funções da execução do programa//////////////////////////////////////////////
void option_1(thash* hash, int S);//T=1
void option_2(thash* hash);//T=2
void option_3(thash* hash);//T=3
void option_4(thash* hash);//T=4
void option_5(thash* hash);//T=5

///////////////////////////////////////////////////////////////////////////////////////////////



/// Execução do programa///////////////////////////////////////////////////////////////////////
int main(){
    int S,T,flag=1;
    int C1,C2;
    scanf("%d %d %d",&S,&C1,&C2);
    thash* hash=make_thash(S,C1,C2);
    while(flag){
        scanf("%d",&T);
        switch(T){
            case 0:
                flag=0;
                break;
            case 1:
                option_1(hash,S);
                break;
            case 2:
                option_2(hash);
                break;
            case 3:
                option_3(hash);
                break;
            case 4:
                option_4(hash);
                break;
            case 5:
                option_5(hash);
                break;
        }
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////



/// Funções auxiliares da tabela hash//////////////////////////////////////////////////////////

//Função equivalente à "hash" que foi descrita no pdf
int return_k(thash* hash, t_key* key){
    int k=0;
    int size_key=strlen(key);
    for(int i=0; i<size_key; i++){
        k+=3*k+key[i];
        k=k%(hash->len);
    }
    return k;
}

//Função que cria um dado novo que está sendo adicionado na tabela hash com base em uma chave
data create_data(t_key* key){
    data dt;
    strcpy(dt.key,key);
    dt.added=1;
    return dt;
}

//Função que compara em ordem alfabética duas chaves, sendo composta pela funlçao srtcmp
int key_cmp(t_key* k1, t_key* k2){
    return(strcmp(k1,k2));
}

///////////////////////////////////////////////////////////////////////////////////////////////




/// Definição de funções da tabela hash////////////////////////////////////////////////////////
thash* make_thash(int size, int C1, int C2){
    thash* hash=calloc(1,sizeof(thash));

    hash->datas=calloc(size,sizeof(data));
    for(int i=0;i<size;i++){
        hash->datas[i].key[0]='*'; //sendo "*" indicador de espaço nunca ocupado
    }
    hash->len=size;
    hash->adds=0;
    hash->removes=0;
    hash->C1=C1;
    hash->C2=C2;

    return hash;
}

int add_thash_data(thash* hash,  t_key* key){
    int pos;
    pos=search_thash_data(hash,key);//necessário para saber se o elemento existe na tabela,pois podem haver mais de uma adição no mesmo espaço da tabela hash.
    //Elemento existe, sendo necessário incrementar número de adições dele.
    if(pos!=-1){
        hash->datas[pos].added++;
        return pos;
    }
    //Elemento não existe, necessário verificar se há espaços vazios para adicioná-lo na tabela.
    if(pos==-1){
        int k=return_k(hash,key);
        int S=hash->len;
        for(int i=0; i < hash->len ;i++){
            pos=h(k,i);
            if(hash->datas[pos].key[0]=='*' || hash->datas[pos].key[0]=='#'){
                hash->datas[pos]=create_data(key);
                hash->adds++;//Mais um elemento adicionado, incrementa número total de adições da hash.
                return pos;//Elemento adicionado pela primeira vez com sucesso.
            }
        }
        return -1;//Tabela está cheia de elementos.
    }
}


int remotion_thash_data(thash* hash,  t_key* key){
    int k=return_k(hash,key);
    int S=hash->len;
    int pos=0;
    for(int i=0; i < hash->len ;i++){
        
        pos=h(k,i);

        if(hash->datas[pos].key[0]=='*'){
            return -1; //Elemento não foi removido pois não existe na tabela.
        }
        if(key_cmp(hash->datas[pos].key,key)==0){
            hash->datas[pos].key[0]='#';//Assim, "#" indica que esse espaço já foi ocupado.
            hash->datas[pos].added=0;
            hash->removes++; //Mais um elemento removido, incrementa número total de adições da hash.
            return pos; //Elemento removido com sucesso.
        }
    }
    return -1; 
    //Tabela hash está cheia de elementos e o procurado para exclusão não existe nela.
}

int search_thash_data(const thash *hash,  t_key* key){
    int k=return_k(hash,key);
    int S=hash->len;
    int pos=0;
    for(int i=0; i < hash->len ;i++){
        
        pos=h(k,i);

        if(hash->datas[pos].key[0]=='*'){
            return -1; //Elemento não encontrado pois não existe na tabela hash.
        }
        if(key_cmp(hash->datas[pos].key,key)==0){
            return pos; //Elemento encontrado com sucesso ->retorna sua posição na tabela hash.
        }
    }
    return -1; 
    //Tabela hash está cheia de elementos e o procurado não foi encontrado.
}

void print_data_info(const thash* hash, t_key* key){
    int pos=search_thash_data(hash,key);
    if(pos==-1){
        printf("%s nao encontrada\n",key);
    }
    else{
        printf("%s encontrada %d\n",hash->datas[pos].key,hash->datas[pos].added);
    }
}

void print_thash_datas(const thash* hash){
    printf("imprimindo tabela hash\n");
    for (int i =0; i<hash->len ;i++){
        if(hash->datas[i].key[0]!='*' && hash->datas[i].key[0]!='#'){
            printf("%s %d\n",hash->datas[i].key,i);
        }
    }
    printf("fim da tabela hash\n");
}
void print_thash_info(const thash* hash){
    //Usa-se o número total de adições diferentes e de remoções difeentes para saber o número total de dados diferentes na tabela hash (total=adições-remoções).
    printf("foram encontradas %d palavras diferentes\n",hash->adds-hash->removes);

    data fdata=hash->datas[0];
    //Laço para o encontro do dado com maior número de adições na tabela
    for(int i=0; i< hash->len; i++){
        
        if(fdata.added<hash->datas[i].added) fdata=hash->datas[i];
        //Caso dois dados tenham o mesmo número de adições, tem prioridade o que forr mais antecipado no alfabeto.
        else if(fdata.added==hash->datas[i].added){
            if(key_cmp(fdata.key,hash->datas[i].key)>=1) fdata=hash->datas[i]; 
        }
    }
    printf("palavra mais frequente = %s, encontrada %d vezes\n",fdata.key,fdata.added);
}

///////////////////////////////////////////////////////////////////////////////////////////////



/// Definição de funções da execução do programa///////////////////////////////////////////////

/*Qunado T=1
*Função que lê uma frase em uma string auxiliar , recebe partes dessa string em um vetor texto, para adicionar cada palavra na abela hash.
*Separação feta por meio da função strtok, utilizando o espaço(" ") como separador entre palavras.
*Uso de um contador para evitar tentativa de adições quando a tabela já está cheia.
*/
void option_1(thash* hash,int S){
    int cont=0;
    char aux[100000];
    t_key *text;

    scanf("%s",aux);
    text=strtok(aux," ");
    
    while(text!=NULL && cont<S){
        add_thash_data(hash,text);
        cont++;
        text=strtok(NULL," ");
    }
}

/*Quando T=2
*Imprime algumas informações da tabela hash:
*1-número de palavras diferentes
*2-palavra com mais adições e o número de adições dessa  palavra
*/
void option_2(thash* hash){
    print_thash_info(hash);
}

/*Quando T=3
*É lida uma quantidade n de dados que terão suas informações imprimidas.
*È alocado um vetor de n strings para guardas as chaves de tais dados(indicados pelo usuário).
*São imprimidas informações do dado (nesse caso somente a quantidade de vezes que foi adicionado), sendo também informado, pela função da hash, se tal dado existe na tabela.
*/
void option_3(thash* hash){
    int n;
    t_key** words;

    scanf("%d",&n);
    words=calloc(n,sizeof(t_key*));
    for(int i=0; i<n; i++){
        words[i]=calloc(size_word,sizeof(t_key));
        scanf("%s",words[i]);
    }

    for(int i=0; i<n; i++){
        print_data_info(hash,words[i]);
    }
}

/*Quando T=4
*É lida uma quantidade n de dados que serão removidos da tabela.
*È alocado um vetor de n strings para guardas as chaves de tais dados(indicados pelo usuário).
*Dados são removidos através da função de remoção da tabela hash, sendo informado se tal dado foi removido com sucesso ou se o dado a ser removido  não existe na tabela.
*/
void option_4(thash* hash){
    int n,pos;
    t_key** words;

    scanf("%d",&n);
    words=calloc(n,sizeof(t_key*));
    for(int i=0; i<n; i++){
        words[i]=calloc(size_word,sizeof(t_key));
        scanf("%s",words[i]);
    }

    for(int i=0; i<n; i++){
        pos=remotion_thash_data(hash,words[i]);
        if(pos==-1) printf("%s nao encontrada\n",words[i]);
        else printf("%s removida\n",words[i]);
    }
}

/*Quando T=5
*Simplesmente imprime dados  da tabela hash da primeira posição (0) até a última (n-1).
*obs: posições vazias não são imprimidas!
*/
void option_5(thash* hash){
    print_thash_datas(hash);
}

///////////////////////////////////////////////////////////////////////////////////////////////

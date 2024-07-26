#include "estatic_hash.h"

/// Definição de estruturas ///////////////////////////////////////////////////////////////////
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




/// Definição de funções auxiliares ///////////////////////////////////////////////////////////

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




/// Declaração de funções de usuário //////////////////////////////////////////////////////////
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

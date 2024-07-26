#include "estatic_hash.h"

/// Definição de estruturas ///////////////////////////////////////////////////////////////////
typedef struct type_data{
    t_key key;
    int added; //quantas vezes dado foi adicionado repetidamente na tabela
}data; //struct de um dado que contém sua chave e outras informações adicionais

/* Variável da tabela hash que contém:
*1-vetor de dados
*2-tamanho máximo da tabela (correspondente ao número de espaços alocados no vetor de dados)
*3-número de adições de dados diferentes na tabela
*4-número de remoções de dados diferentes na tabela
*/
typedef struct type_thash{
    data* datas;
    int len;
    int adds;
    int removes;
}thash;
///////////////////////////////////////////////////////////////////////////////////////////////




/// Definição de funções auxiliares ///////////////////////////////////////////////////////////
int return_k(t_key key){
    int k=key;
    return k;
}

data create_data(t_key key){
    data dt;
    dt.key=key;
    dt.added=1;
    return dt;
}
///////////////////////////////////////////////////////////////////////////////////////////////




/// Definição de funções de usuário ///////////////////////////////////////////////////////////
thash* make_thash(const int size){

    thash* hash=calloc(1,sizeof(thash));

    hash->datas=calloc(size,sizeof(data));
    for(int i=0;i<size;i++){
        hash->datas[i].key=-1;
    }
    hash->len=size;
    hash->adds=0;
    hash->removes=0;

    return hash;
}

int add_thash_data(thash* hash, const t_key key){
    int k=return_k(key);
    int S=hash->len;
    int pos=0;
    pos=search_thash_data(hash,key);//procura necessária para evitar adicionar dois dados em lugares diferentes, por conta dos espaços removidos 
    if(pos!=-1){
        hash->datas[pos].added++;
        return pos;
    }
    else{
        for(int i=0; i<hash->len; i++){
            pos=h(k,i);
            if(hash->datas[pos].key==-1 || hash->datas[pos].key==-2){
                hash->datas[pos]=create_data(key);
                hash->adds++;
                return pos;
            }
        }
    }
    return -1; //tabela hash está cheia de dados
}


int remotion_thash_data(thash* hash, const t_key key){
    int k=return_k(key);
    int S=hash->len;
    int pos=0;
    for(int i=0; i < hash->len ;i++){
        
        pos=h(k,i);

        if(hash->datas[pos].key==-1){
            return -1; //elemento não foi removido pois não existe na tabela
        }
        if(hash->datas[pos].key==key){
            hash->datas[pos].key=-2;
            hash->datas[pos].added=0;
            hash->removes++;
            return pos; //elemento removido com sucesso
        }
    }
    return -1; 
    //tabela hash está cheia de elementos e o procurado para exclusão não existe nela 
}

int search_thash_data(const thash *hash, const t_key key){
    int k=return_k(key);
    int S=hash->len;
    int pos=0;
    for(int i=0; i < hash->len ;i++){
        
        pos=h(k,i);

        if(hash->datas[pos].key==-1){
            return -1; //elemento não existe na tabela hash
        }
        if(hash->datas[pos].key==key){
            return pos; //elemento encontrado com sucesso->retorna sua posição na tabela hash
        }
    }
    return -1; 
    //tabela hash está cheia de elementos e o procurado não foi encontrado
}

int return_data_added(const thash* hash, int pos){
    return (hash->datas[pos].added);
}

void print_thash_datas(thash* hash){
    printf("\n\tTabela hash:");
    for (int i =0; i<hash->len ;i++){
        if(hash->datas[i].key==-1 || hash->datas[i].key==-2){
            printf("\nDatas[%d]=%d",i,hash->datas[i].key);
        }
        else{
            printf("\nDatas[%d]=%d[adicionado %d vezes]",i,hash->datas[i].key,hash->datas[i].added);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////

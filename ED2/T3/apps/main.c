#include "estatic_hash.h"

void option_1(thash* hash, int S);
void option_2(thash* hash);
void option_3(thash* hash);
void option_4(thash* hash);
void option_5(thash* hash);


int main(){
    int S,T,C1,C2,flag=1;
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
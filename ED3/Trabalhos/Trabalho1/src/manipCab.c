#include "manipCab.h"


// inicia o cab
void cabecalho_inicia(cabecalho* cab_aux)
{
    cab_aux->status = '0';
    cab_aux->topo = -1;
    cab_aux->proxRRN = 0;
    cab_aux->nroRegRem = 0;
    cab_aux->nroPagDisco = 0;
    cab_aux->qttCompacta = 0;
}

/*  Funcao que escreve o cabecalho no arquivo .bin
    > Parametros: fp (ponteiro para o .bin)
                  cab (cabecalho a ser escrito)
    > Retorno: 0 (foi possivel escrever o cabecalho no .bin com exito)
               -1 (houve erro de escrita)
*/
int escreve_cab_bin(FILE *fp, cabecalho cab)
{
    int n = TAM_PAG;                                // n : tamanho do cabecalho (uma pagina de disco)
    char lixo = '$';
    fseek(fp,0,SEEK_SET);                           // garantia de estar no inicio

    if(fwrite(&cab.status,sizeof(char),1,fp) <= 0) return (-1);
    if(fwrite(&cab.topo,sizeof(int),1,fp) <= 0) return (-1);
    if(fwrite(&cab.proxRRN,sizeof(int),1,fp) <= 0) return (-1);
    if(fwrite(&cab.nroRegRem,sizeof(int),1,fp) <= 0) return (-1);
    if(fwrite(&cab.nroPagDisco,sizeof(int),1,fp) <= 0) return (-1);
    if(fwrite(&cab.qttCompacta,sizeof(int),1,fp) <= 0) return (-1);

    for(n -= 21; n != 0; n--)
        if(fwrite(&lixo,sizeof(char),1,fp) <= 0) return (-1);       // escrever os lixos no espaco que resta

    return 0;
}

int set_status(FILE *fp, char c)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,0,SEEK_SET) != 0) return (-1);              // vai para o local do status
    if(fwrite(&c,sizeof(char),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

int set_topo(FILE *fp, int topo)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,1,SEEK_SET) != 0) return (-1);              // vai para o local do topo
    if(fwrite(&topo,sizeof(int),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

int set_proxRRN(FILE *fp, int prox)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,5,SEEK_SET) != 0) return (-1);              // vai para o local do proxRRN
    if(fwrite(&prox,sizeof(int),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

int set_nroRegRem(FILE *fp, int removidos)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,9,SEEK_SET) != 0) return (-1);              // vai para o local do nroRegRem
    if(fwrite(&removidos,sizeof(int),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

int set_nroPagDisco(FILE *fp, int paginas)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,13,SEEK_SET) != 0) return (-1);              // vai para o local do nroPagDisco
    if(fwrite(&paginas,sizeof(int),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

int set_qttCompacta(FILE *fp, int qtd)
{
    int n = ftell(fp);                                      // salva o local de fp
    if(fseek(fp,17,SEEK_SET) != 0) return (-1);              // vai para o local do qttCompacta
    if(fwrite(&qtd,sizeof(int),1,fp) <= 0) return (-1);
    if(fseek(fp,n,SEEK_SET) != 0) return (-1);              // retorna ao local inicial de fp
    return 0;
}

/*Função responsável por retornar o número de páginas de disco com base no proxRRN
    Parâmetros:
        ->proxRRN: próximo RRN disponível no arquivo
    Retorna:
        -> cont: novo número de páginas de disco
*/
int atualiza_nroPag(int proxRRN){
    int cont, resto;

    // Obtém número de páginas
    cont = proxRRN * TAM_REG;
    resto = cont % TAM_PAG;
    cont = ( resto == 0 ) ? ( cont/TAM_PAG ) : ( cont/TAM_PAG + 1); // número de páginas de registros
    cont++;                                                         // contando com o cabeçalho

    return cont;                             // retorna número de páginas atualizado
}
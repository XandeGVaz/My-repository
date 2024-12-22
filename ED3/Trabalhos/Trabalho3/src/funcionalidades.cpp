#include "funcionalidades.hpp"

using namespace grafos;

void funcionalidade10(){

    // Leitura do arquivo (principal) de registros 
    char arqNome[50];
    scanf("%s",arqNome);

    // Abertura do arquivo binário para leitura dos registros
    FILE *fp = fopen(arqNome,"rb");

    // Verificação da abertura do arquivo
    if(fp == NULL){
        msg_erro_padrao();
        return;
    }

    // Leitura do cabeçalho do arquivo e verificação de erros
    int flag;
    cabecalho cab = le_cab_bin(fp, &flag);
    if(flag == ERRO || cab.status == '0'){
        msg_erro_padrao();
        return;
    }

    // Criação do grafo com base nos registros do arquivo de dados
    Grafo grafo = criaGrafo(fp);

    // Fechamento do arquivo
    fclose(fp);

    // Impressão dos vértices do grafo e elementos adjacentes
    grafo.imprimeGrafo();

}

void funcionalidade11()
{   
    // Leitura do nome do arquivo binário
    char arqNome[50];
    scanf("%s",arqNome);

    // Abertura do arquivo binário para leitura dos registros e verificação de erros
    FILE* fp = fopen(arqNome,"rb");
    if(fp == NULL)
    {
        msg_erro_padrao();
        return;
    }

    // Leitura do cabeçalho do arquivo e verificação de erros
    int flag;
    cabecalho cab = le_cab_bin(fp, &flag);
    if(flag == ERRO || cab.status == '0'){
        msg_erro_padrao();
        return;
    }

    // Cria grafo com base nos registros do arquivo
    Grafo grafo = criaGrafo(fp);

    // Fecha arquivo
    fclose(fp);

    // Leitura do número de nomes a serem buscados
    int n;
    scanf("%d",&n);

    // Lista de nomes a serem buscados
    std::list<std::string> listaNomes;
    std::list<std::string>::iterator itListaNomes;

    // Leitura dos nomes a serem buscados
    char *nome;
    
    for(int i=0; i<n; i++)
    {
        nome = new char[50];

        scan_quote_string(nome);
        listaNomes.push_back(std::string(nome));

        delete [] nome;
    }

    // Percurso da lista de nomes fornecidos
    for(itListaNomes = listaNomes.begin(); itListaNomes != listaNomes.end(); itListaNomes++)
    {   
        // Imprime vértices adjacentes ao vértice com nome fornecido
        imprimeAdjacencias(grafo, *itListaNomes);
    }

}

void funcionalidade12()
{
    // Leitura do nome do arquivo binário
    char arqNome[50];
    scanf("%s",arqNome);

    // Abertura do arquivo binário para leitura dos registros e verificação de erros
    FILE* fp = fopen(arqNome,"rb");
    if(fp == NULL)
    {
        msg_erro_padrao();
        return;
    }

    // Leitura do cabeçalho do arquivo e verificação de erros
    int flag;
    cabecalho cab = le_cab_bin(fp, &flag);
    if(flag == ERRO || cab.status == '0'){
        msg_erro_padrao();
        return;
    }

    // Cria grafo com base nos registros do arquivo
    Grafo grafo = criaGrafo(fp);

    // Fecha arquivo
    fclose(fp);

    // Imprime o número de ciclos simples do grafo
    std::cout << "Quantidade de ciclos: " << grafo.numCiclosGrafo() << std::endl;

}

void funcionalidade13(){

    // Leitura do nome do arquivo binário
    char arqNome[50];
    scanf("%s",arqNome);

    // Abertura do arquivo binário para leitura dos registros e verificação de erros
    FILE* fp = fopen(arqNome,"rb");
    if(fp == NULL)
    {
        msg_erro_padrao();
        return;
    }

    // Leitura do cabeçalho do arquivo e verificação de erros
    int flag;
    cabecalho cab = le_cab_bin(fp, &flag);
    if(flag == ERRO || cab.status == '0'){
        msg_erro_padrao();
        return;
    }

    // Cria grafo com base nos registros do arquivo
    Grafo grafo = criaGrafo_sunlight(fp);

    // Fecha arquivo
    fclose(fp);

    // Imprime a mensagem sobre a conectividade do grafo
    msgFortementeConexo(grafo.ehFortementeConexo() /*Verifica se é conexo*/, grafo.numComponentes() /*Número de componentes conexas*/);

}


void funcionalidade14(){

    // Leitura do nome do arquivo binário
    char arqNome[50];
    scanf("%s",arqNome);

    // Abertura do arquivo binário para leitura dos registros e verificação de erros
    FILE* fp = fopen(arqNome,"rb");
    if(fp == NULL)
    {
        msg_erro_padrao();
        return;
    }

    // Leitura do cabeçalho do arquivo e verificação de erros
    int flag;
    cabecalho cab = le_cab_bin(fp, &flag);
    if(flag == ERRO || cab.status == '0'){
        msg_erro_padrao();
        return;
    }

    // Cria grafo com base nos registros do arquivo
    Grafo grafo = criaGrafo(fp);

    // Fecha arquivo
    fclose(fp);

    // Leitura do número de mínimos caminhos a serem calculados
    int n;
    scanf("%d",&n);

    // Lista de nomes dos vértices de saída nos menores caminhos procurados
    std::vector<std::string> listaNomesSaida;

    // Lista de nomes dos vértices de entrada nos menores caminhos procurados
    std::vector<std::string> listaNomesEntrada;


    // Leitura dos nomes a serem buscados
    char nomeSaida[50];
    char nomeEntrada[50];
    
    // Leitura dos nomes de saída e entrada
    for(int i=0; i<n; i++)
    {
        // Leitura dos nomes de saída e entrada
        scan_quote_string(nomeSaida);
        scan_quote_string(nomeEntrada);

        // Adição dos nomes de saída e entrada nas listas
        listaNomesSaida.push_back(nomeSaida);
        listaNomesEntrada.push_back(nomeEntrada);
    }

    // Variável para armazenar o menor caminho entre os vértices de saída e entrada
    int menorCaminho;

    // Percurso da lista de nomes fornecidos
    for(int i=0; i<n; i++)
    {      
        // Obtem o menor caminho entre os vértices de saída e entrada
        menorCaminho = grafo.menorCaminho(listaNomesSaida[i], listaNomesEntrada[i]);

        std::cout << listaNomesSaida[i] << " " << listaNomesEntrada[i] << ": ";

        // Imprime o menor caminho entre os vértices de saída e entrada
        if(menorCaminho == -1) std::cout << "CAMINHO INEXISTENTE" << std::endl;
        else std::cout << menorCaminho << std::endl;
    }

}
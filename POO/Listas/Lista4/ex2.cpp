/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <stack>
#include <queue>

#define INTMAX 2147483647


std::string jogo(std::stack<int> cartas, std::queue<std::string> jogadores){

    // Declaração da fila de pontuação
    std::queue<int> pontuacao;

    // Inicialização da fila de pontuação
    for(int i = 0; i<jogadores.size(); i++)
        pontuacao.push(0);
    
    // Declaração da carta auxiliar
    int cartaAux = 0;

    // Declaração da menor pontuação
    int menor = INTMAX;

    // Declaração do jogador ganhador
    std::string jogadorGanhador;

    // Enquanto houver cartas
    while(!cartas.empty()){

        // Retira a carta do topo da pilha
        cartaAux = cartas.top();
        cartas.pop();

        // Adiciona a carta na pontuação do jogador
        pontuacao.push(cartaAux+pontuacao.front());
        pontuacao.pop();

        // Adiciona o jogador no final da fila
        jogadores.push(jogadores.front());
        jogadores.pop();
    }

    // Enquanto houver jogadores
    while(!jogadores.empty()){

        // Se a pontuação do jogador for menor que a menor pontuação
        if(menor > pontuacao.front()){
            // Atualiza a menor pontuação
            menor = pontuacao.front();
            jogadorGanhador = jogadores.front();
        }

        // Se a pontuação do jogador for igual a menor pontuação
        if(menor == pontuacao.front()){
            // Se o jogador for menor que o jogador ganhador, alfabeticamente, atualiza o jogador ganhador
            if(jogadorGanhador.compare(jogadores.front()) > 0){
                jogadorGanhador = jogadores.front();
            }
        }

        // Saem da fila de pontuação e da fila de jogadores
        pontuacao.pop();
        jogadores.pop();
    }

    // Retorna o jogador ganhador
    return jogadorGanhador;
}

int main() {
    std::stack<int> c;
    std::queue<std::string> j;
    c.push(5);
    c.push(2);
    c.push(15);
    c.push(11);
    c.push(8);
    c.push(12);
    c.push(10);
    c.push(13);
    c.push(10);
    c.push(13);
    c.push(8);
    c.push(5);
    c.push(4);
    c.push(6);
    c.push(13);
    c.push(1);
    c.push(10);
    c.push(15);
    c.push(14);
    c.push(9);
    c.push(9);
    c.push(9);
    c.push(14);
    c.push(3);
    c.push(7);
    c.push(13);
    c.push(4);
    c.push(8);
    c.push(5);
    c.push(15);
    c.push(5);
    c.push(15);
    c.push(6);
    c.push(2);
    c.push(12);
    c.push(15);
    c.push(15);
    c.push(10);
    c.push(10);
    c.push(15);
    c.push(2);
    c.push(2);
    c.push(15);
    c.push(10);
    c.push(3);
    c.push(5);
    c.push(2);
    c.push(3);
    c.push(13);
    c.push(5);
    c.push(9);
    c.push(7);
    c.push(5);
    c.push(13);
    c.push(2);
    c.push(4);
    c.push(3);
    c.push(2);
    c.push(13);
    c.push(8);
    c.push(4);
    c.push(4);
    c.push(10);
    c.push(15);
    c.push(1);
    c.push(13);
    c.push(10);
    c.push(3);
    c.push(5);
    c.push(5);
    c.push(15);
    c.push(6);
    c.push(5);
    c.push(6);
    c.push(9);
    c.push(4);
    c.push(6);
    c.push(1);
    c.push(15);
    c.push(9);
    c.push(4);
    c.push(5);
    c.push(10);
    c.push(3);
    c.push(10);
    c.push(13);
    c.push(9);
    c.push(8);
    c.push(9);
    j.push("dom");
    j.push("theo");
    j.push("otávio");
    j.push("yan");
    j.push("davi");
    j.push("lívia");
    j.push("luiz");
    j.push("camila");
    j.push("maria");
    j.push("felipe");
    j.push("natália");
    j.push("dr.");
    j.push("rael");
    j.push("antônio");
    j.push("ana");
    j.push("srta.");
    j.push("isaac");
    j.push("liam");
    std::cout << jogo(c, j) << std::endl;
    return 0;
}

// deveria ser
// theo
// mas deu
// liam
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>

long long int mdc(long long int num1, long long int num2) // função responsável por encontrar o mdc de dois números
{   
    // obtenção dos módulos das entradas
    long long int n1, n2;
    n1 = (num1>=0) ? num1 : -num1;
    n2 = (num2>=0) ? num2 : -num2;

    long long int a, b;                 // variáveis auxiliares
    long long int rest;                 // variável que armazena o resto da divisão

    a = (n1 > n2) ? n1 : n2;    // a recebe o maior número
    b = (n1 > n2) ? n2 : n1;    // b recebe o menor número

    while(b != 0){
        rest = a % b;                   // rest recebe o resto da divisão de a por b
        
        a = b;                          
        b = rest;                         
    }

    return a;                           // retorna o mdc
}

class Fracao{

    long long int _numerador;
    long long int _denominador;

    void reduz(){   // privada -> todas as instâncias devem estar em suas formas reduzidas

        long long int minDivisor = mdc(_numerador, _denominador);
        _numerador /= minDivisor;
        _denominador /= minDivisor;
    }

public:

    Fracao(long long int numerador = 0, long long int denomiador = 1)
    {
        _numerador = numerador;
        _denominador = denomiador;

        reduz();
    }

    Fracao(double x, double eps)
    {
        // numerador e denominador padrões
        long long int numerador=0, denominador=1;
        // contador para verificar precisão
        int cont= 0;                

        // partes inteira e decimal da entrada x
        long long int inteiro = x;
        double decimal = x - inteiro;

        /*      
        *       -Enquanto a parte decimal for menor que a precisão,
        *   dividi-se essa parte até que a precisão seja atingida
        *       -Conta-se o número de divisões feitas e a cada uma 
        *   multiplicamos o denominador por 10
        *       -Isso garante que a até a casa decimal desejada seja
        *   considerada no fracionamento
        */
        while( std::abs(decimal) > eps)    
        {
            decimal /= 10;
            denominador *= 10;
            cont++;
        }

        // desconsidera casa que ultrapassa o nível de precisão
        if(cont>0) denominador /= 10;
        
        _denominador = denominador;

        // numerador correspondente ao denominador obtido
        decimal = denominador*x;
        _numerador = decimal;

        reduz();
    }

    friend std::ostream& operator <<(std::ostream &out, const Fracao &f){
        
        //caso não seja inteiro, imprime numerador e denomiandor
        if(f._numerador % f._denominador != 0) out << f._numerador << '/' << f._denominador;

        //caso seja inteirp, imprime apenas numerador
        else out << f._numerador;
        
        return out;
    }

    operator double() const{
        return ((double) _numerador/_denominador);
    }

    friend Fracao operator +(const Fracao &a, const Fracao &b){
        if(a._numerador != 0  && b._numerador != 0) 
            return Fracao( a._numerador*b._denominador + b._numerador*a._denominador,
            a._denominador * b._denominador );

        else if(a._numerador == 0) return Fracao(b._numerador, b._denominador);
        else return Fracao(a._numerador, a._denominador);
    }

    friend Fracao operator -(const Fracao &a, const Fracao &b){
        if(a._numerador != 0  && b._numerador != 0) 
            return Fracao( a._numerador*b._denominador - b._numerador*a._denominador,
            a._denominador * b._denominador );

        else if(a._numerador == 0) return Fracao(-b._numerador, -b._denominador);
        else return Fracao(a._numerador, a._denominador);                          
    }

    friend Fracao operator *(const Fracao &a, const Fracao &b){
        return Fracao( a._numerador*b._numerador, a._denominador * b._denominador );
    }

    friend Fracao operator /(const Fracao &a, const Fracao &b){
        return Fracao( a._numerador*b._denominador, a._denominador * b._numerador );
    }
};


int main() {
    Fracao f(0.7045454545454546, 1e-10);
    std::cout << f << " " << double(f) << std::endl;
    f = f * Fracao(78LL, 76LL);
    f = f + Fracao(-75LL, 76LL);
    f = f / Fracao(9LL, 2LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f / Fracao(-62LL, 94LL);
    f = f * Fracao(99LL, 4LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f - Fracao(16LL, 28LL);
    f = f + Fracao(59LL, 26LL);
    return 0;
}


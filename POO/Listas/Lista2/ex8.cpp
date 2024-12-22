
#include <iostream>
#include <string>

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

// Complexos
class C{
    
    double _real;
    double _imag;

public:
    
    C(double, double imag);
    double parteReal() const;
    double parteImag() const;

    /* Polimorfismo nesse exercício
    *   Como precisávamos usar o operador << na main, o qual usa função friend, foi necessária fazer um 
    * método virtual que retornasse uma string coma o conteúdo que desejamos integrar à saída em cada
    * através do operador <<
    *   Vale ressaltar que cada tipo numérico possui uma impressão diferente, então esse método virtual
    * foi necessária para adequar, em cada classe derivada, o conteúdo de forma mais conveniente à saída
    * esperada. Sem essa função virtual, todas as impressões ocorreriam conforme a proposta na classe base
    * (classe C).
    */
    virtual std::string saida() const;
    friend std::ostream& operator <<(std::ostream &out, const C &a);      
};

C::C(double real = 0, double imag = 0): _real(real), _imag(imag) {}

double C::parteReal() const{
    return _real;
}

double C::parteImag() const{
    return _imag;
}

std::string C::saida() const {
    return (std::to_string(_real) + " + " + std::to_string(_imag) + "i");
}


std::ostream& operator <<(std::ostream &out, const C &a){
    out << a.saida();
    return out;
}


// Reais
class R : public C{

public:

    R(double real);

    std::string saida() const override;     // o override ajuda a evidenciar o fato de que trata-se de um método virtual
    friend std::ostream& operator <<(std::ostream &out, const R &a);

};

R::R(double real = 0): C(real, 0){}

std::string R::saida() const{
    return(std::to_string(parteReal()));
}


std::ostream& operator <<(std::ostream &out, const R &a){
    out << a.saida();
    return out;
}


// Racionai
class Q: public R{

    long long int _numerador;
    long long int _denominador;

    void reduz(){   // privada -> todas as instâncias devem estar em suas formas reduzidas

        long long int minDivisor = mdc(_numerador, _denominador);
        _numerador /= minDivisor;
        _denominador /= minDivisor;
    }

public:

    Q(long long int numerador, long long int denomiador);
    long long int numerador() const;

    std::string saida() const override;
    friend std::ostream& operator <<(std::ostream& out, const Q &a);

};

Q::Q(long long int numerador = 0, long long int denominador = 1): R((double)numerador/denominador),
_numerador(numerador), _denominador(denominador){}

long long int Q::numerador() const{
    return _numerador;
}

std::string Q::saida() const{
    return(std::to_string(_numerador) + "/" + std::to_string(_denominador));
}

std::ostream& operator <<(std::ostream& out, const Q &a){
    out << a.saida();
    return out;
}


// Inteiros
class Z: public Q{

public:

    Z(long long int inteiro);

    std::string saida() const override;
    friend std::ostream& operator <<(std::ostream &out, const Z &a);
};

Z::Z(long long int inteiro = 0): Q(inteiro, 1){}

std::string Z::saida() const{
    long long int num = numerador();
    if(num > 0) return("+" + std::to_string(num));
    else return std::to_string(num);
}

std::ostream& operator <<(std::ostream &out, const Z &a){
    out << a.saida();
    return out;
}


// Naturais
class N: public Z{

public:
    N(unsigned long long int natural);

    std::string saida() const override;
    friend std::ostream& operator <<(std::ostream &out, const N &a);
};

N::N(unsigned long long int natural = 0): Z(natural){}

std::string N::saida() const {
    return (std::to_string(numerador()));
}

std::ostream& operator <<(std::ostream &out, const N &a){    
    out << a.saida();
    return out;
}


int main() {
    const int numObjetos = 5;
    C* objetos[numObjetos];             // esta maneira de alocação não inicia os objetos

    objetos[0] = new C(3.5, 2.1);
    objetos[1] = new R(5.0);
    objetos[2] = new Q(1, 3);
    objetos[3] = new Z(10);
    objetos[4] = new N(10);
    for (int i = 0; i < numObjetos; ++i)
        std::cout << *objetos[i] << std::endl;
    for (int i = 0; i < numObjetos; ++i)
        delete objetos[i];
    return 0;
}


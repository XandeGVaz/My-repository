/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <string>
#include <iomanip>

// função responsável por converrter um char para um dígito
int converte_digito(char c){
    int num =  c - '0';         // conversão de char para inteiro em c
    return num;
}

class BigInt{
    int * _partes;
    int _npartes;
    bool _positivo;

public:

    // Construtor por passagem de string
    BigInt(std::string numero){
        char c;
        int digito;

        // aloca partes do BigInt
        _partes = new int[9];
        
        // verifica quantas partes BigInt terá de fato
        _npartes = numero.size();

        // verificação de sinal
        c = numero[0];
        if(c != '-'){
            // definimos como um número positivo
            _positivo = true;
        }
        else{
            // ajustamos o número de partes e definimos como um número negativo
            _npartes--;
            _positivo = false;
        }

        // Big int recebe as partes restantes
        for(int i=0, j=0; i < _npartes; i++){

            if(!_positivo) j = i+1;
            else j=i;

            digito = converte_digito(numero[j]);
            _partes[i] = digito;
        }

        // Inversão do sinal do primeiro elemento caso o número seja negativo
        if(!_positivo) _partes[0] = - _partes[0];
    }

    // Construtor por passagem de número
    BigInt(int num, bool eh_num = true){
        
        // aloca partes do BigInt
        _partes = new int[9];
        
        if(eh_num)
        {
            std::string aux = std::to_string(num);
            char c;
            int digito;


            // verifica quantas partes BigInt terá de fato
            _npartes = aux.size();

            // verificação de sinal
            c = aux[0];
            if(c != '-'){
                // definimos como um número positivo
                _positivo = true;
            }
            else{
                // ajustamos o número de partes e definimos como um número negativo
                _npartes--;
                _positivo = false;
            }

            // Big int recebe as partes restantes
            for(int i=0, j=0; i < _npartes; i++){

                if(!_positivo) j = i+1;
                else j=i;

                digito = converte_digito(aux[j]);
                _partes[i] = digito;
            }

            // Inversão do sinal do primeiro elemento caso o número seja negativo
            if(!_positivo) _partes[0] = - _partes[0];
        }

        else
        {
            // adiciona uma quantidade num de dígitos '0' no BigInt
            for(int i = 0; i < num; i++){
                _partes[i] = 0;
            }

            // número total de parrtes é igual a num
            _npartes = num;
            
            // número formado é positivo (só tem dígitos zero)
            _positivo = true;
        }
    }

    // Cnstrutor padrão
    BigInt(){
        // cria um Big int de uma parte igual ao dígito zero (também positiva)
        _partes = new int[9];
        _partes[0] = 0;
        _npartes = 1;
        _positivo = true; 
    }

    /* Construtor de movimento, utilizado quando há a passagem de valores sem cópia, 
    mas sim transferência*/
    BigInt(BigInt &&b): _npartes(b._npartes), _positivo(b._positivo)
    {
        _partes = std::move(b._partes); // construtor de movimento próprrio de strings/vetores
    }

    // Destruidor
    ~BigInt(){
        delete _partes;
    }

    // Verificação de positivo
    bool positivo(){
        return _positivo;
    }

    /*Regra dos Três do C++:

        Se sua classe possuir um desses três: destrutor, construtor de cópia ou operador 
        de atribuição, provavelmente ela precisa de todos os três.
    
    */

   // Construtor de cópia por atribuição , recomendado para classes que usam recursos (como listas)
    BigInt& operator=(const BigInt &b){
        
        // Novo vetor de PArtes
        _partes = new int[9];
        
        // Cópia de integrantes
        std::copy(b._partes, b._partes+b._npartes, _partes); // std::copy (copia, copia+extensãoDaCópia , destino do copy)
        _npartes = b._npartes;
        _positivo = b._positivo; 

        return *this;
    }

    // retorno do módulo do BigInt
    BigInt abs(){

        std::string aux ;
        int i = 0;

        // se negativo o primeira parte passa a ser positiva
        if(!_positivo){
            i=1;
            aux.append(std::to_string(-_partes[0]));
        }

        // Passa BigInt para o formato string
        for(i ; i<_npartes; i++)
            aux.append(std::to_string(_partes[i]));
        
        // Retona um BigInt iniciado com base na string formada
        return BigInt(aux);
    }

    // Verificar igualdade de números
    friend bool operator ==(const  BigInt &a, const BigInt &b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i < a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }        
        num1 = std::stoi(str1);

        for(int i = 0; i < b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }        
        num2 = std::stoi(str2);

        return (num1==num2);

    }

    // Comparação a>b
    friend bool operator >(const  BigInt &a, const BigInt &b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i < a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }        
        num1 = std::stoi(str1);

        for(int i = 0; i < b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }        
        num2 = std::stoi(str2);

        return (num1>num2);

    }

    // operação de soma de big ints
    friend BigInt operator+(const BigInt &a, const BigInt b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i<a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }
        num1=std::stoi(str1);

        for(int i = 0; i<b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }
        num2=std::stoi(str2);

        num1 += num2;

        return BigInt(num1);    
    }

    // operação de subtração de big ints
    friend BigInt operator-(const BigInt &a, const BigInt b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i<a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }
        num1=std::stoi(str1);

        for(int i = 0; i<b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }
        num2=std::stoi(str2);

        num1 -= num2;

        return BigInt(num1);    
    }

    // inverte sinal BigInt
    BigInt operator -(){
        
        std::string str;
        
        // copia string com sinal do primeiro elemento invertido (isso também causa inversão de _positivo no construtor)
        str.append(std::to_string(-_partes[0]));
        for(int i = 1; i<_npartes; i++){
            str.append(std::to_string(_partes[i]));
        }

        return BigInt(str);
    }

    // operação de multiplicação de big ints
    friend BigInt operator*(const BigInt &a, const BigInt b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i<a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }
        num1=std::stoi(str1);

        for(int i = 0; i<b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }
        num2=std::stoi(str2);

        num1 *= num2;

        return BigInt(num1);    
    }

    // operação de divisão de  um big int por um inteiro
    friend BigInt operator/(const BigInt &a, int b){
        
        std::string str;
        int num;
        
        for(int i = 0; i<a._npartes; i++){
            str.append(std::to_string(a._partes[i]));
        }
        
        num = std::stoi(str);
        num /= b;

        return BigInt(num);    
    }

    // operação de um bigint elevado a outro
    friend BigInt operator^(const BigInt &a, const BigInt b){
        
        std::string str1, str2;
        int num1, num2;
        
        for(int i = 0; i<a._npartes; i++){
            str1.append(std::to_string(a._partes[i]));
        }
        num1=std::stoi(str1);

        for(int i = 0; i<b._npartes; i++){
            str2.append(std::to_string(b._partes[i]));
        }
        
        for(int i=1; i<num2; i++)
            num1 *= num1;

        return BigInt(num1);    
    }


    // Operador de saída
    friend std::ostream& operator <<(std::ostream& out, BigInt &a){
        
        int ret;
        std::string aux;
        
        // adiciona todos os dígitos de int*_pates na string;
        for(int i=0; i<a._npartes; i++){
            aux.append(std::to_string(a._partes[i]));        
        }

        // transforma string em um inteiro;
        ret = std::stoi(aux);

        // retorna inteiro em uma referência de saída 
        out << ret;

        return out;
    }
};

int main(){
    // std::string u = "-28";
    // int num = std::strtol(u.data(), NULL, 10);
    // std::cout << "Tamanho:" << u.size() << "| Número:" << num << "| String:" << u.data() << std::endl;

    int i = -28;

    std::string u = std::to_string(i);

    BigInt test("28");
    std::cout << test << std::endl;

    BigInt test2(-589,true);
    std::cout << test2 << std::endl;

    BigInt test3 ;
    test3 = test2;
    std::cout << test3 << std::endl;

    BigInt test4 = test3.abs();
    std::cout << test4 << std::endl;

    if(test4>test)
        std::cout << "test4 > test" << std::endl;

    BigInt aux;
    aux = test4;
    test4 = test;
    test = aux;
    
    if(test4>test)
        std::cout << "test4 > test" << std::endl;
    else
        std::cout << "test4 < test" << std::endl;

    



}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <math.h>

class Vetor{
    int _x;
    int _y;

public:

    Vetor(int x=0, int y=0): _x(x), _y(y){}
    
     /* --> IMPOTANTE
     *      - Const necessário para explicitar para o compilador que esse método 
     *  não altera o objeto (instância atual) 
     *      - Isso permite, posteriormente, usar esse método em outros métodos
     *  que recebem: const Vetor &x
     */
    double abs() const          
    {
        return sqrt(_x*_x + _y*_y);
    }

    friend Vetor operator +(const Vetor &a, const Vetor &b){
        
        return Vetor(a._x + b._x, a._y + b._y);
    
    }

    friend Vetor operator -(const Vetor &a, const Vetor &b){

        return Vetor(a._x - b._x, a._y - b._y);

    }

    friend int operator *(const Vetor &a, const Vetor &b){

        return (a._x*b._x + a._y*b._y);

    }

    friend int operator ^(const Vetor &a, const Vetor &b){
        
        return (a._x * b._y - b._x * a._y);
    
    }

    friend double operator <(const Vetor &a, const Vetor &b)
    {

        return 180/M_PI*acos((a*b)/(a.abs()*b.abs()));
    
    }

    friend std::ostream& operator <<(std::ostream &out, const Vetor &a){
        
        out << '(' << a._x << "," << a._y << ')';
    
        return out;

    }
};

int main(){
    Vetor v;
    std::cout << v << std::endl;
    v = v+Vetor(1, 2);
    std::cout << v << std::endl;
    v = v+Vetor(1, 2);
    std::cout << v << std::endl;
    v = v-Vetor(1, 6);
    std::cout << v << std::endl;
    int a = v*Vetor(3, 2);
    std::cout << a << std::endl;
    int b = v^Vetor(-4501, 9002);
    std::cout << b << std::endl;
    double c = v.abs();
    std::cout << c << std::endl;
    return 0;
}

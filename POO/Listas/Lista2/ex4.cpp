/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <random>
#include <math.h>


class Polinomio2{
    int _a;
    int _b;
    int _c;

public:
    
    Polinomio2(int a=0, int b=0, int c=0)
    {
        if(a==0){
            _a = 1;
            _b = std::rand();
            _c = std::rand();
        }
        else{
            _a = a; _b = b; _c = c; 
        }
    }

    double operator ()(double x){
        return(_a*(x*x) + _b*x + _c);
    }

    double *raizes()
    {
        int a = _a, b =_b, c =_c;
        double * ret;
        double x1, x2;
        // int ai = 100 *  a; int bi = 100 * b; int ci = 100 * c;
        double delta = (b*b) - (4*a*c);

        if(delta > 0)
        {
            if(a!=0)
            {
                x1 = ( (-b) - sqrt( delta ) )/( 2.0*a );
                x2 = ( (-b) + sqrt( delta ) )/( 2.0*a );

                ret = new double[3];
                
                ret[0] = 2;
                ret[1] = x1; ret[2] = x2; 
            }

            else
            {
                x1 = -c / b;
                ret = new double[2];
                ret[0] = 1; ret[1] = x1;
            }

            return ret;
        }

        if(delta == 0)
        {
            if(a == 0 && c == 0){
                ret = new double [1];
                ret[0] = INFINITY;
            }

            else if(a!=0){
                x1 = (-b)/( 2.0*a );
                ret = new double[2];
                ret[0] = 1; ret[1] = x1;
            }

            else{
                ret = new double[1];
                ret[0] = 0;
            }

            return ret;
        }

        ret = new double[1];
        ret[0] = 0;

        return ret;
    }
};


int main(){
    double *v;
    Polinomio2 p1(1, 1, 1);
    v = p1.raizes(); for(int i=0; i<=v[0]; i++) std::cout << v[i] << " " ;
    std::cout << '\n' << p1(2) << '\n' ;
    Polinomio2 p2(1, 2, 1);
    v = p2.raizes(); for(int i=0; i<=v[0]; i++) std::cout << v[i] << " " ;
    std::cout << '\n' << p2(2) << '\n' ;
    Polinomio2 p3(1, -3, 2);
    v = p3.raizes(); for(int i=0; i<=v[0]; i++) std::cout << v[i] << " " ;
    std::cout << '\n' << p3(2) << '\n' ;
    return 0;
}
/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>


std::string raizes(double a, double b, double c){

    std::string ret;
    double x1, x2;
    // int ai = 100 *  a; int bi = 100 * b; int ci = 100 * c;
    double delta = (b*b) - (4*a*c);

    if(delta > 0){
        if(a!=0){
            x1 = ( (-b) - sqrt( delta ) )/( 2.0*a );
            x2 = ( (-b) + sqrt( delta ) )/( 2.0*a );

            if(a>0)
                ret = std::to_string(x1) + " e " + std::to_string(x2) ;
            else
                ret = std::to_string(x2) + " e " + std::to_string(x1) ;            
        }
        else{
            x1 = -c / b;
            ret = std::to_string(x1);
        }

        return ret;
    }
    
    if(delta == 0){
        if(a == 0 && c == 0){
            ret = "Infinitas";
        }

        else if(a!=0){
            x1 = (-b)/( 2.0*a );
            ret = std::to_string(x1);
        }

        else{
            ret = "Nenhuma";
        }
        return ret;
    }

    ret = "Nenhuma";
    return ret;
}
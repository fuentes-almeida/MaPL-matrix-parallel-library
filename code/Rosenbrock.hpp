/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent base class for Rosenbrock function representation, the different kinds of functions must inherit
 *   
 *   --> Atributes
 *     The following attributes have been implemented:
 *       - 
 *   	 
 *  
 *   --> Methods
 *     The following methods have been implemented:
 *       - 
 * 
 *   *********************************************************************************/

#ifndef ROSENBROCK_HPP
#define ROSENBROCK_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Function.hpp"

using namespace std;

class Rosenbrock2D : public Function {
    

    public:
        Rosenbrock2D();
        
        double evaluate(Vector *x);
        Vector gradient(Vector *x);
        Matrix hessian(Vector *x);

};

#endif // ROSENBROCK_HPP

/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent class for Linear Solver representation, including proper attributes and methods
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

#ifndef LINEARSOLVER_HPP
#define LINEARSOLVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Solver.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

class LinearSolver : public Solver {
    
    protected:
        Matrix *A;
        Vector *b, *x;

    public:
        LinearSolver();
        void load(Matrix *A, Vector *x, Vector *b);
        virtual Vector* solve(){ return NULL; };

};

#endif // LINEARSOLVER_HPP

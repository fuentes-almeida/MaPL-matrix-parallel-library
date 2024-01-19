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

#ifndef CHOLESKYSOLVERLLT_HPP
#define CHOLESKYSOLVERLLT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

class CholeskySolverLLT : public LinearSolver {

    public:
        CholeskySolverLLT();
        void load(Matrix *A, Vector *x, Vector *b);
        Vector* solve();

};

#endif // CHOLESKYSOLVERLLT_HPP
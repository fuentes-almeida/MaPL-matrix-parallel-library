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

#ifndef CHOLESKYSOLVERLDLT_HPP
#define CHOLESKYSOLVERLDLT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "CholeskySolverLLT.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

class CholeskySolverLDLT : public CholeskySolverLLT {

    public:
        CholeskySolverLDLT();
        void load(Matrix *A, Vector *x, Vector *b);
        
        Vector* solve();
        void generateCholeskyMatrix();
        void solveCholeskyInfMatrix();
        void solveCholeskyDiagonal();
        void solveCholeskySupMatrix();
};

#endif // CHOLESKYSOLVERLDLT_HPP
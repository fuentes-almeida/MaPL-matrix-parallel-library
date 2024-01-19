/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Derived class for Line Search Optimizer representation, including proper attributes and methods
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

#ifndef LINESEARCHOPTIMIZER_HPP
#define LINESEARCHOPTIMIZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Optimizer.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Function.hpp"
#include "CholeskySolverLDLT.hpp"


using namespace std;

Solver *mySolver = new CholeskySolverLDLT();

class LineSearchOptimizer : public Optimizer {

    public:
        LineSearchOptimizer();
        Vector steepestDescentDirection(Function fx, Vector *x);
        Vector newtonDescentDirection(Function fx, Vector *x);

        double stepLengthSecondOrder(string condition, double stepLength, Vector x, Function fx, Vector descentDirection);
        double stepLengthThirdOrder(string condition, double stepLength, Vector x, Function fx, Vector descentDirection);
        double stepLengthBacktracking(string condition, double stepLength, Vector x, Function fx, Vector descentDirection);

        bool validWeakWolfeCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient);
        bool validStrongWolfeCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient);
        bool validGoldsteinCondition(double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient);
        bool validCondition(string condition, double stepLength, Vector *x, Function fx, Vector descentDirection, Vector gradient);
};

#endif // LINESEARCHOPTIMIZER_HPP

/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent base class for Solver representation, the different kinds of solvers must inherit
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

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>
#include <stdlib.h>
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

class Solver {
    protected:
        string name;
        string type;

    public:
		Solver();
		virtual string getName() const { return name; }
		virtual void setName(const string &n) { name = n; }

		virtual string getType() const { return name; }
		virtual void setType(const string &n) { name = n; }
		
		virtual string getParameterName(int i) const { return ""; }
		virtual string getParameterValue(int i) const { return ""; }
		virtual int getNumberOfParameters() const { return 0; }

        virtual void load(Matrix *A, Vector *x, Vector *b){};
        virtual Vector* solve(){ return NULL; };

		virtual ~Solver() {}
};

#endif // SOLVER_HPP
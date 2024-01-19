/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent base class for Function representation, the different kinds of functions must inherit
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

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <stdlib.h>
#include "Vector.hpp"
#include "Matrix.hpp"

using namespace std;

class Function {
    protected:
        string name;
        string type;
		int dimension;

    public:
		Function();
		virtual string getName() const { return name; }
		virtual void setName(const string &n) { name = n; }

		virtual string getType() const { return name; }
		virtual void setType(const string &n) { name = n; }

		virtual int getDimension() const { return dimension; }
		virtual void setDimension(const int &n) { dimension = 0; }

		virtual string getParameterName(int i) const { return ""; }
		virtual string getParameterValue(int i) const { return ""; }
		virtual int getNumberOfParameters() const { return 0; }
        
		virtual double evaluate(Vector *x) const { return 0; }
        virtual Vector gradient(Vector *x) const { return NULL; }
        virtual Matrix hessian(Vector *x) const { return NULL; }

		virtual ~Function() {}
};

#endif // SOLVER_HPP
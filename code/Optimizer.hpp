/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent base class for Optimizer representation, the different kinds of functions must inherit
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

#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class Optimizer {
    protected:
        string name;
        string type;

    public:
		Optimizer();
		virtual string getName() const { return name; }
		virtual void setName(const string &n) { name = n; }

		virtual string getType() const { return name; }
		virtual void setType(const string &n) { name = n; }
		
		virtual string getParameterName(int i) const { return ""; }
		virtual string getParameterValue(int i) const { return ""; }
		virtual int getNumberOfParameters() const { return 0; }

		virtual ~Optimizer() {}
};

#endif // OPTIMIZER_HPP

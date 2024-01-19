/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent class for Vector representation, including proper attributes and methods
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

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;
typedef vector<double> vector_d;

class Vector{
    private:
        //Private attributes
        vector_d data;
        int length; 
    
    public:
        //Constructor void
        Vector(void){};

        //Constructor from dat file
        Vector(char* datFileName);

        //Constructor from STL vector
        Vector(vector_d vector){};

        //Constructor for empty initialized vector
        Vector(int length);

        //Destructor
        ~Vector(void){};

        //Getters
        int inline        getLength   (void)  const { return this->length; }
        vector_d inline   getData     (void)  const { return this->data;   }
        
        //Inline Setters
        void inline setData    (vector_d data)   { this->data = data;          }
        void inline setLength  (vector_d data)   { this->length = data.size(); }
        
        //member functions
        Vector duplicate();

        //Overriden operators
        friend ostream& operator<<(ostream& out,const Vector& vector);
        friend Vector operator-(const Vector& vector);
        friend Vector operator-(const Vector& vectorLeft, const Vector& vectorRight);
        friend Vector operator+(const Vector& vectorLeft, const Vector& vectorRight);
        friend Vector operator*(const Vector& vector, const double scalar);
        friend double operator*(const Vector& vectorLeft, const Vector& vectorRight);


};

#endif // VECTOR_H

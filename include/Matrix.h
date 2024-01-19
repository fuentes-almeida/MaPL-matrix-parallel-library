/***********************************************************************************
 * AUTHORS
 *   - Gerardo Fuentes
 * 
 * DATE
 *    May 2021
 *
 * DESCRIPTION
 *   Parent class for Matrix representation, including proper attributes and methods
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

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Vector.h"

using namespace std;
typedef vector<double> vector_d;

class Matrix{
    private:
        //Private attributes
        vector_d data;
        int numColumns;
        int numRows; 
    
    public:
        //Constructor void
        Matrix(void){};

        //Constructor from dat file
        Matrix(char* datFileName);

        //Constructor for empty initialized matrix
        Matrix(int numRows, int numColumns);

        //Constructor from STL vector
        Matrix(vector_d vector, int numColumns, int numRows){};

        //Destructor
        ~Matrix(void){};

        //Getters
        vector_d inline   getData         (void)     const { return this->data;         }
        int inline        getNumColumns   (void)     const { return this->numColumns;   }
        int inline        getNumRows      (void)     const { return this->numRows;      }
        double inline     getElement      (int i, int j);

        //Inline Setters
        void inline setData         (vector_d data)    { this->data = data;                }
        void inline setNumColumns   (int numColumns)   { this->numColumns = numColumns;    }
        void inline setNumRows      (int numRows)      { this->numRows = numRows;          }
        void inline setElement      (int i, int j, double value);

        //member functions
        Matrix duplicate();
        
        //Overriden operators
        friend ostream& operator<<(ostream& out,const Matrix& matrix);
        friend Vector operator*(const Matrix& matrixLeft, const Vector& vectorRight);
};

#endif // MATRIX_H

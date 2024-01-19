#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

using namespace std;

//Constructor from dat file
Matrix::Matrix(char* datFileName){
 
  ifstream datFile (datFileName);

    if (datFile.is_open()){

        int numColumns, numRows = 0;
        double value;
        
        datFile >> numRows >> numColumns;    
        vector_d data (numColumns * numRows);
    
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numColumns; j++){
            
            datFile >> value;
            data[i*numRows + j] = value;
        }
    }
    
    datFile.close();
    this->data = data;
    this->numColumns = numColumns;
    this->numRows = numRows;

  }
  else cout << "Unable to open file"; 
}

//Constructor for empty initialized matrix
Matrix::Matrix(int numRows, int numColumns){

    this->data = vector_d(numColumns * numRows);   

}

Matrix Matrix::duplicate(){
  
  int numRows = this->numRows;
  int numColummns = this->numColumns;
  Matrix copy(numRows, numColummns);
  
  for (int i = 0; i < numRows; i++){
      for (int j = 0; j < numColummns; j++){
          copy.data[i*numRows + j] = this->data[i*numRows + j];
      }
  }

  return copy;
}

//Print method override
ostream& operator<<(ostream& out, const Matrix& matrix){

    for (int i=0; i<matrix.numRows; i++){
        for (int j=0; j<matrix.numColumns; j++){
            out<<matrix.data[i+matrix.numRows +j]<<" ";
        }
        out<<endl;
    }
    out<<endl;
    return out;
}

//Matrix Vector product method override
Vector operator*(const Matrix& matrixLeft, const Vector& vectorRight){

    Vector result(matrixLeft.numRows);
    vector_d resultData = result.getData();
    vector_d vectorRightData = vectorRight.getData();

    for (int i=0; i<matrixLeft.numRows; i++){
            double suma=0;
        for(int j=0; j<matrixLeft.numColumns; j++){
            suma += matrixLeft.data[i*matrixLeft.numRows + j] * vectorRightData[j];
        }
        resultData[i] = suma;
    }
    return result;
}
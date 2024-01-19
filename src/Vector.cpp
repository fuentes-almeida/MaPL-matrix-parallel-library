#include "Vector.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

using namespace std;

//Constructor from dat file
Vector::Vector(char* datFileName){

  ifstream datFile (datFileName);

  if (datFile.is_open()){

    int length;
    vector_d data;
    double value;

    datFile >> length;

    for (int i = 0; i < length; i++){
      datFile >> value;
      //cout<<value<<endl;
      data.push_back(value);
    }
  
    datFile.close();

    this->data = data;
    this->length = length;
  }

  else cout << "Unable to open file"; 
}

//Constructor for empty initialized vector
Vector::Vector(int length){

    this->data = vector_d(length);  
    this->length = length; 

}

Vector Vector::duplicate(){
  
  int length = this->getLength();
  Vector copy(length);
  
  for (int i = 0; i < length; i++){
    copy.data[i] = this->data[i];
  }

  return copy;
}

//Print method override
ostream& operator<<(ostream& out, const Vector& vector){

    for (int i=0; i<vector.length; i++){
      out<<vector.data[i]<<" ";
      out<<endl;
    }
    return out;
}

//Negative method override
Vector operator-(const Vector& vector){
    Vector result(vector.length);
    for (int i=0; i<vector.length; i++){
      result.data[i] = -vector.data[i];
    }
    return result;
}

//Substract method override
Vector operator-(const Vector& vectorLeft, const Vector& vectorRight){
    Vector result(vectorLeft.length);
    for (int i=0; i<vectorLeft.length; i++){
      result.data[i] = vectorLeft.data[i] - vectorRight.data[i];
    }
    return result;
}

//Adition method override
Vector operator+(const Vector& vectorLeft, const Vector& vectorRight){
    Vector result(vectorLeft.length);
    for (int i=0; i<vectorLeft.length; i++){
      result.data[i] = vectorLeft.data[i] + vectorRight.data[i];
    }
    return result;
}

//Scalar product method override
Vector operator*(const Vector& vector, const double scalar){
    Vector result(vector.length);
    for (int i=0; i<vector.length; i++){
      result.data[i] = scalar * vector.data[i];
    }
    return result;
}

//Inner product method override
double operator*(const Vector& vectorLeft, const Vector& vectorRight){
    double result = 0;
    for (int i=0; i<vectorLeft.length; i++){
      result += vectorLeft.data[i] * vectorRight.data[i];
    }
    return result;
}
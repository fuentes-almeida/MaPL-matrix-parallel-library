#include "Rosenbrock.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

using namespace std;

Rosenbrock2D::Rosenbrock2D(){
    cout<<"Initializing constructor Rosenbrock"<<endl;
    this->name = "Rosenbrock";
    this->type = "Algebraic";
    this->dimension = 2;
}

double Rosenbrock2D::evaluate(Vector *x){
    
    vector_d x_data = x->getData();
    double x1 = x_data[0];
    double x2 = x_data[1];

    return 100 * (x2 - x1*x1) * (x2 - x1*x1) + (1 - x1)*(1 - x1);
}

Vector Rosenbrock2D::gradient(Vector *x){

    Vector gradient(2);
    vector_d data = gradient.getData();

    vector_d x_data = x->getData();
    double x1 = x_data[0];
    double x2 = x_data[1];

    data[0] = -400*x1*(x2 - x1*x1) - 2*(1 - x1);
    data[1] = 200*(x2 - x1*x1);

    return gradient;
}

Matrix Rosenbrock2D::hessian(Vector *x){

    Matrix hessian(2,2);
    vector_d h_data = hessian.getData();

    vector_d x_data = x->getData();
    double x1 = x_data[0];
    double x2 = x_data[1];

    h_data[0] = -400*(x2-x1*x1)+800*x1*x1+2;
    h_data[1] = -400*x1;
    h_data[2] = -400*x1;
    h_data[3] = 200;

    return hessian;
}
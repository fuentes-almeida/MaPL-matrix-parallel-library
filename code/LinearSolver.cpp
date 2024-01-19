#include "LinearSolver.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

using namespace std;

LinearSolver::LinearSolver(){
    cout<<"Initializing constructor LinearSolver"<<endl;
    this->type = "LinearEquationsSolver";
    this->name = "LinearSolver";
}

void LinearSolver::load(Matrix *A, Vector *x, Vector *b){
    
    this->A = A;
    this->b = b;
    this->x = x;

    cout << *A <<endl;
    cout << *b <<endl;
}

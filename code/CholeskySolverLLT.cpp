#include "CholeskySolverLLT.hpp"
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

using namespace std;

CholeskySolverLLT::CholeskySolverLLT():LinearSolver(){
    cout<<"Initializing constructor LLT"<<endl;
    this->name = "CholeskySolverLLT";
}

void CholeskySolverLLT::load(Matrix *A, Vector *x, Vector *b){
    LinearSolver::load(A, x, b);
}

Vector* CholeskySolverLLT::solve(){
    //TODO: write LLT solver implementation
    return NULL;
}
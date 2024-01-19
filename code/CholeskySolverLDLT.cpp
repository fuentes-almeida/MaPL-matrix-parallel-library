#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "CholeskySolverLDLT.hpp"
#include "CholeskySolverLLT.hpp"
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

CholeskySolverLDLT::CholeskySolverLDLT():CholeskySolverLLT(){
    cout<<"Initializing constructor LDLT"<<endl;
    this->name = "CholeskySolverLDLT";
}

void CholeskySolverLDLT::load(Matrix *A, Vector *x, Vector *b){
    LinearSolver::load(A, x, b);
}

void CholeskySolverLDLT::generateCholeskyMatrix(){
    
    Matrix *A = this->A;
    int rank = A->getNumRows();
    vector_d data = A->getData();
    
    for (int i = 0; i <rank; i++){
        double sum = 0;
        for(int k = 0; k < i; k++){
            sum = sum + data[i * rank + k] * data[i * rank +k] * data[k * rank + k];
            cout << sum << endl;
        }

        data[i * rank + i] = data[i * rank + i] - sum;
        
        for(int j = i + 1; j < rank; j++){
            double sum = 0;

            for(int k = 0; k < i; k++){
                sum = sum + data[i * rank + k] * data[j * rank + k] * data[k * rank + k];
                cout << sum << endl;
            }

            data[j * rank + i] = (data[j * rank + i] - sum) / data[i * rank + i];
            data[i * rank + j] = data[j * rank + i];

        }
    }
    this->A->setData(data);

    cout << "Decomposed Matrix in L and LT components" << endl;
    cout << *A << endl;
}


void CholeskySolverLDLT::solveCholeskyInfMatrix(){

    Matrix *L = this->A;
    Vector *b  = this->b;
    Vector *x  = this->x;

    vector_d b_data = b->getData();
    vector_d x_data = x->getData();
    vector_d L_data = L->getData();
    int rank = x->getLength();
    cout<<rank<<endl;
    x_data[0] = b_data[0];
    
    for(int j = 1; j < rank; j++){
        double sum=0;
        for(int i = 0; i <= j - 1; i++){
            sum = sum + L_data[j * rank + i] * x_data[i];
            cout << sum << endl;
        }
        x_data[j] = b_data[j] - sum;
    }
    this->x->setData(x_data);

    cout << "Solution for Cholesky Inferior system Lx=b" << endl;
    cout << *x << endl;
}


void CholeskySolverLDLT::solveCholeskyDiagonal(){
    
    Matrix *D = this->A;
    Vector *b  = this->x;
    Vector *x  = this->x;

    vector_d b_data = b->getData();
    vector_d x_data = x->getData();
    vector_d D_data = D->getData();
    int rank = x->getLength();

    for(int i = 0; i < rank; i++){
        x_data[i] = b_data[i] / D_data[i * rank + i];
    }
    this->x->setData(x_data);

    cout << "Solution for Cholesky Diagonal system Dx=b" << endl;
    cout << *x << endl;
}


void CholeskySolverLDLT::solveCholeskySupMatrix(){
    
    Matrix *LT = this->A;
    Vector *b  = this->x;
    Vector *x  = this->x;

    vector_d b_data  = b->getData();
    vector_d x_data  = x->getData();
    vector_d LT_data = LT->getData();
    int rank = x->getLength();

    x_data[rank-1] = b_data[rank-1];

    for(int j = rank - 2; j >= 0; j--){
        double sum = 0;
        for(int i = j + 1; i < rank; i++){
            sum = sum + LT_data[j * rank + i] * x_data[i];
            cout << sum << endl;
        }
        x_data[j] = b_data[j] - sum;
    }
    this->x->setData(x_data);

    cout << "Solution for Cholesky Superior system LTx=b" << endl;
    cout << *x << endl;
}


Vector* CholeskySolverLDLT::solve()
{
    generateCholeskyMatrix();
    solveCholeskyInfMatrix();
    solveCholeskyDiagonal();
    solveCholeskySupMatrix();

    cout << "Solution for Complete Cholesky system Ax=b" << endl;
    cout << *x << endl;

    return this->x;
}
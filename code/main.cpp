#include <stdio.h>
#include <stdlib.h>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "CholeskySolverLDLT.hpp"
using namespace std;

int main(int argc, char **argv){
    
    cout<<"Running application"<<endl;

    char *command, *matrixFileName, *vectorFileName;
    if (argc > 1){
        command = argv[1];
        matrixFileName = argv[2];
        vectorFileName = argv[3];
    }

    Vector *b = new Vector(vectorFileName);
    Matrix *A = new Matrix(matrixFileName);
    
    int range = b->getLength();
    Vector *x = new Vector(range);
    
    cout<<*b<<endl;
    cout<<*A<<endl;

    Solver *mySolver = new CholeskySolverLDLT();
    mySolver->load(A, x, b);
    mySolver->solve();
    cout<<*x<<endl;
    
    return 0;
}


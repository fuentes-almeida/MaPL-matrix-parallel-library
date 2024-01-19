#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main(int argc, char **argv){

    cout<<"Running application"<<endl;

    char *matrixFileName, *vectorFileName;
    if (argc > 1){
        matrixFileName = argv[2];
        vectorFileName = argv[1];
    }

    Vector *b = new Vector(vectorFileName);
    Matrix *A = new Matrix(matrixFileName);
    
    int range = b->getLength();
    
    cout<<*b<<endl;
    cout<<*A<<endl;

    return 0;
}
#ifndef MEMO_H
#define MEMO_H

int *RequestVectorIntMem(int);
float *RequestVectorFloatMem(int);
char *RequestVectorCharMem(int);
unsigned char*RequestVectorUnsignedCharMem(int);
double *RequestVectorDoubleMem(int);

int **RequestMatrixIntMem(int,int);
float **RequestMatrixFloatMem(int,int);
char **RequestMatrixCharMem(int,int);
unsigned char**RequestMatrixUnsignedCharMem(int,int);
double **RequestMatrixDoubleMem(int,int);

void freeMatrizInt(int**, int);
void freeMatrizFloat(float**, int);
void freeMatrizChar(char**, int);
void freeMatrizUnsignedChar(unsigned char**, int);
void freeMatrizDouble(double**, int);

#endif // MEMO_H


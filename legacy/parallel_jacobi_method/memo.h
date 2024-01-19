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
void freeMatrizInt(int **matriz, int w);
void freeMatrizFloat(float **matriz, int w);
void freeMatrizChar(char **matriz, int w);
void freeMatrizUnsignedChar(unsigned char **matriz, int w);
void freeMatrizDouble(double **matriz, int w);
void freeVectorInt(int *lista);
void freeVectorFloat(float *lista);
void freeVectorChar(char *lista);
void freeVectorUnsignedChar(unsigned char *lista);
void freeVectorDouble(double *lista);

#endif // MEMO_H


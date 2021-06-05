#include <stdio.h>
#include <stdlib.h>
#include "memo.h"

int *RequestVectorIntMem(int data_size){
    int *pointer;
    pointer=(int*)calloc(data_size,sizeof(int));
    return pointer;}

float *RequestVectorFloatMem(int data_size){
    float *pointer;
    pointer=(float*)calloc(data_size,sizeof(float));
    return pointer;}

char *RequestVectorCharMem(int data_size){
    char *pointer;
    pointer=(char*)calloc(data_size,sizeof(char));
    return pointer;}

unsigned char*RequestVectorUnsignedCharMem(int data_size){
    unsigned char*pointer;
    pointer=(unsigned char*)calloc(data_size,sizeof(unsigned char));
    return pointer;}

double *RequestVectorDoubleMem(int data_size){
    double *pointer;
    pointer=(double*)calloc(data_size,sizeof(double));
    return pointer;}

int **RequestMatrixIntMem(int data_size1, int data_size2){
    int i;
    int **pointer;
    pointer=(int **)calloc(data_size1,sizeof(int*));
    for (i=0;i<data_size1;i++)
        pointer[i]=(int*)calloc(data_size2,sizeof(int));
    return pointer;}

float **RequestMatrixFloatMem(int data_size1, int data_size2){
    int i;
    float **pointer;
    pointer=(float **)calloc(data_size1,sizeof(float*));
    for (i=0;i<data_size1;i++)
        pointer[i]=(float*)calloc(data_size2,sizeof(float));
    return pointer;    }

char **RequestMatrixCharMem(int data_size1, int data_size2){
    int i;
    char **pointer;
    pointer=(char **)calloc(data_size1,sizeof(char*));
    for (i=0;i<data_size1;i++)
        pointer[i]=(char*)calloc(data_size2,sizeof(char));
    return pointer;}

unsigned char**RequestMatrixUnsignedCharMem(int data_size1, int data_size2){
    int i;
    unsigned char **pointer;
    pointer=(unsigned char **)calloc(data_size1,sizeof(unsigned char*));
    for (i=0;i<data_size1;i++)
        pointer[i]=(unsigned char*)calloc(data_size2,sizeof(unsigned char));
    return pointer;}

double **RequestMatrixDoubleMem(int data_size1, int data_size2){
    int i;
    double **pointer;
    pointer=(double **)calloc(data_size1,sizeof(double*));
    for (i=0;i<data_size1;i++)
        pointer[i]=(double*)calloc(data_size2,sizeof(double));
    return pointer;}

void freeMatrizInt(int **matriz, int w){
    int i;
    for( i=0;i<w;i++)
        free(matriz[i]);
    free(matriz);
}

void freeMatrizFloat(float **matriz, int w){
    int i;
    for( i=0;i<w;i++)
        free(matriz[i]);
    free(matriz);
}

void freeMatrizChar(char **matriz, int w){
    int i;
    for( i=0;i<w;i++)
        free(matriz[i]);
    free(matriz);
}

void freeMatrizUnsignedChar(unsigned char **matriz, int w){
    int i;
    for( i=0;i<w;i++)
        free(matriz[i]);
    free(matriz);
}

void freeMatrizDouble(double **matriz, int w){
    int i;
    for( i=0;i<w;i++)
        free(matriz[i]);
    free(matriz);
}

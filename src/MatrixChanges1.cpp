//
// Created by dzondzi on 28.12.20..
//


#include <rg/MatrixChanges1.h>

std::vector<std::vector<unsigned int>> matrica;
std::vector<std::vector<unsigned int>> pocMatrica;

int n;
int m;


void initMatrix(std::string path){
    Matrix matrix(path);
    n = matrix.getN();
    m = matrix.getM();
    matrica = matrix.getMatrix();
    pocMatrica = matrix.getMatrix();
}

void restartMatrix(){
    matrica = pocMatrica;
}









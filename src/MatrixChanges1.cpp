//
// Created by dzondzi on 28.12.20..
//


#include <rg/MatrixChanges1.h>

std::vector<std::vector<unsigned int>> outMatrix;
std::vector<std::vector<unsigned int>> initialMatrix;

int n;
int m;


void initMatrix(std::string path){
    Matrix matrix(path);
    n = matrix.getN();
    m = matrix.getM();
    outMatrix = matrix.getMatrix();
    initialMatrix = matrix.getMatrix();
}

void restartMatrix(){
    outMatrix = initialMatrix;
}









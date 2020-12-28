//
// Created by dzondzi on 28.12.20..
//


#include <rg/MatrixChanges1.h>

std::vector<std::vector<unsigned int>> matrica;

void initMatrix(std::string path){
    Matrix matrix(path);
    matrica = matrix.getMatrix();
}
//
// Created by dzondzi on 28.12.20..
//
#pragma once
#ifndef PROJECT_BASE_LOADMATRIX_H
#define PROJECT_BASE_LOADMATRIX_H


#include <vector>
#include <iostream>
#include <learnopengl/filesystem.h>
#include <fstream>


class Matrix{
    int n;
    int m;
    std::vector<std::vector<unsigned int>> matrica;
public:

    Matrix(std::string filePath){
        std::ifstream myfile;
        myfile.open(filePath);
        if(!myfile){
            std::cerr << "Myfile failed to open! \n";
            exit(EXIT_FAILURE);
        }
        myfile >> n >> m;
        if(n < 1 || m < 1){
           std::cerr << "n or m < 1 \n";
           exit(EXIT_FAILURE);
        }

        std::vector<unsigned int> pom(m);

        for(int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                myfile >> pom[i];
            }
            matrica.push_back(pom);
        }
    }

    int getN(){
        return n;
    }
    int getM(){
        return m;
    }

    std::vector<std::vector<unsigned int>> getMatrix(){
        return matrica;
    };

};


#endif //PROJECT_BASE_LOADMATRIX_H

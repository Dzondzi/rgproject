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
     //   ASSERT(myfile,"myfile failed to open");
        myfile >> n >> m;
       // ASSERT(n > -1, "n > 0");
       // ASSERT(m > -1, "m > 0");
        std::cerr << n << " " <<m;
        std::vector<unsigned int> pom(m);
        int x;
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

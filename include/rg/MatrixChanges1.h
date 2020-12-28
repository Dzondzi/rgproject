//
// Created by dzondzi on 28.12.20..
//
#pragma once
#ifndef PROJECT_BASE_MATRIXCHANGES1_H
#define PROJECT_BASE_MATRIXCHANGES1_H

#include <rg/LoadMatrix.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <vector>

extern std::vector<std::vector<unsigned int>> matrica;
extern int n;
extern int m;
void initMatrix(std::string path);
void changingMatrixInput(GLFWwindow* window);

#endif //PROJECT_BASE_MATRIXCHANGES1_H

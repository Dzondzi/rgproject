//
// Created by dzondzi on 28.12.20..
//


#include <rg/MatrixChanges1.h>

std::vector<std::vector<unsigned int>> matrica;
int n;
int m;

void initMatrix(std::string path){
    Matrix matrix(path);
    n = matrix.getN();
    m = matrix.getM();
    matrica = matrix.getMatrix();
}

void changingMatrixInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ){

    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ){

    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ){

    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ){

    }


}






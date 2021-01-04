//
// Created by dzondzi on 28.12.20..
//

#ifndef PROJECT_BASE_GAME_H
#define PROJECT_BASE_GAME_H

#include <rg/ourShader.h>
#include <rg/model.h>
#include <rg/LoadMatrix.h>
#include <rg/MatrixChanges1.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <rg/ourTexture.h>
#include <rg/ourCamera.h>


unsigned int initBuffers();
unsigned int initEBOBuffers();
void renderBox(int i, int j, int type, unsigned int VAO, ourShader shader, std::vector<ourTexture> teksture, ourCamera camera,
               glm::vec3 pointLightPositions[],int numOfPointLights, int pacmanRotaion);
void renderLightCube(unsigned int VAO, ourShader shader,ourCamera camera, glm::vec3 pointLightPosition);
void renderModel(Model model, Shader shader, ourCamera camera, glm::vec3 pointLightPosition);
#endif //PROJECT_BASE_GAME_H

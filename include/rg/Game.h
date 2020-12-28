//
// Created by dzondzi on 28.12.20..
//

#ifndef PROJECT_BASE_GAME_H
#define PROJECT_BASE_GAME_H

#include <rg/Shader.h>

#include <rg/LoadMatrix.h>
#include <rg/MatrixChanges1.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <rg/Texture2D.h>

unsigned int initBuffers();
void renderBox(int i, int j, int type, unsigned int VAO, Shader shader, std::vector<Texture> teksture);

#endif //PROJECT_BASE_GAME_H

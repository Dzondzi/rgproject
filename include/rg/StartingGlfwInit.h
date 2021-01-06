//
// Created by dzondzi on 27.12.20..
//
#pragma once

#ifndef PROJECT_BASE_STARTINGGLFWINIT_H
#define PROJECT_BASE_STARTINGGLFWINIT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

extern GLFWwindow* window;

void ourGlfwInit();


#endif //PROJECT_BASE_STARTINGGLFWINIT_H

//
// Created by dzondzi on 27.12.20..
//

//
// Created by dzondzi on 27.12.20..
//

#include <rg/StartingCallbackInit.h>
#include <rg/StartingGlfwInit.h>

unsigned int width = 800;
unsigned int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void ourCallbackInit(){
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}



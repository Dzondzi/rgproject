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


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        std::cerr << "G\n";
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        std::cerr << "O\n";
        height*=1.02;
        width*=1.02;
        glfwSetWindowSize(window, width, height);
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwMaximizeWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        glfwRestoreWindow(window);
    }



}

void ourCallbackInit(){
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
}



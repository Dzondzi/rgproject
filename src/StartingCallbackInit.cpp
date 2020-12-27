//
// Created by dzondzi on 27.12.20..
//

//
// Created by dzondzi on 27.12.20..
//

#include <rg/StartingCallbackInit.h>
#include <rg/StartingGlfwInit.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){


}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset){

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        std::cerr << "G\n";
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    }

}

void ourCallbackInit(){
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}



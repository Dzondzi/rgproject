#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <rg/StartingGlfwInit.h>
#include <rg/StartingCallbackInit.h>

// camera


int main() {
    //starting initialize
    startGlfwInit();
    startCallbackInit();


    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
